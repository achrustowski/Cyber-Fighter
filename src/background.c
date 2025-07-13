#include "background.h"
#include "draw.h"
#include <raylib.h>
#include "structs.h"

extern App app;

static Texture2D    background;
float origin_y;

void init_background(void)
{
    background = load_texture("data/bg/bg_layer1.png", 1);
}

void draw_background()
{
    DrawTextureEx(background,
            (Vector2){
            (app.camera.target.x - (app.S_W / 2.0f)),
            (app.camera.target.y - background.height)
            }, 0.0f, 2.0f, WHITE);
}

void remove_background_textures()
{
    UnloadTexture(background);
}
