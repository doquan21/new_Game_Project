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
    Barrier (){};
    Barrier (int _x,int _y)
    {
        x = _x;
        y = _y;
    }
    void renderBarrier(SDL_Renderer* renderer);


};
#endif // BARRIER_H
