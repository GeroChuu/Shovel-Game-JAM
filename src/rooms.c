#include <game.h>

#include <nob.h>

static Player *player;

void set_player(Player *p) {
    player = p;
}

void init_mission_one_room_one(Room *r)       {
    nob_da_append(r, ((Block){(Rectangle){32*0  , 32*10, 32*4, 32*2}, false, false})); // base
    nob_da_append(r, ((Block){(Rectangle){32*12  , 32*10, 32*4, 32*2}, false, false})); // base
    
    r->start.x     = 32*.1;
    r->start.y     = 32* 9;
    r->finish.x    = 32*15.7;
    r->finish.y    = 32* 9;
}

void init_mission_one_room_two(Room *r)       {
    nob_da_append(r, ((Block){(Rectangle){32*0  , 32*10, 32*16, 32*2}, false, false})); // base
    nob_da_append(r, ((Block){(Rectangle){32*15  , 32*0 , 32*1 , 32*12}, false, false}));// left wall
    nob_da_append(r, ((Block){(Rectangle){32*0, 32*4 , 32*14.5, 32*1}, false, false})); // second floor
    nob_da_append(r, ((Block){(Rectangle){32*0  , 32*0 , 32*15, 32*2}, false, false})); // roof

    r->start.x     = 32*.1;
    r->start.y     = 32* 9;
    r->finish.x    = 32*.4;
    r->finish.y    = 32* 3;
}

Block *one_three_rock;
void init_mission_one_room_three(Room *r)     {
    Block rock     = {0};
    rock.bound     = (Rectangle){32*4, 32*0, 32*2, 32*4};
    rock.breakable = true;

    nob_da_append(r, rock);
    one_three_rock = &r->items[0];
    
    nob_da_append(r, ((Block){(Rectangle){32*0, 32*9 , 32*16, 32*1}, false, false})); // floor
    nob_da_append(r, ((Block){(Rectangle){32*0, 32*4 , 32*16, 32*1}, false, false})); // floor

    r->start.x     = 32*15;
    r->start.y     = 32* 8;
    r->finish.x    = 32*0;
    r->finish.y    = 32*8;
}

void init_mission_two_room_one(Room *r)       {
    nob_da_append(r, ((Block){(Rectangle){32*14, 32*1, 32*6, 32*1}, false, false}));// right wall
    nob_da_append(r, ((Block){(Rectangle){32*15, 32*0, 32*1, 32*1}, false, false}));// right wall
    nob_da_append(r, ((Block){(Rectangle){32*0, 32*11, 32*5, 32*1}, false, false})); // floor
    
    r->start.x     = 32*0;
    r->start.y     = 32*9;
    r->finish.x    = 32*14;
    r->finish.y    = 32*0;
}

Block *two_two_floor_slide;
Block *two_two_wall_slide;
void init_mission_two_room_two(Room *r)       {
    nob_da_append(r, ((Block){(Rectangle){32*0, 32*5, 32*5, 32*1}, false, false})); // left floor
    nob_da_append(r, ((Block){(Rectangle){32*11, 32*5, 32*5, 32*1}, false, false})); // right floor
    nob_da_append(r, ((Block){(Rectangle){32*11, 32*1, 32*5, 32*1}, false, false})); // right roof
    nob_da_append(r, ((Block){(Rectangle){32*0, 32*11 , 32*16, 32*1}, false, false})); // floor
    
    nob_da_append(r, ((Block){(Rectangle){32*0, 32*5, 32*6, 32*1}, false, false})); // floor slide
    two_two_floor_slide = &r->items[r->count-1];

    nob_da_append(r, ((Block){(Rectangle){32*11, 32*1, 32*1, 32*4}, false, false})); // wall slide
    two_two_wall_slide = &r->items[r->count-1];
    
    r->start.x     = 32*0;
    r->start.y     = 32*4;
    r->finish.x    = 32*16;
    r->finish.y    = 32*4;
}

void init_mission_two_room_three(Room *r)     {
    (void)r;
}

void init_mission_three_room_one(Room *r)     {
    (void)r;
}

void init_mission_three_room_two(Room *r)     {
    (void)r;
}

void init_mission_three_room_three(Room *r)   {
    (void)r;
}

void update_mission_one_room_one(Room *r, float dt)     {
    (void)r;
    (void)dt;
}

void update_mission_one_room_two(Room *r, float dt)     {
    (void)r;
    (void)dt;
}

void update_mission_one_room_three(Room *r, float dt)   {
    Block *floor = &r->items[1];
    if (one_three_rock->bound.y + one_three_rock->bound.height < floor->bound.y) one_three_rock->bound.y += 1000.0f*dt;
}

void update_mission_two_room_one(Room *r, float dt)     {
    (void)r;
    (void)dt;
}

