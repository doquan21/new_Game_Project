#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Function.h"

using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event event;
    while (true) {
        if ( SDL_WaitEvent(&event) != 0 && (event.type == SDL_KEYDOWN || event.type == SDL_QUIT) )
            return;
        SDL_Delay(10);
    }
}

SDL_Texture* load_image(string file_path,SDL_Renderer* renderer)
{
    SDL_Surface* loadImage = NULL;
    SDL_Texture* tex = NULL;
    loadImage = IMG_Load(file_path.c_str());
    if(loadImage != NULL)
    {
        tex = SDL_CreateTextureFromSurface(renderer, loadImage);
        SDL_FreeSurface(loadImage);

    }
    return tex;
}
void render_image(string file_path,SDL_Renderer* renderer)
{
    SDL_Texture* tex = NULL;
    tex = load_image(file_path.c_str() ,renderer);
    SDL_RenderCopy(renderer , tex, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(tex);

}
void showScore(TTF_Font* font, SDL_Renderer* render,string score)
{
    //render "Score :"
    SDL_Color color = {0,0,0,225};
    SDL_Rect scorebar_rect;
    scorebar_rect.x = 310;
    scorebar_rect.y = 75;
    scorebar_rect.w = 115;
    scorebar_rect.h = 40;
    SDL_Surface* surfScore = TTF_RenderText_Solid(font, "Score :", color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(render,surfScore);
    SDL_RenderCopy(render,tex,NULL,&scorebar_rect);
    SDL_FreeSurface(surfScore);
    SDL_DestroyTexture(tex);

    //render "Health"
    SDL_Rect healthbar_rect;
    healthbar_rect.x = 310;
    healthbar_rect.y = 540;
    healthbar_rect.w = 130;
    healthbar_rect.h = 40;
    surfScore = TTF_RenderText_Solid(font, "Health :", color);
    tex = SDL_CreateTextureFromSurface(render,surfScore);
    SDL_RenderCopy(render,tex,NULL,&healthbar_rect);


    SDL_Rect score_rect;
    score_rect.x = 430;
    score_rect.y = 75;
    score_rect.w = 60;
    score_rect.h = 40;

    surfScore = TTF_RenderText_Solid(font, score.c_str(), color);
    tex = SDL_CreateTextureFromSurface(render,surfScore);
    SDL_RenderCopy(render,tex,NULL,&score_rect);

    SDL_FreeSurface(surfScore);
    SDL_DestroyTexture(tex);
}
