#ifndef GAME_H_
#define GAME_H_

#include <raylib.h>

typedef struct {
    Rectangle bound;
} Block;

#define FINISH_RADIUS 20.0f
#define GRAVITY     2000.0f

typedef struct {
    Block *items;
    size_t count,capacity;

    Vector2 spawn,finish;
} Room;

#define PLAYER_MAX_SPEED   600.0f
#define PLAYER_JUMP       -220.0f
#define PLAYER_ACCELERATE 1200.0f
#define PLAYER_FRICTION   1200.0f

typedef struct {
    Rectangle bound;
    Vector2 velocity;

    Rectangle platform;
    bool grounded,body_hardening;
} Player;

#define BALL_MAX_SPEED   800.0f
#define BALL_ACCELERATE 1000.0f
#define BALL_FRICTION   1000.0f

typedef struct {
    Rectangle bound;
    Vector2 velocity;
} Ball;

#endif // GAME_H_
