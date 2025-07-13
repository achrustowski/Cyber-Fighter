#include "camera.h"
#include "structs.h"
#include <string.h>
#include <math.h>

extern App app;
extern Stage stage;

void init_camera()
{
    memset(&app.camera, 0, sizeof(Camera2D));
    app.camera.target = (Vector2) {0.0f, 0.0f};
    app.camera.offset = (Vector2)
    {
        app.S_W / 2.0f, app.S_H / 2.0f
    };
    app.camera.rotation = 0.0f;
    app.camera.zoom = 1.0f;
}

void do_camera_logic()
{
    app.camera.target = (Vector2)
    {
        stage.fighter_head.next->position.x + 20.0f,
        0.0f
    };
    app.camera.zoom = expf(logf(app.camera.zoom) + (float)(GetMouseWheelMove() * 0.1f));
    if (IsKeyPressed(KEY_R))
    {
        app.camera.zoom = 1.0f;
    }
}
