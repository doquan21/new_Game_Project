#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

SDL_Texture* load_image(string file_path,SDL_Renderer* renderer);

#endif // FUNCTION_H

