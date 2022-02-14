#include "player.h"

Player::Player(Game *game)
{
    currentGame = game;
};

int Player::playerInput()
{
    /**
     * Handle user input
     **/

    // Check mouse coords
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (currentGame->getPlayer() == 0)
    {
        if (currentGame->leftPaddle->getY() + (currentGame->leftPaddle->getHeight() / 2) > y + 20)
        {
            currentGame->leftPaddle->up();
        }
        else if (currentGame->leftPaddle->getY() + (currentGame->leftPaddle->getHeight() / 2) < y - 20)
        {
            currentGame->leftPaddle->down();
        }
    }
    else
    {
        if (currentGame->rightPaddle->getY() + (currentGame->rightPaddle->getHeight() / 2) > y + 20)
        {
            currentGame->rightPaddle->up();
        }
        else if (currentGame->rightPaddle->getY() + (currentGame->rightPaddle->getHeight() / 2) < y - 20)
        {
            currentGame->rightPaddle->down();
        }
    }

    SDL_Event e;
    int result = 1;

    // Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {

        switch (e.type)
        {
        case SDL_QUIT: // User requests quit
            currentGame->cleanGame();
            result = 0;
            break;
        case SDL_KEYDOWN: // User presses a key
            if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q)
            {
                currentGame->cleanGame();
                result = 0;
            }

            break;
        default:
            break;
        }
    }
    return result; // return 0 when quitting
}

void Player::renderItems(SDL_Renderer *renderer, int windowHeight, int windowWidth)
{
    lineRGBA(renderer, windowWidth / 2, 0, windowWidth / 2, windowHeight, 0, 0, 0, 128);
    currentGame->leftPaddle->render(renderer);
    currentGame->rightPaddle->render(renderer);
    currentGame->ball->render(renderer);
}