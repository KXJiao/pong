// Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include "paddle.h"
#include "ball.h"

// Default screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

// Vars for game
SDL_Window *window;
SDL_Renderer *renderer;

Paddle paddle(200, 40, 100, 50);
Ball ball(10, 512, 384);

bool running;

void csci437_error(const std::string &msg)
{
    std::cerr << msg << " (" << SDL_GetError() << ")" << std::endl;
    exit(0);
}

void csci437_img_error(const std::string &msg)
{
    std::cerr << msg << " (" << IMG_GetError() << ")" << std::endl;
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

    // Init Bitmap loading
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
        csci437_img_error("SDL could not initialize bitmap loaders!");

    // Small delay to allow the system to create the window.
    SDL_Delay(100);

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        csci437_error("Unable to create renderer!");
}

void doInput(void)
{
    /**
     * Handle user input
     **/

    SDL_Event e;
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
        case SDL_QUIT: // User requests quit
            running = false;
            break;
        case SDL_KEYDOWN: // User presses a key
            if (e.key.keysym.sym == SDLK_q)
                running = false;
            else if (e.key.keysym.sym == SDLK_w)
            {
                paddle.up();
            }
            else if (e.key.keysym.sym == SDLK_s)
            {
                paddle.down();
            }

            break;
        default:
            break;
        }
    }
}

SDL_Texture *loadTexture(std::string filename)
{
    /**
     * Loads image from file as texture
     **/

    SDL_Texture *texture;
    texture = IMG_LoadTexture(renderer, filename.c_str());

    return texture;
}

void drawTexture(SDL_Texture *texture, int x, int y)
{
    /**
     * Draws a texture at the given coordinates
     **/

    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void prepareScene(void)
{
    /***
     * Sets up renderer
     **/
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void presentScene(void)
{
    /***
     * Displays items on screen
     **/
    SDL_RenderPresent(renderer);
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

    /*** Main Loop ***/
    running = true;

    int testx = 150;
    int testy = 150;

    // While application is running
    while (running)
    {
        prepareScene();
        doInput();
        ball.move();
        paddle.render(renderer);
        ball.render(renderer);
        presentScene();
        SDL_Delay(16);
    }

    /*** Clean Up ***/
    cleanup();

    // Done.
    return 0;
}
