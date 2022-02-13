#include "paddle.h"
#include <SDL2_gfxPrimitives.h>

Paddle::Paddle(int h, int w, int x, int y)
{
    height = h;
    width = w;
    xpos = x;
    ypos = y;
};

void Paddle::up()
{
    ypos -= 10;
}

void Paddle::down()
{
    ypos += 10;
}

void Paddle::render(SDL_Renderer *renderer)
{
    boxRGBA(renderer, xpos, ypos, xpos + width, ypos + height, 0, 0, 0, 255);
}
