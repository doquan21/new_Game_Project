#include "Barrier.h"
#include "Function.h"

using namespace std;

void Barrier::renderBarrier(SDL_Renderer* renderer)
{
    //string nameBarrier[5] = {""}
    SDL_Texture* block = load_image("image/Barrier_1.png",renderer);
    SDL_Rect block_rect;
    block_rect.x = x;
    block_rect.y = y;
    block_rect.w = 80;
    block_rect.h = 30;
    SDL_RenderCopy(renderer , block, NULL, &block_rect);
    SDL_DestroyTexture(block);
}
