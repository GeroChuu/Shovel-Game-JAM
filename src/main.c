#include <stdio.h>

#include <game.h>
#include <raymath.h>

#define NOB_IMPLEMENTATION
#include <nob.h>
#include <math.h>

#define SCREEN_WIDTH  32.0f*16.0f
#define SCREEN_HEIGHT 32.0f*12.0f

bool do_simulation = true;

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

bool rectangle_eq(Rectangle a, Rectangle b) {
    if (a.x != b.x || a.y != b.y) return false;
    if (a.width != b.width || a.height != b.height) return false;

    return true;
}

bool player_hit_wall(const Room *r, Player *p, float dt) {
    for (size_t i = 0; i < r->count; ++i) {
        Rectangle it = r->items[i].bound;

        Rectangle player_rect = p->bound;
        player_rect.x += p->velocity.x * dt;

        if (!rectangle_eq(it, p->platform)) {
            if (p->velocity.x > 0) {
                if (CheckCollisionRecs(player_rect, it) && p->bound.x < it.x) {
                    p->velocity.x = 0.0f;
                    p->bound.x = it.x-p->bound.width;
                    if (p->velocity.y < 0) p->velocity.y *= 0.9f;

                    return true;
                }
            } else if (p->velocity.x < 0) {
                if (CheckCollisionRecs(player_rect, it) &&
                    p->bound.x+p->bound.width > it.x + it.width) 
                {
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

#define FLOAT2VEC2D(f) (Vector2){(f), (f)}

void player_update(const Room *r, Player *p, float dt) {
    if (!do_simulation) return;

    p->velocity.y += GRAVITY * dt;
    
    check_player_touch_ground(r, p, dt);

    float move = 0.0f;
    float frict = PLAYER_FRICTION;
    if (p->grounded) {
        if (IsKeyDown(KEY_A)) move -= 1.0f;
        if (IsKeyDown(KEY_D)) move += 1.0f;

        if (p->bound.x+p->bound.width < p->platform.x ||
            p->bound.x > p->platform.x + p->platform.width) p->grounded = false;

    } else {
        frict /= 2.0f;
    }

    move = (player_hit_wall(r, p, dt)) ? 0.0f : move;
    player_hit_ceil(r, p, dt);

    if (move != 0.0f) {
        p->velocity.x += move * PLAYER_ACCELERATE * dt;
    } else {
        if      (p->velocity.x > 0) p->velocity.x = fmaxf(0, p->velocity.x - frict * dt);
        else if (p->velocity.x < 0) p->velocity.x = fminf(0, p->velocity.x + frict * dt);
    }

    p->velocity = Vector2Clamp(p->velocity, FLOAT2VEC2D(-PLAYER_MAX_SPEED), FLOAT2VEC2D(PLAYER_MAX_SPEED));
    p->bound.x += p->velocity.x * dt;
    p->bound.y += p->velocity.y * dt;

    if (IsKeyPressed(KEY_W) && p->grounded) {
        p->velocity.y = PLAYER_JUMP;
        p->grounded = false;
    }

    p->body_hardening = IsKeyDown(KEY_S);
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Transporter");
    Player player = {0};
    player.bound  = (Rectangle){0, 200, 24, 32};
    
    Room room = {0};
    nob_da_append(&room, ((Block){(Rectangle){32* 0, 32*10, 32*16, 32*2}}));

    Camera2D camera = {0};
    camera.target.x = SCREEN_WIDTH/2.0f;
    camera.target.y = SCREEN_HEIGHT/2.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        player_update(&room, &player, dt);

        BeginDrawing();
        ClearBackground(GetColor(0x181828FF));

        camera.offset.x = GetRenderWidth()/2;
        camera.offset.y = GetRenderHeight()/2;

        BeginMode2D(camera);
        for (size_t i=0; i<room.count; ++i) {
            DrawRectangleRec(room.items[i].bound, RED);
        }

        Color player_col = player.body_hardening ? YELLOW : BLUE;
        DrawRectangleRec(player.bound, player_col);

        EndMode2D();

        DrawFPS(5,5);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
