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
    void render(SDL_Renderer *renderer);
    bool paddleBounce(Paddle *paddle);

private:
    int radius;

    int xpos;
    int ypos;

    int xvel;
    int yvel;

    int maxvel;
};

#endif /* _BALL_H_ */