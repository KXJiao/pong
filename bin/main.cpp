// Using SDL and standard IO
#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include "paddle.h"
#include "ball.h"
#include "computer.h"
#include "game.h"
#include "player.h"

// Default screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

// Vars for game
SDL_Window *window;
SDL_Renderer *renderer;

bool running;

void csci437_error(const std::string &msg)
{
    std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
    exit(0);
}

void initSDL(void)
{
    /**
     * Initializes SDL window and renderers
     **/

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        csci437_error("SDL could not initialize!");

    // Create window
    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
        csci437_error("Window could not be created!");

    // Small delay to allow the system to create the window.
    SDL_Delay(100);

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        csci437_error("Unable to create renderer!");
}

void cleanup(void)
{
    /**
     * Cleans up objects and quits
     **/

    // Destroy renderer
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    // Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char **argv)
{
    /*** Initialization ***/
    initSDL();
    Game *game = new Game(SCREEN_HEIGHT, SCREEN_WIDTH);
    Player *player = new Player(game);

    /*** Main Loop ***/
    running = true;
    game->startGame(1, 0);

    // While application is running
    while (running)
    {
        // Prepare rendering
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Check player input
        if (player->playerInput() == 0)
        {
            running = false;
        }

        // Run game
        game->playGame();

        // Render
        player->renderItems(renderer);

        // Show rendered items
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    /*** Clean Up ***/
    cleanup();

    // Done.
    return 0;
}
