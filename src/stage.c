#include "stage.h"
#include "background.h"
#include "defs.h"
#include "enums.h"
#include "structs.h"
#include "player.h"
#include "enemies.h"
#include <raylib.h>
#include <string.h>
#include "draw.h"
#include "animation.h"
#include "timer.h"
#include <stdio.h>

extern App app;
extern Stage stage;

static void draw_fighters(void);
static void update_fighters_animations(void);

void init_stage(void)
{
    memset(&stage, 0, sizeof(Stage));
    stage.fighter_tail = &stage.fighter_head;
    stage.bullet_tail = &stage.bullet_head;

    init_player_resources();
    init_enemy_resources();
    init_player();
}

void do_stage_logic(void)
{
    do_player_logic();
    do_enemies_logic();
    update_fighters_animations();
}

void stage_draw(void)
{
    draw_fighters();
}

void update_fighters_animations()
{
    Entity* e;
    for (e = stage.fighter_head.next; e != NULL; e = e->next)
    {
        if (e->animation.anim_type == ONE_SHOT)
        {
            if (current_frame(&e->animation, &e->animation.timer) == e->animation.frame_count - 1)
            {
                e->src_rect.x = current_frame(&e->animation, &e->animation.timer) * CELL_SIZE * FIGHTER_SCALE;
            } else
            {
                step_animation(&e->animation.timer, app.delta_time);
                e->src_rect.x = current_frame(&e->animation, &e->animation.timer) * CELL_SIZE * FIGHTER_SCALE;
            }
        } else
        {
            step_animation(&e->animation.timer, app.delta_time);
            e->src_rect.x = current_frame(&e->animation, &e->animation.timer) * CELL_SIZE * FIGHTER_SCALE;
        }
    }
}

static void draw_fighters()
{
    Entity* e;

    for (e = stage.fighter_head.next; e != NULL; e = e->next)
    {
        blit_rect(e->texture, e->src_rect, e->position, e->dir);
    }
}

void unload_resources(void)
{
    remove_player_textures();
    remove_enemy_textures();
    remove_background_textures();
}
