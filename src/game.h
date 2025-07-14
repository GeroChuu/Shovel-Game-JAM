#ifndef GAME_H_
#define GAME_H_

#include <raylib.h>
#include <stddef.h>

typedef struct Player Player;
typedef struct Ball Ball;
typedef struct Room Room;

typedef void(Room_Init_Func)(Room*);
typedef void(Room_Draw_Func)(const Room*, const Player*, const Ball*, const Ball*, size_t);
typedef void(Room_Update_Func)(Room*, float);

typedef enum {
    MAIN_MENU,
    GAME_PLAY,
    ROOM_COMPLETE,
} Game_State_Kind;

typedef struct {
    Rectangle bound;
    bool  breakable;
} Block;

#define FLOAT2VEC2D(f) (Vector2){(f), (f)}

#define PATH_CAPACITY    80

#define FINISH_RADIUS 20.0f
#define GRAVITY     2000.0f

typedef enum {
    ONE_ONE    ,
    ONE_TWO    ,
    ONE_THREE  ,

    TWO_ONE    ,
    TWO_TWO    ,
    TWO_THREE  ,

    THREE_ONE  ,
    THREE_TWO  ,
    THREE_THREE,

    ROOM_COUNT,
} Room_Tag;

struct Room {
    Block *items;
    size_t count,capacity;
    Vector2 start, finish;
    
    Room_Init_Func *init;
    Room_Draw_Func *draw;

    Room_Update_Func *update;
};

#define PLAYER_MAX_SPEED   600.0f
#define PLAYER_JUMP       -420.0f
#define PLAYER_ACCELERATE 1300.0f
#define PLAYER_FRICTION   1400.0f

struct Player {
    Rectangle bound;
    Vector2 velocity;

    Rectangle platform;
    bool grounded,body_hardening;
};

#define BALL_MAX_SPEED   800.0f
#define BALL_ACCELERATE 1000.0f
#define BALL_FRICTION   1000.0f
#define BALL_SPEED_SCALE   6.0f

typedef enum {
    BALL_HOLDED ,
    BALL_THROWED,
} Ball_State;

struct Ball {
    Rectangle bound;
    Vector2 velocity;

    Ball_State state;
};

Room *get_room(Room_Tag tag);

#endif // GAME_H_
