// Using SDL and standard IO
#include <SDL.h>
#include <SDL_ttf.h>
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

// Errors
void csci437_error(const std::string &msg)
{
    std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
    exit(0);
}

void csci437_ttf_error(const std::string &msg)
{
    std::cerr << msg << " (" << TTF_GetError() << ")" << std::endl;
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

    // init TTF
    if (TTF_Init() < 0)
        csci437_ttf_error("Unable to initialize TTF!");

    // Small delay to allow the system to create the window.
    SDL_Delay(100);

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        csci437_error("Unable to create renderer!");
}

void renderText(std::string str, int x, int y)
{
    /**
     * Renders given string on the screen at the given coordinates
     **/

    // Load font
    TTF_Font *font = TTF_OpenFont("../resource/Arial.ttf", 50);
    if (font == NULL)
        csci437_error("Unable to open font!");

    // render text
    SDL_Color color = {0, 0, 0};
    SDL_Surface *text = TTF_RenderText_Solid(font, str.c_str(), color);
    if (text == NULL)
        csci437_ttf_error("Unable to render text!");

    // convert to texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text);
    if (texture == NULL)
        csci437_error("Could not create texture from surface!");

    bool red = true, green = true, blue = true;
    float angle = 0;

    SDL_Rect dst = {x, y, text->w, text->h};
    SDL_Point rot = {text->w / 2, text->h / 2};

    SDL_FreeSurface(text);
    text = NULL;

    SDL_SetTextureColorMod(texture, red * 255, green * 255, blue * 255);
    SDL_RenderCopyEx(renderer, texture, NULL, &dst, angle, &rot, SDL_FLIP_NONE);

    // Destroy texture
    SDL_DestroyTexture(texture);
}

void cleanup()
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
    bool running = true;
    game->startGame(1, 0);

    // While application is running
    while (running)
    {
        // Prepare rendering
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Check player input, specifically for exit input
        if (player->playerInput() == 0)
        {
            running = false;
        }

        // Run game
        game->playGame();

        // Render player view and text
        player->renderItems(renderer, SCREEN_HEIGHT, SCREEN_WIDTH);

        renderText(std::to_string(game->getLeftScore()), SCREEN_WIDTH / 2 - 100, 10);
        renderText(std::to_string(game->getRightScore()), SCREEN_WIDTH / 2 + 50, 10);

        if (game->getGameStatus() == 0) // Represents game's end
        {
            if (game->getLeftScore() >= 11)
            {
                renderText("Left Player Wins!", 150, SCREEN_HEIGHT / 2 - 100);
            }
            else if (game->getRightScore() >= 11)
            {
                renderText("Right Player Wins!", 150, SCREEN_HEIGHT / 2 - 100);
            }

            renderText("Press r to restart, q or esc to quit.", 150, SCREEN_HEIGHT / 2);
        }

        // Show rendered items
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    /*** Clean Up ***/
    delete player;
    delete game;
    cleanup();

    // Done.
    return 0;
}
