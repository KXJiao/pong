#ifndef _BALL_H_
#define _BALL_H_
#include <SDL.h>
#include "paddle.h"

class Ball
{
public:
    int scoring;
    Ball(int, int, int);
    void move(int, int);
    int getX();
    int getY();
    int getDirection(); // left -1, right 1
    void reset();
    bool paddleBounce(Paddle *paddle);
    void render(SDL_Renderer *renderer);

private:
    int radius;

    int xpos;
    int ypos;

    int startX;
    int startY;

    int xvel;
    int yvel;

    int maxvel;
};

#endif /* _BALL_H_ */