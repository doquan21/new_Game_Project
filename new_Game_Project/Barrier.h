#ifndef BARRIER_H
#define BARRIER_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;

struct Barrier
{
    int x;
    int y;
    int posNameBarrier = 0;
    int posBarrier = 1;
    Barrier (){};
    Barrier (int _x,int _y)
    {
        x = _x;
        y = _y;
    }
    void renderBarrier(SDL_Renderer* renderer);

    void move1();

    void move2();
};
#endif // BARRIER_H
