#ifndef _BALL_H_
#define _BALL_H_
#include <SDL.h>

class Ball
{
public:
    Ball(int, int, int);
    void move();
    int getX();
    int getY();
    void render(SDL_Renderer *renderer);

private:
    int radius;

    int xpos;
    int ypos;

    int xvel;
    int yvel;

    int maxvel;

    void paddleBounce();
};

#endif /* _BALL_H_ */