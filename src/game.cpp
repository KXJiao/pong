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

    int aiLength;
    if (difficulty == 0)
    {
        aiLength = 100;
    }
    else if (difficulty == 1)
    {
        aiLength = 200;
    }
    else if (difficulty == 2)
    {
        aiLength = 300;
    }

    if (player == 0)
    {
        leftPaddle = new Paddle(200, 30, 100, 50);
        rightPaddle = new Paddle(aiLength, 30, windowWidth - 130, 50);
        computer = new Computer(rightPaddle);
    }
    else if (player == 1)
    {
        leftPaddle = new Paddle(aiLength, 30, 100, 50);
        rightPaddle = new Paddle(200, 30, windowWidth - 130, 50);
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

    ball->move();
    computer->controlPaddle(ball);
}

void Game::cleanGame()
{
    gameStatus = 0;
    player = -1;
    delete leftPaddle;
    delete rightPaddle;
    delete computer;
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
