#include <SDL3/SDL.h>
#include <raylib.h>
#include "camera.h"
#include "gui_mode.h"
#include "stage.h"
#include "structs.h"
#include "init.h"
#include "background.h"
#include <stdlib.h>

App app;
Stage stage;

int main()
{
    srand(time(NULL));
    memset(&app, 0, sizeof(App));
    app.S_W = 1024;
    app.S_H = 768;

    InitWindow(app.S_W, app.S_H, "2D platformer");
    init_game();
    SetTargetFPS(FPS);
    app.show_gui_mode = true;

    while (!WindowShouldClose())
    {
        app.delta_time = GetFrameTime();
        do_stage_logic();
        do_camera_logic();
        if (IsKeyPressed(KEY_F1))
        {
            if (app.show_gui_mode)
            {
                app.show_gui_mode = false;
            } else
            {
                app.show_gui_mode = true;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        init_gui_mode();
        BeginMode2D(app.camera);
        draw_background();
        stage_draw();
        EndMode2D();
        EndDrawing();
    }
    cleanup();

    return 0;
}
