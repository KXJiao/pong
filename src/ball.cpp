#include "ball.h"
#include <stdlib.h>
#include <SDL2_gfxPrimitives.h>

Ball::Ball(int r, int x, int y)
{
    radius = r;
    xpos = x;
    ypos = y;

    startX = x;
    startY = y;

    scoring = 0;

    // Randomly move ball in a direction
    int random = rand() % 10;
    int direction = 1;
    if (random < 5)
    {
        direction = -1;
    }

    xvel = 10 * direction;
    yvel = -6 + (rand() % 12);

    maxvel = 20;
};

void Ball::move(int windowHeight, int windowWidth)
{
    int rand_pert = rand() % 3; // Degree of perturbation (on wall bounce)

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

    // Random perturbation
    if ((ypos < 0) || (ypos > windowHeight))
    {
        yvel *= -1;
        // Make sure ball doesn't bounce multiple times
        if (yvel < 0)
        {
            ypos -= 5;
        }
        else
        {
            ypos += 5;
        }

        // Apply perturbation to x velocity
        if (getDirection() == -1)
        {
            xvel -= rand_pert;
        }
        else
        {
            xvel += rand_pert;
        }
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

    // Make sure ball doesn't become too slow
    if (xvel < 3 && xvel > -3)
    {
        if (getDirection() == -1)
        {
            xvel = -3;
        }
        else
        {
            xvel = 3;
        }
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

int Ball::getDirection()
{
    if (xvel > 0)
    {
        return 1;
    }
    else if (xvel < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void Ball::reset()
{
    xvel = 0;
    yvel = 0;
    SDL_Delay(1000);

    xpos = startX;
    ypos = startY;

    // Randomly move ball in a direction
    int random = rand() % 10;
    int direction = 1;
    if (random < 5)
    {
        direction = -1;
    }

    xvel = 10 * direction;
    yvel = -6 + (rand() % 12);
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

        // Displace slightly to prevent multibouncing
        if (getDirection() == -1)
        {
            xpos -= 5;
            xvel -= 1; // Speed up horizontal speed slightly
        }
        else
        {
            xpos += 5;
            xvel += 1;
        }

        int rand_pert = -3 + (rand() % 6); // Degree of perturbation (on paddle bounce)
        yvel += rand_pert;

        return true;
    }
    return false;
}

void Ball::render(SDL_Renderer *renderer)
{
    // Actually a box to make intersections easier to calculate
    boxRGBA(renderer, xpos, ypos, xpos + radius, ypos + radius, 0, 0, 0, 128);
}
