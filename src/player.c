#include "defs.h"
#include <raylib.h>
#include "structs.h"
#include "player.h"
#include "draw.h"
#include <stdlib.h>
#include <string.h>
#include "enums.h"
#include <stdio.h>

extern App app;
extern Stage stage;

static Entity* player;

static Animation idle_animation;
static Animation run_animation;
static Animation run_attack_animation;
static Animation punch_animation;
static Animation jump_animation;
static Animation hurt_animation;
static Animation double_jump_animation;
static Animation death_animation;
static Animation climb_animation;
static Animation attack_one_animation;
static Animation attack_two_animation;
static Animation attack_three_animation;

static Texture2D idle_texture;
static Texture2D run_texture;
static Texture2D run_attack_texture;
static Texture2D punch_texture;
static Texture2D jump_texture;
static Texture2D hurt_texture;
static Texture2D double_jump_texture;
static Texture2D death_texture;
static Texture2D climb_texture;
static Texture2D attack_one_texture;
static Texture2D attack_two_texture;
static Texture2D attack_three_texture;

static void init_player_textures(void);
static void init_player_animations(void);
static void player_movement(void);
static void player_idle(void);
static void player_run(void);
static void player_jump(void);
static void player_double_jump(void);
static void player_attack(void);

void init_player(void)
{
    player = (Entity*)malloc(sizeof(Entity));
    memset(player, 0, sizeof(Entity));
    stage.fighter_tail->next = player;
    stage.fighter_tail = player;

    player->type = PLAYER;
    player->data.player.state = IDLE;
    player->grounded = true;
    player->position = (Vector2) {0.0f, 0.0f};
    player->velocity = (Vector2) {HORIZONTAL_SPEED, VERTICAL_SPEED};
    player->speed = 0.0f;
    player->acceleration = (Vector2) {300.0f, 0.0f};
    player->src_rect = (Rectangle) {0.0f, 0.0f, CELL_SIZE * FIGHTER_SCALE, CELL_SIZE * FIGHTER_SCALE};
    player->dir = RIGHT;
    player->rotate = 0;
    player->is_moving = false;
    player->data.player.jump_reload = 2;

    player->texture = idle_texture;
    player->animation = idle_animation;

    player->timer.time = 0;
    player->timer.timeout = false;
}

static void player_movement()
{
    if (player->is_moving)
    {
        player->position.x += player->dir * player->velocity.x * app.delta_time;
    }
    if (!player->grounded)
    {
        player->position.y += player->speed * app.delta_time;
        player->speed += GRAVITY * app.delta_time;
        if (player->position.y >= 0.0f)
        {
            player->position.y = 0.0f;
            player->grounded = true;
            player->data.player.jump_reload = 2;
        }
    }
}

void do_player_logic(void)
{
    switch (player->data.player.state)
    {
        case IDLE:
            if (player->is_moving && player->grounded)
            {
                player->data.player.state = RUN;
                player_run();
            }
            if (!player->grounded)
            {
                player->data.player.state = JUMP;
                player_jump();
            }
            if (player->data.player.is_attacking && player->grounded)
            {
                player->data.player.state = ATTACK;
                player_attack();
            }
            break;
        case RUN:
            if (!player->is_moving && player->grounded)
            {
                player->data.player.state = IDLE;
                player_idle();
            }
            if (!player->grounded)
            {
                player->data.player.state = JUMP;
                player_jump();
            }
            break;
        case JUMP:
            if (!player->is_moving && player->grounded)
            {
                player->data.player.state = IDLE;
                player_idle();
            }
            if (player->is_moving && player->grounded)
            {
                player->data.player.state = RUN;
                player_run();
            }
            if (!player->grounded && IsKeyPressed(KEY_SPACE))
            {
                player->data.player.state = D_JUMP;
                player_double_jump();
            }
            break;
        case D_JUMP:
            if (!player->is_moving && player->grounded)
            {
                player->data.player.state = IDLE;
                player_idle();
            }
            if (player->is_moving && player->grounded)
            {
                player->data.player.state = RUN;
                player_run();
            }
            break;
        case ATTACK:
            break;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        player->is_moving = true;
        player->dir = RIGHT;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        player->is_moving = true;
        player->dir = LEFT;
    }
    if (IsKeyPressed(KEY_SPACE) && player->data.player.jump_reload >= 0)
    {
        --player->data.player.jump_reload;
        player->grounded = false;
        player->speed = -player->velocity.y;
    }
    if (IsKeyPressed(KEY_A))
    {
    }
    if (IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_LEFT))
    {
        player->is_moving = false;
    }
    player_movement();
}

