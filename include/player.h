#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "game.h"

class Player
{
public:
    Player(Game *game);
    int playerInput();
    void renderItems(SDL_Renderer *renderer, int, int);

private:
    Game *currentGame;
};

#endif /* _PLAYER_H_ */