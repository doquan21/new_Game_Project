#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Function.h"

using namespace std;

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

void showScore(TTF_Font* font, SDL_Renderer* render,string score)
{
    SDL_Color color = {0,0,0,225};
    SDL_Rect scorebar_rect;
    scorebar_rect.x = 320;
    scorebar_rect.y = 75;
    scorebar_rect.w = 90;
    scorebar_rect.h = 50;
    SDL_Surface* surfScore = TTF_RenderText_Solid(font, "Score :", color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(render,surfScore);
    SDL_RenderCopy(render,tex,NULL,&scorebar_rect);
    SDL_FreeSurface(surfScore);
    SDL_DestroyTexture(tex);

    SDL_Rect score_rect;
    score_rect.x = 430;
    score_rect.y = 75;
    score_rect.w = 50;
    score_rect.h = 50;

    surfScore = TTF_RenderText_Solid(font, score.c_str(), color);
    tex = SDL_CreateTextureFromSurface(render,surfScore);
    SDL_RenderCopy(render,tex,NULL,&score_rect);

    SDL_FreeSurface(surfScore);
    SDL_DestroyTexture(tex);
}
