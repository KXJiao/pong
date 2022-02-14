#include "computer.h"

Computer::Computer(Paddle *paddle)
{
    aiPaddle = paddle;
};

void Computer::controlPaddle(Ball *ball, int windowWidth)
{
    int currentBallX = ball->getX();
    int currentBallY = ball->getY();
    int currentPaddleY = aiPaddle->getY();

    // Check which side paddle is on, then only move when ball is close
    if ((aiPaddle->getX() < (windowWidth / 2) && currentBallX < (windowWidth / 2) - 100) || (aiPaddle->getX() >= (windowWidth / 2) && currentBallX >= (windowWidth / 2) + 100))
    {
        if (currentPaddleY + aiPaddle->getHeight() < currentBallY)
        {
            aiPaddle->down();
        }
        else if (currentPaddleY > currentBallY)
        {
            aiPaddle->up();
        }
    }
}