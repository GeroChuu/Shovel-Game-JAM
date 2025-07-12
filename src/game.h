#ifndef GAME_H_
#define GAME_H_

#include <raylib.h>

typedef void(Room_Init_Func)(void);
typedef void(Room_Draw_Func)(void);
typedef void(Room_Update_Func)(float);

typedef struct {
    Rectangle bound;
} Block;

#define FLOAT2VEC2D(f) (Vector2){(f), (f)}

#define PATH_CAPACITY    80

#define FINISH_RADIUS 20.0f
#define GRAVITY     2000.0f

typedef struct {
    Block *items;
    size_t count,capacity;
    Vector2 start, finish;
    
    Room_Init_Func *init;
    Room_Draw_Func *draw;
    Room_Update_Func *update;
} Room;

#define PLAYER_MAX_SPEED   600.0f
#define PLAYER_JUMP       -420.0f
#define PLAYER_ACCELERATE 1300.0f
#define PLAYER_FRICTION   1900.0f

typedef struct {
    Rectangle bound;
    Vector2 velocity;

    Rectangle platform;
    bool grounded,body_hardening;
} Player;

#define BALL_MAX_SPEED   800.0f
#define BALL_ACCELERATE 1000.0f
#define BALL_FRICTION   1000.0f
#define BALL_SPEED_SCALE   6.0f

typedef enum {
    BALL_HOLDED ,
    BALL_THROWED,
} Ball_State;

typedef struct {
    Rectangle bound;
    Vector2 velocity;

    Ball_State state;
} Ball;

#endif // GAME_H_
