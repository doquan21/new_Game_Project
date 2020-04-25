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

