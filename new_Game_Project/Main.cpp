#include "Game.h"

const int S_width = 500;
const int S_height = 800;
const string title = "Racing Car";

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;
bool initSDL();


int main(int argc, char* argv[])
{
    //tao window, renderer
    if (initSDL() == false) return 0;

    bool is_run=true, playAgain = true;


    while(is_run == true){

    game(renderer);

    while (playAgain)
    {
        if ( SDL_PollEvent(&event) == 0 )
        {
            if (event.type == SDL_QUIT) {is_run = false; playAgain = false;}
            if (event.type == SDL_KEYDOWN) playAgain = false;
        }
        SDL_Delay(10);
    }
    }


    //ket thuc
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

    TTF_Quit();
	IMG_Quit();
	SDL_Quit();
    return 0;
}

bool initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << "Error Init";
        return false;
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, S_width, S_height, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        cout << "Error Create window";
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
    {
        cout << "Error Create renderer";
        return false;
    }

    if (TTF_Init() <0)
    {
        cout << "Error TTF init";
        return false;
    }

    return true;
}

