#include <stdio.h>

#include <game.h>
#include <raymath.h>

#define NOB_IMPLEMENTATION
#include <nob.h>
#include <math.h>

#define SCREEN_WIDTH  32.0f*16.0f
#define SCREEN_HEIGHT 32.0f*12.0f

Ball ball       =  {0};
Room *room      = NULL;
Player player   =  {0};
Camera2D camera =  {0};
static Ball throw_path[PATH_CAPACITY];

Game_State_Kind current_state = GAME_PLAY;
Room_Tag current_room_tag     = ONE_ONE;
    

bool finished      = false;
bool do_simulation =  true;

bool rectangle_eq(Rectangle a, Rectangle b) {
    if (a.x != b.x || a.y != b.y) return false;
    if (a.width != b.width || a.height != b.height) return false;

    return true;
}

bool check_player_touch_ground(const Room *r, Player *p, float dt) {
    for (size_t i = 0; i < r->count; ++i) {
        Rectangle it = r->items[i].bound;

        Rectangle player_rect = p->bound;
        player_rect.y += p->velocity.y * dt;

        if (p->velocity.y > 0) {
            if (CheckCollisionRecs(player_rect, it) && p->bound.y < it.y) {
                p->grounded   = true;
                p->platform   = it;
                p->velocity.y = 0;
                p->bound.y    = it.y - p->bound.height;
                
                return true;
            }
        }
    }

    return false;
}

bool player_hit_wall(Room *r, Player *p, float dt) {
    for (size_t i = 0; i < r->count; ++i) {
        Rectangle it = r->items[i].bound;

        Rectangle player_rect = p->bound;
        player_rect.x += p->velocity.x * dt;

        if (!rectangle_eq(it, p->platform)) {
            if (p->velocity.x > 0) {
                if (CheckCollisionRecs(player_rect, it) && p->bound.x < it.x) {
                    if (r->items[i].breakable && p->body_hardening && p->velocity.x >= PLAYER_MAX_SPEED*0.8) {
                        nob_da_remove_unordered(r, i);
                    }

                    p->velocity.x = 0.0f;
                    p->bound.x = it.x-p->bound.width;
                    if (p->velocity.y < 0) p->velocity.y *= 0.9f;

                    return true;
                }
            } else if (p->velocity.x < 0) {
                if (CheckCollisionRecs(player_rect, it) &&
                    p->bound.x+p->bound.width > it.x + it.width) 
                {
                    if (r->items[i].breakable && p->body_hardening && p->velocity.x <= -PLAYER_MAX_SPEED*0.8) {
                        nob_da_remove_unordered(r, i);
                    }

                    p->velocity.x = 0.0f;
                    p->bound.x = it.x+it.width;
                    if (p->velocity.y < 0) p->velocity.y *= 0.9f;

                    return true;
                }
            }
        }
    }

    return false;
}

void player_hit_ceil(const Room *r, Player *p, float dt) {
    for (size_t i = 0; i < r->count; ++i) {
        Rectangle it = r->items[i].bound;
        Rectangle player_rect = p->bound;

        player_rect.x += p->velocity.x * dt;
        player_rect.y += p->velocity.y * dt;

        if (!rectangle_eq(it, p->platform)) {
            if (p->velocity.y < 0) {
                if (CheckCollisionRecs(player_rect, it) && 
                    p->bound.x+p->bound.width > it.x    &&
                    p->bound.x < it.x+it.width) 
                {
                    p->bound.y = it.y + it.height;
                    p->velocity.y = 0;
                    break;
                }
            }
        }
    }
}

