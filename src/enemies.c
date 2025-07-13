#include "enemies.h"
#include <raylib.h>
#include "defs.h"
#include "structs.h"
#include "draw.h"
#include <string.h>
#include <stdlib.h>
#include "enums.h"

extern App app;
extern Stage stage;

static Animation idle_animation;
static Animation hit_animation;
static Animation die_animation;

static Texture2D idle_texture;
static Texture2D hit_texture;
static Texture2D die_texture;

static void init_enemy_textures(void);
static void init_enemy_animations(void);

void spawn_enemies()
{
    Entity* enemy;

    enemy = (Entity*)malloc(sizeof(Entity));
    memset(enemy, 0, sizeof(Entity));
    stage.fighter_tail->next = enemy;
    stage.fighter_tail = enemy;

    enemy->type = ENEMY;
    enemy->data.enemy.state = STATIONARY;
    enemy->position = (Vector2) {0.0f, 0.0f};
    enemy->velocity = (Vector2) {0.0f, 0.0f};
    enemy->src_rect = (Rectangle) {0.0f, 0.0f, CELL_SIZE * FIGHTER_SCALE, CELL_SIZE * FIGHTER_SCALE};
    enemy->dir = RIGHT;
    enemy->rotate = 0;
    enemy->is_moving = false;

    enemy->texture = idle_texture;
    enemy->animation = idle_animation;

    enemy->timer.time = 0;
    enemy->timer.timeout = false;
}

void do_enemies_logic()
{
}

void init_enemy_resources(void)
{
    init_enemy_textures();
    init_enemy_animations();
}

static void init_enemy_textures()
{
    idle_texture = load_texture("data/enemy/enemy.png", FIGHTER_SCALE);
    hit_texture = load_texture("data/enemy/enemy_hit.png", FIGHTER_SCALE);
    die_texture = load_texture("data/enemy/enemy_die.png", FIGHTER_SCALE);
}

static void init_enemy_animations()
{
    //idle_animation.first_frame = 0;
    //idle_animation.last_frame = 8;

    //hit_animation.first_frame = 0;
    //hit_animation.last_frame = 8;

    //die_animation.first_frame = 0;
    //die_animation.last_frame = 18;
}

void remove_enemy_textures()
{
    UnloadTexture(idle_texture);
    UnloadTexture(hit_texture);
    UnloadTexture(die_texture);
}
