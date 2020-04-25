#include "Barrier.h"
#include "Function.h"

using namespace std;

void Barrier::renderBarrier(SDL_Renderer* renderer)
{
    string nameBarrier[5] = {"image/Barrier_1.png", "image/Barrier_2.png" ,"image/Barrier_3.png"
    , "image/Barrier_4.png", "image/Barrier_5.png"};

    SDL_Texture* block = load_image(nameBarrier[posNameBarrier],renderer);
    SDL_Rect block_rect;
    block_rect.x = x;
    block_rect.y = y;
    block_rect.w = 80;
    block_rect.h = 30;
    SDL_RenderCopy(renderer , block, NULL, &block_rect);
    SDL_DestroyTexture(block);
}

void Barrier::move1()
{
    y += 8;
    if (posBarrier == 1)x = 10;
    else if (posBarrier == 2) x = 210;
    else x = 210;

    if (y > 800)
    {
        y = 0;
        posBarrier++;
        posNameBarrier++;
        if (posBarrier == 3) posBarrier =0;
        if (posNameBarrier ==4) posNameBarrier =0;
    }

}

void Barrier::move2()
{
    y += 10;
    if (posBarrier == 0) x = 10;
    else if (posBarrier == 1) x = 110;
    else if (posBarrier == 2) x = 10;
    else x = 110;

    if (y > 800)
    {
        y = 0;
        posBarrier++;
        posNameBarrier++;
        if (posBarrier == 4) posBarrier =0;
        if (posNameBarrier ==4) posNameBarrier =0;
    }
}
