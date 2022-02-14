#include "game.h"

Game::Game(int height, int width)
{
    windowHeight = height;
    windowWidth = width;
    gameStatus = 0;
    player = -1;
};

void Game::startGame(int difficulty, int playerSide)
{
    /**
     * Setup game
     **/

    leftPlayerScore = 0;
    rightPlayerScore = 0;
    player = playerSide;

    int aiLength; // length of computer's paddle
    if (difficulty == 0)
    {
        aiLength = 80;
    }
    else if (difficulty == 1)
    {
        aiLength = 160;
    }
    else if (difficulty == 2)
    {
        aiLength = 240;
    }

    // Decide if player is left or right paddle
    if (player == 0)
    {
        leftPaddle = new Paddle(160, 15, 100, windowHeight / 2 - 80, windowHeight);
        rightPaddle = new Paddle(aiLength, 15, windowWidth - 115, (windowHeight / 2) - (aiLength / 2), windowHeight);
        computer = new Computer(rightPaddle);
    }
    else if (player == 1)
    {
        leftPaddle = new Paddle(aiLength, 15, 100, (windowHeight / 2) - (aiLength / 2), windowHeight);
        rightPaddle = new Paddle(160, 15, windowWidth - 115, windowHeight / 2 - 80, windowHeight);
        computer = new Computer(leftPaddle);
    }

    ball = new Ball(10, windowWidth / 2, windowHeight / 2);

    gameStatus = 1;
}

void Game::playGame()
{
    if (gameStatus == 0) // Game won or lost
    {
        return;
    }
    else // Play Game
    {
        ball->move(windowHeight, windowWidth);
        if (ball->scoring == 1)
        {
            leftPlayerScore += 1;
        }
        else if (ball->scoring == 2)
        {
            rightPlayerScore += 1;
        }

        // Reset ball after score
        if (ball->scoring > 0)
        {
            ball->reset();
            ball->scoring = 0;

            if (leftPlayerScore >= 11 || rightPlayerScore >= 11)
            {
                gameStatus = 0;
            }
        }

        ball->paddleBounce(leftPaddle);
        ball->paddleBounce(rightPaddle);

        computer->controlPaddle(ball, windowWidth);
    }
}

void Game::cleanGame()
{
    gameStatus = -1;
    player = -1;
    delete ball;
    delete computer;
    delete rightPaddle;
    delete leftPaddle;
}

int Game::getGameStatus()
{
    return gameStatus;
}
int Game::getLeftScore()
{
    return leftPlayerScore;
}
int Game::getRightScore()
{
    return rightPlayerScore;
}
int Game::getPlayer()
{
    return player;
}