void player_update(const Room *r, Player *p, float dt) {
    if (!do_simulation) return;

    p->velocity.y += GRAVITY * dt;
    
    check_player_touch_ground(r, p, dt);

    float move = 0.0f;
    float frict = PLAYER_FRICTION;
    Vector2 max_speed_a = FLOAT2VEC2D( PLAYER_MAX_SPEED);
    Vector2 max_speed_b = FLOAT2VEC2D(-PLAYER_MAX_SPEED);
    if (p->grounded) {
        if (IsKeyDown(KEY_A)) move -= 1.0f;
        if (IsKeyDown(KEY_D)) move += 1.0f;

        if (p->bound.x+p->bound.width < p->platform.x ||
            p->bound.x > p->platform.x + p->platform.width) p->grounded = false;

    } else {
        frict /= 8.0f;
        max_speed_a.x *= 2.0f;
        max_speed_b.x *= 2.0f;
    }

    move = (player_hit_wall((Room*)r, p, dt)) ? 0.0f : move;
    player_hit_ceil(r, p, dt);

    if (move != 0.0f) {
        p->velocity.x += move * PLAYER_ACCELERATE * dt;
    } else {
        if      (p->velocity.x > 0) p->velocity.x = fmaxf(0, p->velocity.x - frict * dt);
        else if (p->velocity.x < 0) p->velocity.x = fminf(0, p->velocity.x + frict * dt);
    }

    p->velocity = Vector2Clamp(p->velocity, max_speed_b, max_speed_a);
    p->bound.x += p->velocity.x * dt;
    p->bound.y += p->velocity.y * dt;

    if (IsKeyPressed(KEY_W) && p->grounded) {
        p->velocity.y = PLAYER_JUMP;
        p->grounded = false;
    }

    p->body_hardening = IsKeyDown(KEY_S);
}

void player_swap(const Room *r, Player *p, Ball *b) {
    Vector2 ball_pos = (Vector2){b->bound.x, b->bound.y};
    Vector2 ball_velocity = b->velocity;

    b->velocity = p->velocity;
    b->bound.x  = p->bound.x;
    b->bound.y  = p->bound.y + (p->bound.height - b->bound.height);

    p->velocity = ball_velocity;
    p->bound.x  = ball_pos.x;
    p->bound.y  = ball_pos.y - (p->bound.height - b->bound.height);

    NOB_UNUSED(r);
}

void ball_check_collision_and_bounce(const Room *r, Ball *b, float dt) {
    for (size_t i=0; i<r->count; ++i) {
        Rectangle it = r->items[i].bound;
        Rectangle ball_rect = b->bound;

        ball_rect.x += b->velocity.x * dt;
        ball_rect.y += b->velocity.y * dt;

        if (CheckCollisionRecs(it, ball_rect)) {
            Vector2 plane = {0};
            if (b->bound.y < it.y && b->bound.x > it.x){
                plane.y    = -1.0f;
                b->bound.y = it.y-b->bound.height;
                
            } else if (b->bound.y > it.y+it.height && b->bound.x > it.x) {
                plane.y    =  1.0f;
                b->bound.y = it.y+it.height;

            } else if (b->bound.y+b->bound.height >= it.y && b->bound.y <= it.y+it.height) {
                if (b->bound.x <= it.x) {
                    plane.x    = -1.0f;
                    b->bound.x = it.x-b->bound.width;

                } else if (b->bound.x >= it.x+it.width) {
                    plane.x    =  1.0f;
                    b->bound.x = it.x+it.width;
                }
            }
            
            b->velocity = Vector2Reflect(b->velocity, plane);
            b->velocity = Vector2Scale(b->velocity, 0.7f);
            break;
        }
    }
}

void ball_simulate(const Room *r, Ball *b, float dt) {
    b->velocity.y += GRAVITY * dt;

    if      (b->velocity.x > 0) b->velocity.x = fmaxf(0, b->velocity.x - (BALL_FRICTION/8) * dt);
    else if (b->velocity.x < 0) b->velocity.x = fminf(0, b->velocity.x + (BALL_FRICTION/8) * dt);
    
    if      (b->velocity.y > 0) b->velocity.y = fmaxf(0, b->velocity.y - (BALL_FRICTION/8) * dt);
    else if (b->velocity.y < 0) b->velocity.y = fminf(0, b->velocity.y + (BALL_FRICTION/8) * dt);

    b->velocity = Vector2Clamp(b->velocity, FLOAT2VEC2D(-BALL_MAX_SPEED*2), FLOAT2VEC2D(BALL_MAX_SPEED*2));
    b->bound.x += b->velocity.x * dt;
    b->bound.y += b->velocity.y * dt;

    ball_check_collision_and_bounce(r, b, dt);
}

