#include "ball.h"
#include <stdlib.h>
#include <SDL2_gfxPrimitives.h>

Ball::Ball(int r, int x, int y)
{
    radius = r;
    xpos = x;
    ypos = y;

    scoring = 0;

    xvel = 10;
    yvel = 6;

    maxvel = 15;
};

void Ball::move(int windowHeight, int windowWidth)
{
    int rand_pert = -3 + (rand() % 6); // Degree of perturbation (on wall bounce)

    xpos += xvel;

    if (xpos > windowWidth)
    {
        scoring = 1;
    }
    else if (xpos < 0)
    {
        scoring = 2;
    }

    ypos += yvel;

    if ((ypos < 0) || (ypos > windowHeight))
    {
        yvel *= -1;

        xvel += rand_pert; // Perturbation
    }

    // Limit speed of ball
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
    boxRGBA(renderer, xpos, ypos, xpos + radius, ypos + radius, 0, 0, 0, 128);
}

bool Ball::paddleBounce(Paddle *paddle)
{
    SDL_Rect *ballBounds = new SDL_Rect;
    ballBounds->x = xpos;
    ballBounds->y = ypos;
    ballBounds->h = radius;
    ballBounds->w = radius;

    SDL_Rect *paddleBounds = new SDL_Rect;
    paddleBounds->x = paddle->getX();
    paddleBounds->y = paddle->getY();
    paddleBounds->h = paddle->getHeight();
    paddleBounds->w = paddle->getWidth();

    if (SDL_HasIntersection(ballBounds, paddleBounds))
    {
        xvel *= -1;
        return true;
    }
    return false;
}