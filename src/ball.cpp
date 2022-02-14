#include "ball.h"
#include <stdlib.h>
#include <SDL2_gfxPrimitives.h>

Ball::Ball(int r, int x, int y)
{
    radius = r;
    xpos = x;
    ypos = y;

    xvel = 20;
    yvel = 10;

    maxvel = 25;
};

void Ball::move()
{
    int rand_pert = -3 + (rand() % 6);

    xpos += xvel;

    if ((xpos < 0) || (xpos > 1024)) // temp hardcode screen limits
    {
        xvel *= -1;
        yvel += rand_pert; // Perturbation
        if (yvel > maxvel)
            yvel -= rand_pert;
    }

    ypos += yvel;

    if ((ypos < 0) || (ypos > 768))
    {
        yvel *= -1;

        xvel += rand_pert; // Perturbation
        if (xvel > maxvel)
            xvel -= rand_pert;
    }
}

void Ball::render(SDL_Renderer *renderer)
{
    filledCircleRGBA(renderer, xpos, ypos, radius, 0, 0, 0, 128);
}

void Ball::paddleBounce()
{
}