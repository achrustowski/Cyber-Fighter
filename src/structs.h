#ifndef STRUCTS_H_
#define STRUCTS_H_

#include "defs.h"
#include <stdbool.h>
#include <raylib.h>
#include "enums.h"

typedef struct Entity Entity;
typedef struct Animation Animation;
typedef struct Timer Timer;
typedef struct Tile Tile;
typedef struct Player_Data Player_Data;
typedef struct Enemy_Data Enemy_Data;
typedef struct Bullet_Data Bullet_Data;
typedef union Object_Data Object_Data;

typedef struct App
{
    int                 keyboard[MAX_NUM_KEYS];
    int                 S_W, S_H;
    float               delta_time;
    bool                show_gui_mode;
    Camera2D            camera;
} App;

struct Timer
{
    float               length;
    float               time;
    bool                timeout;
};

struct Animation
{
    Timer               timer;
    int                 frame_count;
    Animation_Type      anim_type;
    bool                one_shot_cycle;
};

typedef struct Tile
{
    Group               group;
    Vector2             position;
    Rectangle           collision_box;
    bool                is_active;
    Rectangle           src_rect;
    Texture2D           texture;
} Tile;

struct Player_Data
{
    Player_State        state;
    int                 attack_timer;
    int                 jump_reload;
    bool                is_attacking;
};

struct Enemy_Data
{
    Enemy_State         state;
    Timer               damage_timer;
    bool                is_flashing;
    int                 health;
};

struct Bullet_Data
{
    Bullet_State        state;
};

union Object_Data
{
    Player_Data         player;
    Enemy_Data          enemy;
    Bullet_Data         bullet;
};

struct Entity
{
    Object_Type         type;
    Object_Data         data;
    Vector2             position;
    Vector2             velocity;
    Vector2             acceleration;
    Rectangle           collision_box;
    Rectangle           src_rect;
    float               rotate;
    float               speed;
    int                 sprite_frame;
    bool                is_moving;
    bool                grounded;
    Timer               timer;
    Animation           animation;
    Texture2D           texture;
    Entity*             next;
    Direction           dir;
};

typedef struct Stage
{
    Entity              fighter_head;
    Entity*             fighter_tail;
    Entity              bullet_head;
    Entity*             bullet_tail;
} Stage;

#endif
