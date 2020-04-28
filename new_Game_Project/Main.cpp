#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Function.h"
#include "Player.h"
#include "Barrier.h"
#include "Health.h"

using namespace std;

const int S_width = 500;
const int S_height = 800;
const string title = "Test SDL game";

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool initSDL();

void waitUntilKeyPressed();

int main(int argc, char* argv[])
{
    //tao window, renderer
    if (initSDL() == false) return 0;


    //tao main menu start && chay menu start
    SDL_Texture* tex = NULL;
    tex = load_image("image/start.png",renderer);
    SDL_RenderCopy(renderer , tex, NULL, NULL);
    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();
    SDL_DestroyTexture(tex);

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

    // tao score
    TTF_Font* font = TTF_OpenFont("score.ttf",50);

    int healthPoint =0;
    long long int countScore =0;
    bool running = true;

    while (running == true)
    {
        //chay background
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
            mainPlayer.pollEvent(event, renderer, nameFilePlayer);
        }

        //in ra score
        countScore+=10;
        string str = to_string(countScore);
        showScore(font, renderer,str);

        //chay barriers
        barrier1.renderBarrier(renderer);
        barrier1.move1();

        barrier2.renderBarrier(renderer);
        barrier2.move2();



        //kiem tra va cham

        if (barrier1.checkCollision(mainPlayer) ) { healthPoint++; cout <<healthPoint<<endl;};
        if (barrier2.checkCollision(mainPlayer) ) { healthPoint++; cout <<healthPoint<<endl;};

        // chay health
        createHealth(healthPoint,renderer);

        SDL_RenderPresent(renderer);


        SDL_RenderClear(renderer);

    }

    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

    TTF_CloseFont(font);

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

void waitUntilKeyPressed()
{
    SDL_Event event;
    while (true) {
        if ( SDL_WaitEvent(&event) != 0 && (event.type == SDL_KEYDOWN || event.type == SDL_QUIT) )
            return;
        SDL_Delay(10);
    }
}

