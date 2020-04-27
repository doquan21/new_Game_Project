#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Function.h"
#include "Player.h"
#include "Barrier.h"
using namespace std;

const int S_width = 500;
const int S_height = 800;
const string title = "Test SDL game";

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool initSDL();

void waitUntilKeyPressed();
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc, char* argv[])
{
    //tao window, renderer
    if (initSDL() == false) return 0;
    bool running = true;
    //
    SDL_Event event;

    // tao background
    SDL_Rect background_rect;
    background_rect.x = 0;
    background_rect.y = -4200;
    background_rect.h = 5000;
    background_rect.w = 500;

    // tao nhan vat
    Player mainPlayer(125,650);
    string nameFilePlayer = "image/Player.png";

    // tao rao chan
    Barrier barrier1(10,0);

    Barrier barrier2(110,0);
    int dem=0;
    while (running == true)
    {
        SDL_RenderClear(renderer);
        //chay background
        SDL_Texture* tex = NULL;
        tex = load_image("image/BG1.png",renderer);
        SDL_RenderCopy(renderer , tex, NULL, &background_rect);
        background_rect.y +=5;
        if (background_rect.y > 0) background_rect.y =-4200;
        SDL_DestroyTexture(tex);

        //chay mainplayer
        mainPlayer.renderPlayer(renderer, nameFilePlayer );
        mainPlayer.inside();
        if(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) running = false;
            mainPlayer.pollEvent(event, renderer, mainPlayer, nameFilePlayer);
        }

        //chay barriers
        barrier1.renderBarrier(renderer);
        barrier1.move1();

        barrier2.renderBarrier(renderer);
        barrier2.move2();
        SDL_RenderPresent(renderer);

        //kiem tra va cham
        dem++;
        if (barrier1.checkCollision(mainPlayer) ) cout <<"yes"<<dem<<endl;
        if (barrier2.checkCollision(mainPlayer) ) cout <<"yes"<<dem<<endl;
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
