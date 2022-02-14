#ifndef _GAME_H_
#define _GAME_H_
#include "ball.h"
#include "paddle.h"
#include "computer.h"

class Game
{
public:
    Paddle *leftPaddle;
    Paddle *rightPaddle;
    Ball *ball;

    Game(int, int);
    void startGame(int, int); // difficulty (0 - 2), player paddle (0 or 1)
    void playGame();
    void cleanGame();
    int getGameStatus();
    int getLeftScore();
    int getRightScore();
    int getPlayer();

private:
    int windowHeight;
    int windowWidth;

    Computer *computer;
    int gameStatus;
    int leftPlayerScore;
    int rightPlayerScore;
    int player; // which paddle player is controlling: 0 left, 1 right
};

#endif /* _GAME_H_ */