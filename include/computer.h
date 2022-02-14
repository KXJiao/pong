#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include "ball.h"
#include "paddle.h"
class Computer
{
public:
    Computer(int, int);
    void controlPaddle(Ball ball, SDL_Renderer *renderer);

private:
    int aiPHeight;
    int aiPWidth;
};

#endif /* _COMPUTER_H_ */