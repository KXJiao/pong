#include "paddle.h"
#include <SDL2_gfxPrimitives.h>

Paddle::Paddle(int h, int w, int x, int y, int limit)
{
    // Paddle dimensions
    height = h;
    width = w;

    // Paddle position
    xpos = x;
    ypos = y;

    // Paddle lower position limit
    yLimit = limit;
};

void Paddle::up()
{
    ypos -= 15;
    if (ypos < 0)
    {
        ypos = 0;
    }
}

void Paddle::down()
{
    ypos += 15;
    if (ypos + height > yLimit) // Do not surpass limit
    {
        ypos = yLimit - height;
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

int Paddle::getX()
{
    return xpos;
}

int Paddle::getY()
{
    return ypos;
}

void Paddle::render(SDL_Renderer *renderer)
{
    boxRGBA(renderer, xpos, ypos, xpos + width, ypos + height, 0, 0, 0, 255);
}
