#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include "ball.h"
#include "paddle.h"
#include <memory>
class Computer
{
public:
    Computer(Paddle *paddle);
    void controlPaddle(Ball *ball, int);

private:
    Paddle *aiPaddle;
    int aiPHeight;
    int aiPWidth;
};

#endif /* _COMPUTER_H_ */