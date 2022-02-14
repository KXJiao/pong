#ifndef _PADDLE_H_
#define _PADDLE_H_
#include <SDL.h>

class Paddle
{
public:
    Paddle(int, int, int, int);
    void up();
    void down();
    int getHeight();
    int getWidth();
    int getY();
    void render(SDL_Renderer *renderer);

private:
    int height;
    int width;

    int xpos;
    int ypos;
};

#endif /* _PADDLE_H_ */