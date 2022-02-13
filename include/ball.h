#include <SDL.h>
#ifndef _BALL_H_
#define _BALL_H_

class Ball
{
public:
    Ball(int, int, int);
    void move();
    void render(SDL_Renderer *renderer);

private:
    int radius;

    int xpos;
    int ypos;

    int xvel;
    int yvel;

    void paddleBounce();
};

#endif /* _BALL_H_ */