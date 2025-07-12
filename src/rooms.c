#include <game.h>

void init_mission_one_room_one(void)     {
}

void init_mission_one_room_two(void)     {
}

void init_mission_one_room_three(void)   {
}

void init_mission_two_room_one(void)     {
}

void init_mission_two_room_two(void)     {
}

void init_mission_two_room_three(void)   {
}

void init_mission_three_room_one(void)   {
}

void init_mission_three_room_two(void)   {
}

void init_mission_three_room_three(void) {
}

void update_mission_one_room_one(float dt)     {
    (void)dt;
}

void update_mission_one_room_two(float dt)     {
    (void)dt;
}

void update_mission_one_room_three(float dt)   {
    (void)dt;
}

void update_mission_two_room_one(float dt)     {
    (void)dt;
}

void update_mission_two_room_two(float dt)     {
    (void)dt;
}

void update_mission_two_room_three(float dt)   {
    (void)dt;
}

void update_mission_three_room_one(float dt)   {
    (void)dt;
}

void update_mission_three_room_two(float dt)   {
    (void)dt;
}

void update_mission_three_room_three(float dt) {
    (void)dt;
}

void draw_mission_one_room_one(void)     {
}

void draw_mission_one_room_two(void)     {
}

void draw_mission_one_room_three(void)   {
}

void draw_mission_two_room_one(void)     {
}

void draw_mission_two_room_two(void)     {
}

void draw_mission_two_room_three(void)   {
}

void draw_mission_three_room_one(void)   {
}

void draw_mission_three_room_two(void)   {
}

void draw_mission_three_room_three(void) {
}

Room mission_one_room_one   = {.init = &init_mission_one_room_one, .update = &update_mission_one_room_one, .draw = &draw_mission_one_room_one};
Room mission_one_room_two   = {.init = &init_mission_one_room_two, .update = &update_mission_one_room_two, .draw = &draw_mission_one_room_two};
Room mission_one_room_three = {.init = &init_mission_one_room_three, .update = &update_mission_one_room_three, .draw = &draw_mission_one_room_three};

Room mission_two_room_one   = {.init = &init_mission_two_room_one, .update = &update_mission_two_room_one, .draw = &draw_mission_two_room_one};
Room mission_two_room_two   = {.init = &init_mission_two_room_two, .update = &update_mission_two_room_two, .draw = &draw_mission_two_room_two};
Room mission_two_room_three = {.init = &init_mission_two_room_three, .update = &update_mission_two_room_three, .draw = &draw_mission_two_room_three};

Room mission_three_room_one = {.init = &init_mission_three_room_one, .update = &update_mission_three_room_one, .draw = &draw_mission_three_room_one};
Room mission_three_room_two = {.init = &init_mission_three_room_two, .update = &update_mission_three_room_two, .draw = &draw_mission_three_room_two};
Room mission_three_room_three = {.init = &init_mission_three_room_three, .update = &update_mission_three_room_three, .draw = &draw_mission_three_room_three};

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
    }

    return NULL;
}
