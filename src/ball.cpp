#include "ball.h"
#include <stdlib.h>
#include <SDL2_gfxPrimitives.h>

Ball::Ball(int r, int x, int y)
{
    radius = r;
    xpos = x;
    ypos = y;

    xvel = 10;
    yvel = 6;

    maxvel = 15;
};

void Ball::move()
{
    int rand_pert = -3 + (rand() % 6);

    xpos += xvel;

    if ((xpos < 0) || (xpos > 1024)) // temp hardcode screen limits
    {
        xvel *= -1;
        yvel += rand_pert; // Perturbation
    }

    ypos += yvel;

    if ((ypos < 0) || (ypos > 768))
    {
        yvel *= -1;

        xvel += rand_pert; // Perturbation
    }

    if (xvel > maxvel)
    {
        xvel = maxvel;
    }
    else if (xvel < -maxvel)
    {
        xvel = -maxvel;
    }

    if (yvel > maxvel)
    {
        yvel = maxvel;
    }
    else if (yvel < -maxvel)
    {
        yvel = -maxvel;
    }
}

int Ball::getX()
{
    return xpos;
}

int Ball::getY()
{
    return ypos;
}

void Ball::render(SDL_Renderer *renderer)
{
    filledCircleRGBA(renderer, xpos, ypos, radius, 0, 0, 0, 128);
}

void Ball::paddleBounce()
{
}