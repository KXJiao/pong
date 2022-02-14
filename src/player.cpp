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
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                currentGame->cleanGame();
                result = 0;
            }
            else if (e.key.keysym.sym == SDLK_w)
            {
                if (currentGame->getPlayer() == 0)
                {
                    currentGame->leftPaddle->up();
                }
                else
                {
                    currentGame->rightPaddle->up();
                }
            }
            else if (e.key.keysym.sym == SDLK_s)
            {
                if (currentGame->getPlayer() == 0)
                {
                    currentGame->leftPaddle->down();
                }
                else
                {
                    currentGame->rightPaddle->down();
                }
            }

            break;
        default:
            break;
        }
    }
    return result; // return 0 when quitting
}

void Player::renderItems(SDL_Renderer *renderer)
{
    currentGame->leftPaddle->render(renderer);
    currentGame->rightPaddle->render(renderer);
    currentGame->ball->render(renderer);
}