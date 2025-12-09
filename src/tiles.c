#include "tiles.h"
#include <math.h>
#include <raylib.h>
#include <stdlib.h>
#include "defs.h"
#include "structs.h"
#include "string.h"
#include "stdio.h"
#include "draw.h"
#include <dirent.h>

extern App app;
extern Entity player;

Tileset ts;

static Vector2 map_origin = { -COLS/2.0f * CELL_SIZE, -ROWS/2.0f * CELL_SIZE };

static int selected_tile_index = 0;

static void assign_tileset();
static int world_to_tile_x(float world_x);
static int world_to_tile_y(float world_y);

void do_tilemap_logic()
{
    Vector2 mouse_screen_pos = GetMousePosition();
    Vector2 mouse_world_pos = GetScreenToWorld2D(mouse_screen_pos, app.camera);

    //Check for clicks within the grid area
    int tile_x = world_to_tile_x(mouse_world_pos.x);
    int tile_y = world_to_tile_y(mouse_world_pos.y);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            tile_x >= 0 && tile_x < COLS &&
            tile_y >= 0 && tile_y < ROWS)
    {
        ts.map[tile_y][tile_x].texture = ts.tileset[selected_tile_index]; ts.map[tile_y][tile_x].position = (Vector2) {map_origin.x + tile_x * CELL_SIZE, map_origin.y + tile_y * CELL_SIZE};
    }
}

void draw_tilemap()
{
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            Tile t = ts.map[y][x];
            DrawTexture(t.texture, t.position.x, t.position.y, WHITE);
        }
    }
}

void init_tilemap()
{
    memset(&ts, 0, sizeof(Tileset));
    ts.map = NULL;
    assign_tileset();

    ts.map = (Tile**)malloc(ROWS * sizeof(Tile*));

    if (ts.map == NULL)
    {
        TraceLog(LOG_ERROR, "Failed to allocate memory for tilemap");
        exit(1);
    }

    for (int y = 0; y < ROWS; y++)
    {
        ts.map[y] = (Tile*)malloc(COLS * sizeof(Tile));

        for (int x = 0; x < COLS; x++)
        {
            ts.map[y][x].texture = (Texture2D) {0};
            ts.map[y][x].position = (Vector2) {0.0f, 0.0f};
        }
    }
}

int compareStrings(const void *a, const void *b)
{
    const char *strA = *(const char **)a;
    const char *strB = *(const char **)b;
    return strcmp(strA, strB);
}

static void assign_tileset()
{
    struct dirent *entry;
    DIR *dir;
    char *directory = "data/1 Tiles/";  // target directory
    char *filenames[100];    // array to hold up to 100 file names
    int count = 0;
    char filename[100] = "";

    strcat(filename, directory);

    dir = opendir(directory);
    if (dir == NULL)
    {
        perror("Unable to open directory");
        exit(1);
    }

    while ((entry = readdir(dir)) != NULL)
    {
        // skip '.' and '..'
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // store filename
        filenames[count] = malloc(strlen(entry->d_name) + 1);
        if (filenames[count] == NULL)
        {
            perror("malloc failed");
            closedir(dir);
            exit(1);
        }

        strcpy(filenames[count], entry->d_name);
        count++;
    }
    closedir(dir);

    // Sort filenames alphabetically
    qsort(filenames, count, sizeof(char *), compareStrings);

    // Assign filepath for each tile to tileset array
    for (int i = 0; i < TILESET_SIZE; i++)
    {
        strcat(filename, filenames[i]);
        ts.tileset[i] = load_texture(filename, 1);
        memset(filename, 0, sizeof(filename));
        strcat(filename, directory);
    }
    

    // Free sorted filenames
    for (int i = 0; i < count; i++)
    {
        free(filenames[i]);
    }

}

int world_to_tile_x(float world_x) {
    return (int)floor((world_x - map_origin.x) / CELL_SIZE);
}

int world_to_tile_y(float world_y) {
    return (int)floor((world_y - map_origin.y) / CELL_SIZE);
}
