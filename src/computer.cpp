#include "computer.h"

Computer::Computer(Paddle *paddle)
{
    aiPaddle = paddle;
};

void Computer::controlPaddle(Ball *ball)
{
    int currentBallY = ball->getY();
    int currentPaddleY = aiPaddle->getY();

    if (currentPaddleY + aiPaddle->getHeight() < currentBallY)
    {
        aiPaddle->down();
    }
    else if (currentPaddleY > currentBallY)
    {
        aiPaddle->up();
    }
}