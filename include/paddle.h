#include <SDL.h>
#ifndef _PADDLE_H_
#define _PADDLE_H_
class Paddle
{
public:
    Paddle(int, int, int, int);
    void up();
    void down();
    void render(SDL_Renderer *renderer);

private:
    int height;
    int width;

    int xpos;
    int ypos;
};

#endif /* _PADDLE_H_ */