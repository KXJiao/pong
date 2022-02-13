#include "ball.h"
#include <SDL2_gfxPrimitives.h>

Ball::Ball(int r, int x, int y)
{
    radius = r;
    xpos = x;
    ypos = y;

    xvel = 10;
    yvel = 20;
};

void Ball::move()
{
    xpos += xvel;

    if ((xpos < 0) || (xpos > 1024)) // temp hardcode screen limits
    {
        xvel *= -1;
    }

    ypos += yvel;

    if ((ypos < 0) || (ypos > 768))
    {
        yvel *= -1;
    }
}

void Ball::render(SDL_Renderer *renderer)
{
    filledCircleRGBA(renderer, xpos, ypos, radius, 0, 0, 0, 128);
}

void Ball::paddleBounce()
{
}