void ball_update_throw_path(const Room *r, const Ball *b) {
    throw_path[0].bound    = b->bound;
    throw_path[0].velocity = b->velocity;

    for (int i=0; i < PATH_CAPACITY; ++i) {
        Ball *it = &throw_path[i];
        float dt = i * 0.0003;

        ball_simulate(r, it, dt);

        if (i<PATH_CAPACITY-1) {
            Ball *next     = &throw_path[i+1];
            next->bound    = it->bound;
            next->velocity = it->velocity;
        }
    }
}

void ball_update(const Room *r, const Player *p, Ball *b, float dt) {
    if (b->state == BALL_HOLDED) {
        b->bound.x = p->bound.x;
        b->bound.y = p->bound.y + p->bound.height/2;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse    = GetScreenToWorld2D(GetMousePosition(), camera);
            Vector2 ball_pos = (Vector2){b->bound.x, b->bound.y};
            b->velocity      = Vector2Scale(Vector2Subtract(mouse, ball_pos), BALL_SPEED_SCALE);
            
            ball_update_throw_path(r, b);
            do_simulation = false;
        }
        
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            b->state = BALL_THROWED;
            do_simulation = true;
        }

    } else if (b->state == BALL_THROWED) {
        if (!do_simulation) return;

        ball_simulate(r, b, dt);
        if (IsKeyPressed(KEY_SPACE)) {
            player_swap(r, (Player *)p, b);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_BACKSPACE)) {
            b->state = BALL_HOLDED;
        }
    }
}

void do_one_frame(void) {
    float dt = GetFrameTime();

    if (current_state == GAME_PLAY) {
        room->update(room, dt);

        player_update(room, &player, dt);
        ball_update(room, &player, &ball, dt);

        if (CheckCollisionCircleRec(room->finish, 5, player.bound)) {
            current_state = ROOM_COMPLETE;
        }

    } else if (current_state == ROOM_COMPLETE) {
        current_room_tag += 1;
        current_state = GAME_PLAY;

        room = get_room(current_room_tag);
        player.bound.x = room->start.x;
        player.bound.y = room->start.y;

        ball.state = BALL_HOLDED;
    }

    BeginDrawing();
    ClearBackground(GetColor(0x181828FF));

    if (current_state == GAME_PLAY) {

        BeginMode2D(camera);
        for (size_t i=0; i<room->count; ++i) {
            DrawRectangleRec(room->items[i].bound, RED);
        }

        Color player_col = player.body_hardening ? YELLOW : BLUE;
        DrawRectangleRec(player.bound, player_col);

        DrawRectangleRec(ball.bound, GREEN);

        if (ball.state == BALL_HOLDED && !do_simulation) {
            Color path_color = GREEN;
            for (int i=0; i < PATH_CAPACITY; ++i) {
                path_color.a = fmax(0xFF - i*5, 0);
                DrawRectangleRec(throw_path[i].bound, path_color);
            }
        }

        DrawCircle(room->start.x, room->start.y, 5, GREEN);
        DrawCircle(room->finish.x, room->finish.y, 5, RED);

        EndMode2D();

    } else if (current_state == ROOM_COMPLETE) {
    }

    DrawFPS(5,5);

    EndDrawing();
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Transporter");
    player.bound  = (Rectangle){0, 200, 24, 32};

    ball.bound.width  = 5;
    ball.bound.height = 5;

    for (int i=ONE_ONE; i<ROOM_COUNT; ++i) {
        Room *r = get_room(i);
        r->init(r);
    }

    room = get_room(current_room_tag);
    player.bound.x = room->start.x;
    player.bound.y = room->start.y;

    camera.target.x = SCREEN_WIDTH/2.0f;
    camera.target.y = SCREEN_HEIGHT/2.0f;
    camera.zoom = 1.0f;

    camera.offset = camera.target;

    while (!WindowShouldClose()) do_one_frame();

    CloseWindow();
    return 0;
}
