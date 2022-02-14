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
    ypos -= 30;
    if (ypos < 0)
    {
        ypos = 0;
    }
}

void Paddle::down()
{
    ypos += 30;
    if (ypos + height > 768) // remove hardcode
    {
        ypos = 768 - height;
    }
}

int Paddle::getHeight()
{
    return height;
}

int Paddle::getWidth()
{
    return width;
}

int Paddle::getY()
{
    return ypos;
}

void Paddle::render(SDL_Renderer *renderer)
{
    boxRGBA(renderer, xpos, ypos, xpos + width, ypos + height, 0, 0, 0, 255);
}