static void player_idle()
{
    printf("Idle\n");
    player->texture = idle_texture;
    player->animation = idle_animation;
}

static void player_run()
{
    player->texture = run_texture;
    player->animation = run_animation;
}

static void player_jump()
{
    player->texture = jump_texture;
    player->animation = jump_animation;
}

static void player_double_jump()
{
    --player->data.player.jump_reload;
    player->texture = double_jump_texture;
    player->animation = double_jump_animation;
}

static void player_attack()
{
    printf("Attack\n");
    player->texture = attack_one_texture;
    player->animation = attack_one_animation;
}

void init_player_resources(void)
{
    init_player_textures();
    init_player_animations();
}

static void init_player_textures()
{
    idle_texture            = load_texture("data/player/1 Biker/Biker_idle.png", FIGHTER_SCALE);
    run_texture             = load_texture("data/player/1 Biker/Biker_run.png", FIGHTER_SCALE);
    run_attack_texture      = load_texture("data/player/1 Biker/Biker_run_attack.png", FIGHTER_SCALE);
    attack_one_texture      = load_texture("data/player/1 Biker/Biker_attack1.png", FIGHTER_SCALE);
    attack_two_texture      = load_texture("data/player/1 Biker/Biker_attack2.png", FIGHTER_SCALE);
    attack_three_texture    = load_texture("data/player/1 Biker/Biker_attack3.png", FIGHTER_SCALE);
    climb_texture           = load_texture("data/player/1 Biker/Biker_climb.png", FIGHTER_SCALE);
    death_texture           = load_texture("data/player/1 Biker/Biker_death.png", FIGHTER_SCALE);
    double_jump_texture     = load_texture("data/player/1 Biker/Biker_doublejump.png", FIGHTER_SCALE);
    hurt_texture            = load_texture("data/player/1 Biker/Biker_hurt.png", FIGHTER_SCALE);
    jump_texture            = load_texture("data/player/1 Biker/Biker_jump.png", FIGHTER_SCALE);
    punch_texture           = load_texture("data/player/1 Biker/Biker_punch.png", FIGHTER_SCALE);
}

static void init_player_animations(void)
{
    idle_animation.frame_count = 4;
    idle_animation.timer.length = 0.9f;
    idle_animation.anim_type = REPEATING;

    run_animation.frame_count = 4;
    run_animation.timer.length = 0.6f;
    run_animation.anim_type = REPEATING;

    run_attack_animation.frame_count = 6;
    run_attack_animation.timer.length = 0.6f;
    run_attack_animation.anim_type = REPEATING;

    attack_one_animation.frame_count = 6;
    attack_one_animation.timer.length = 4.6f;
    attack_one_animation.anim_type = ONE_SHOT;

    attack_two_animation.frame_count = 8;
    attack_two_animation.timer.length = 0.6f;
    attack_two_animation.anim_type = ONE_SHOT;

    attack_three_animation.frame_count = 8;
    attack_three_animation.timer.length = 0.6f;
    attack_three_animation.anim_type = ONE_SHOT;

    climb_animation.frame_count = 8;
    climb_animation.timer.length = 0.6f;
    climb_animation.anim_type = REPEATING;

    death_animation.frame_count = 6;
    death_animation.timer.length = 0.6f;
    death_animation.anim_type = REPEATING;

    double_jump_animation.frame_count = 6;
    double_jump_animation.timer.length = 1.0f;
    double_jump_animation.anim_type = ONE_SHOT;

    hurt_animation.frame_count = 2;
    hurt_animation.timer.length = 0.6f;
    hurt_animation.anim_type = REPEATING;

    jump_animation.frame_count = 4;
    jump_animation.timer.length = 1.01f;
    jump_animation.anim_type = ONE_SHOT;

    punch_animation.frame_count = 6;
    punch_animation.timer.length = 0.6f;
    punch_animation.anim_type = REPEATING;
}

void remove_player_textures(void)
{
    UnloadTexture(idle_texture);
    UnloadTexture(run_texture);
    UnloadTexture(run_attack_texture);
    UnloadTexture(punch_texture);
    UnloadTexture(jump_texture);
    UnloadTexture(hurt_texture);
    UnloadTexture(double_jump_texture);
    UnloadTexture(death_texture);
    UnloadTexture(climb_texture);
    UnloadTexture(attack_one_texture);
    UnloadTexture(attack_two_texture);
    UnloadTexture(attack_three_texture);
}