void update_mission_two_room_two(Room *r, float dt)     {
    if (player->velocity.y == 0 && player->bound.y == 32*11 - player->bound.height) {
        if (two_two_floor_slide->bound.x != 32.0f * 5.0f) {
            if (two_two_floor_slide->bound.x + 1000.0f * dt >= 32.0f*5.0f) {
                two_two_floor_slide->bound.x = 32.0f * 5.0f;
            } else {
                two_two_floor_slide->bound.x += 1000.0f * dt;
            }
        }
    }

    if (player->velocity.y == 0 && player->bound.y == 32*11 - player->bound.height && player->bound.x >= 32.0f*14.0f) {
        if (two_two_floor_slide->bound.x != 32.0f * -2.0f) {
            if (two_two_wall_slide->bound.y - 1000.0f * dt <= 32.0f* -2.0f) {
                two_two_wall_slide->bound.y = 32.0f * -2.0f;
            } else {
                two_two_wall_slide->bound.y -= 1000.0f * dt;
            }
        }
    }

    NOB_UNUSED(r);
}

void update_mission_two_room_three(Room *r, float dt)   {
    (void)r;
    (void)dt;
}

void update_mission_three_room_one(Room *r, float dt)   {
    (void)r;
    (void)dt;
}

void update_mission_three_room_two(Room *r, float dt)   {
    (void)r;
    (void)dt;
}

void update_mission_three_room_three(Room *r, float dt) {
    (void)r;
    (void)dt;
}

void draw_mission_one_room_one(const Room *r, const Player *p, const Ball *b, const Ball *path, size_t count)     {
    (void)r;
    (void)p;
    (void)b;
    (void)path;
    (void)count;
}

void draw_mission_one_room_two(const Room *r, const Player *p, const Ball *b, const Ball *path, size_t count)     {
    (void)r;
    (void)p;
    (void)b;
    (void)path;
    (void)count;
}

void draw_mission_one_room_three(const Room *r, const Player *p, const Ball *b, const Ball *path, size_t count)   {
    (void)r;
    (void)p;
    (void)b;
    (void)path;
    (void)count;
}

void draw_mission_two_room_one(const Room *r, const Player *p, const Ball *b, const Ball *path, size_t count)     {
    (void)r;
    (void)p;
    (void)b;
    (void)path;
    (void)count;
}

void draw_mission_two_room_two(const Room *r, const Player *p, const Ball *b, const Ball *path, size_t count)     {
    (void)r;
    (void)p;
    (void)b;
    (void)path;
    (void)count;
}

void draw_mission_two_room_three(const Room *r, const Player *p, const Ball *b, const Ball *path, size_t count)   {
    (void)r;
    (void)p;
    (void)b;
    (void)path;
    (void)count;
}

void draw_mission_three_room_one(const Room *r, const Player *p, const Ball *b, const Ball *path, size_t count)   {
    (void)r;
    (void)p;
    (void)b;
    (void)path;
    (void)count;
}

void draw_mission_three_room_two(const Room *r, const Player *p, const Ball *b, const Ball *path, size_t count)   {
    (void)r;
    (void)p;
    (void)b;
    (void)path;
    (void)count;
}

void draw_mission_three_room_three(const Room *r, const Player *p, const Ball *b, const Ball *path, size_t count) {
    (void)r;
    (void)p;
    (void)b;
    (void)path;
    (void)count;
}

Room mission_one_room_one   = {
    .init   = &init_mission_one_room_one, 
    .draw   = &draw_mission_one_room_one,
    .update = &update_mission_one_room_one, 
};

Room mission_one_room_two   = {
    .init   = &init_mission_one_room_two, 
    .draw   = &draw_mission_one_room_two,
    .update = &update_mission_one_room_two, 
};

Room mission_one_room_three = {
    .init   = &init_mission_one_room_three, 
    .draw   = &draw_mission_one_room_three,
    .update = &update_mission_one_room_three, 
};

Room mission_two_room_one   = {
    .init   = &init_mission_two_room_one, 
    .draw   = &draw_mission_two_room_one,
    .update = &update_mission_two_room_one, 
};

Room mission_two_room_two   = {
    .init   = &init_mission_two_room_two,
    .draw   = &draw_mission_two_room_two,
    .update = &update_mission_two_room_two,
};

Room mission_two_room_three = {
    .init   = &init_mission_two_room_three,
    .draw   = &draw_mission_two_room_three,
    .update = &update_mission_two_room_three,
};

Room mission_three_room_one = {
    .init   = &init_mission_three_room_one,
    .draw   = &draw_mission_three_room_one,
    .update = &update_mission_three_room_one, 
};

Room mission_three_room_two = {
    .init   = &init_mission_three_room_two, 
    .draw   = &draw_mission_three_room_two,
    .update = &update_mission_three_room_two,
};

Room mission_three_room_three = {
    .init   = &init_mission_three_room_three, 
    .draw   = &draw_mission_three_room_three,
    .update = &update_mission_three_room_three, 
};


Room *get_room(Room_Tag tag) {
    switch (tag) {
        case ONE_ONE:     return &mission_one_room_one;
        case ONE_TWO:     return &mission_one_room_two;
        case ONE_THREE:   return &mission_one_room_three;

        case TWO_ONE:     return &mission_two_room_one;
        case TWO_TWO:     return &mission_two_room_two;
        case TWO_THREE:   return &mission_two_room_three;

        case THREE_ONE:   return &mission_three_room_one;
        case THREE_TWO:   return &mission_three_room_two;
        case THREE_THREE: return &mission_three_room_three;

        default: break;
    }

    return NULL;
}
