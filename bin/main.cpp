// Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>

// Default screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

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

int main(int argc, char **argv)
{
    /*** Initialization ***/

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        csci437_error("SDL could not initialize!");

    // Create window
    SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
        csci437_error("Window could not be created!");

    // init TTF
    if (TTF_Init() < 0)
        csci437_ttf_error("Unable to initialize TTF!");

    // Small delay to allow the system to create the window.
    SDL_Delay(100);

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        csci437_error("Unable to create renderer!");

    /*** Render Text ***/

    // Load font
    TTF_Font *font = TTF_OpenFont("../resource/Arial.ttf", 50);
    if (font == NULL)
        csci437_error("Unable to open font!");

    // render text
    SDL_Color color = {255, 255, 255};
    SDL_Surface *text = TTF_RenderText_Solid(font, "Help Me", color);
    if (text == NULL)
        csci437_ttf_error("Unable to render text!");

    // convert to texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text);
    if (texture == NULL)
        csci437_error("Could not create texture from surface!");

    SDL_Rect dst = {(SCREEN_WIDTH - text->w) / 2, (SCREEN_HEIGHT - text->h) / 2, text->w, text->h};
    SDL_Point rot = {text->w / 2, text->h / 2};

    // delete image
    SDL_FreeSurface(text);
    text = NULL;

    /*** Main Loop ***/
    bool running = true;
    SDL_Event e;

    // While application is running
    while (running)
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // User requests quit
            if (e.type == SDL_QUIT)
                running = false;

            // User presses a key
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_q)
                    running = false;
            }

            // render text and bo
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderCopyEx(renderer, texture, NULL, &dst, 0, &rot, SDL_FLIP_NONE);

            boxRGBA(renderer, 30, 50, 330, 250, 255, 0, 0, 128);
            rectangleRGBA(renderer, 30, 50, 330, 250, 255, 255, 255, 255);

            boxRGBA(renderer, 500, 500, 800, 700, 255, 0, 0, 128);

            SDL_RenderPresent(renderer);

            // Update the surface
            SDL_UpdateWindowSurface(window);
        }
    }

    /*** Clean Up ***/

    // Destroy texture
    SDL_DestroyTexture(texture);

    // Destroy renderer
    SDL_DestroyRenderer(renderer);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    // Done.
    return 0;
}