#include <memory>
#include "computer.h"

std::unique_ptr<Paddle> paddleAI;

Computer::Computer(int height, int width)
{
    aiPHeight = height;
    aiPWidth = width;

    paddleAI = std::make_unique<Paddle>(aiPHeight, aiPWidth, 900, 500); // change hard code to proper later
};

void Computer::controlPaddle(Ball ball, SDL_Renderer *renderer)
{
    int currentBallY = ball.getY();
    int currentPaddleY = paddleAI->getY();

    if (currentPaddleY + aiPHeight < currentBallY)
    {
        paddleAI->down();
    }
    else if (currentPaddleY > currentBallY)
    {
        paddleAI->up();
    }
    paddleAI->render(renderer);
}