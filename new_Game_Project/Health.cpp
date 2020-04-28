#include "Health.h"


void createHealth(int healthPoint, SDL_Renderer* renderer)
{
    string nameHealth[4] = {"image/health1.png" , "image/health2.png" ,"image/health3.png" ,"image/health4.png" };

    SDL_Rect health_rect;
    health_rect.x = 303;
    health_rect.y = 600;
    health_rect.w = 190;
    health_rect.h = 38;

    SDL_Texture* tex = load_image(nameHealth[healthPoint], renderer);
    SDL_RenderCopy(renderer,tex,NULL,&health_rect);
    SDL_DestroyTexture(tex);
}
