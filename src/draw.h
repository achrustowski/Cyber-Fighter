#ifndef DRAW_H_
#define DRAW_H_

#include <raylib.h>

Texture2D load_texture(char* filename, int scale);
void blit_rect(Texture2D texture, Rectangle src_rect, Vector2 position, int dir);

#endif
