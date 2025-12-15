#include "draw.h"
#include "defs.h"
#include <raylib.h>

Texture2D load_texture(char* filename, int scale)
{
    Image image = LoadImage(filename);
    ImageResizeNN(&image, image.width * scale, image.height * scale);
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);

    return texture;
}

void blit_rect(Texture2D texture, Rectangle src_rect, Vector2 position, int dir)
{
    if (dir < 0)
    {
        src_rect.width *= dir;        // flip horizontally
        position.x -= CELL_SIZE;
    }
    DrawTextureRec(texture, src_rect, position, WHITE);
}
