// Using SDL and standard IO
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <stdio.h>

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

void doInput(void)
{
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
            break;
        default:
            break;
        }
    }
}

void prepareScene(void)
{
    SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
    SDL_RenderClear(renderer);
}

void presentScene(void)
{
    SDL_RenderPresent(renderer);
}

void cleanup(void)
{
    // Destroy renderer
    SDL_DestroyRenderer(renderer);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char **argv)
{
    /*** Initialization ***/
    initSDL();

    /*** Main Loop ***/
    running = true;

    // While application is running
    while (running)
    {
        prepareScene();
        doInput();
        presentScene();
    }

    /*** Clean Up ***/
    cleanup();

    // Done.
    return 0;
}
