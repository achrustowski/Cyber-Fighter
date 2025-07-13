#include "gui_mode.h"
#include "raylib.h"
#include "structs.h"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

extern App app;
extern Stage stage;
Font font;

void init_gui_font(void)
{
    font = LoadFont("fonts/Terminus (TTF) Bold 700.ttf");
    SetTextLineSpacing(16);
}

void init_gui_mode(void)
{
    int fps = GetFPS();
    char fps_text[32];
    sprintf(fps_text, "FPS: %d", fps);
    char player_coordinates[48];
    sprintf(player_coordinates, "Player X: %.2f, Player Y: %.2f", stage.fighter_head.next->position.x, stage.fighter_head.next->position.y);
    GuiSetFont(font);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(GREEN));
    if (app.show_gui_mode)
    {
        GuiLabel((Rectangle) {50.0f, 0.0f, 250, 100}, fps_text);
        GuiLabel((Rectangle) {200.0f, 0.0f, 450, 100}, player_coordinates);
    }
}
