#include "init.h"
#include <raylib.h>
#include "gui_mode.h"
#include "stage.h"
#include "background.h"
#include "camera.h"
#include "tiles.h"

void init_game()
{
    init_stage();
    init_tilemap();
    init_camera();
    init_background();
    init_gui_font();
}

void cleanup()
{
    unload_resources();
    CloseWindow();
}
