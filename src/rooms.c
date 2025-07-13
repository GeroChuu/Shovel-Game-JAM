#include <game.h>

#include <nob.h>

void init_mission_one_room_one(Room *r)       {
    nob_da_append(r, ((Block){(Rectangle){32*0  , 32*10, 32*16, 32*2}})); // base
    nob_da_append(r, ((Block){(Rectangle){32*0  , 32*0 , 32*1 , 32*12}}));// left wall
    nob_da_append(r, ((Block){(Rectangle){32*1.3, 32*4 , 32*15, 32*1}})); // second floor
    nob_da_append(r, ((Block){(Rectangle){32*1  , 32*0 , 32*15, 32*2}})); // roof

    r->start.x = 32*14;
    r->start.y = 32* 9;
    r->finish.x = 32*15;
    r->finish.y = 32* 3;
}

void init_mission_one_room_two(Room *r)       {
    (void)r;
}

void init_mission_one_room_three(Room *r)     {
    (void)r;
}

void init_mission_two_room_one(Room *r)       {
    (void)r;
}

void init_mission_two_room_two(Room *r)       {
    (void)r;
}

void init_mission_two_room_three(Room *r)    {
    (void)r;
}

void init_mission_three_room_one(Room *r)    {
    (void)r;
}

void init_mission_three_room_two(Room *r)    {
    (void)r;
}

void init_mission_three_room_three(Room *r) {
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
    (void)r;
    (void)dt;
}

void update_mission_two_room_one(Room *r, float dt)     {
    (void)r;
    (void)dt;
}

void update_mission_two_room_two(Room *r, float dt)     {
    (void)r;
    (void)dt;
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
