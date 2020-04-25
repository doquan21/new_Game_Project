#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Function.h"
#include "Player.h"
using namespace std;

const int S_width = 300;
const int S_height = 1000;
const string title = "Test SDL game";

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool initSDL();

void waitUntilKeyPressed();
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc, char* argv[])
{
    if (initSDL() == false) return 0;
    bool running = true;
    SDL_Event event;
    Player mainPlayer(125,700);
    string nameFilePlayer = "Player.png";

    while (running == true)
    {

        SDL_Texture* tex = NULL;
        tex = load_image("BG1.png",renderer);
        SDL_RenderCopy(renderer , tex, NULL, NULL);
        SDL_DestroyTexture(tex);


        mainPlayer.renderPlayer(renderer, nameFilePlayer );
        mainPlayer.inside();
        if(SDL_PollEvent(&event))
        {
          mainPlayer.pollEvent(event);
        }


        SDL_RenderPresent(renderer);
    }


    quitSDL(window,renderer);
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

    return true;
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}
