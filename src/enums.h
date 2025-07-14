#ifndef ENUMS_H_
#define ENUMS_H_

typedef enum Direction
{
    LEFT = -1,
    RIGHT = 1,
} Direction;

typedef enum Animation_Type
{
    REPEATING = 1,
    ONE_SHOT = 2
} Animation_Type;

typedef enum Player_Attack_Type
{
    SIMPLE,
    COMBO,
    ULTRA,
    KICK
} Player_Attack_Type;

typedef enum Player_State
{
    IDLE,
    JUMP,
    D_JUMP,
    RUN,
    ATTACK
} Player_State;

typedef enum Enemy_State
{
    STATIONARY,
    STOMPING,
    DAMAGED,
    DEAD
} Enemy_State;

typedef enum Bullet_State
{
    MOVING,
    COLLIDING,
    INACTIVE
} Bullet_State;

typedef enum Object_Type
{
    PLAYER,
    ENEMY,
    BULLET
} Object_Type;

#endif
