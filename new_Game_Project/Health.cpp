#include "Health.h"


void createHealth(TTF_Font* font, int healthPoint, SDL_Renderer* renderer)
{
    //render "Health :"
    SDL_Color color = {0,0,0,225};
    SDL_Rect healthbar_rect;
    healthbar_rect.x = 310;
    healthbar_rect.y = 540;
    healthbar_rect.w = 130;
    healthbar_rect.h = 40;
    SDL_Surface *surfScore = TTF_RenderText_Solid(font, "Health :", color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer,surfScore);
    SDL_RenderCopy(renderer,tex,NULL,&healthbar_rect);
    SDL_FreeSurface(surfScore);
    SDL_DestroyTexture(tex);


    // render thanh mau
    string nameHealth[4] = {"image/health1.png" , "image/health2.png" ,"image/health3.png" ,"image/health4.png" };

    SDL_Rect health_rect;
    health_rect.x = 303;
    health_rect.y = 600;
    health_rect.w = 190;
    health_rect.h = 38;

    tex = load_image(nameHealth[healthPoint], renderer);
    SDL_RenderCopy(renderer,tex,NULL,&health_rect);
    SDL_DestroyTexture(tex);
}
