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

    if (player == 0)
    {
        leftPaddle = new Paddle(160, 15, 100, windowHeight / 2 - 80);
        rightPaddle = new Paddle(aiLength, 15, windowWidth - 115, (windowHeight / 2) - (aiLength / 2));
        computer = new Computer(rightPaddle);
    }
    else if (player == 1)
    {
        leftPaddle = new Paddle(aiLength, 15, 100, (windowHeight / 2) - (aiLength / 2));
        rightPaddle = new Paddle(160, 15, windowWidth - 115, windowHeight / 2 - 80);
        computer = new Computer(leftPaddle);
    }

    ball = new Ball(10, windowHeight / 2, windowWidth / 2);

    gameStatus = 1;
}

void Game::playGame()
{
    if (gameStatus == 0)
    {
        return;
    }

    ball->move(windowHeight, windowWidth);
    ball->paddleBounce(leftPaddle);
    ball->paddleBounce(rightPaddle);

    computer->controlPaddle(ball);
}

void Game::cleanGame()
{
    gameStatus = 0;
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
