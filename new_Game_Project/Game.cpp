#include "Game.h"

void game(SDL_Renderer* renderer)
{
    //tao main menu start && chay menu start
    render_image("image/start.png",renderer); // trong header Function.h
    waitUntilKeyPressed();

    //tao man hinh howtoplay
    render_image("image/howtoplay.png",renderer); // trong header Function.h
    waitUntilKeyPressed();

    //tao menu dung 3s
    render_image("image/start1.png",renderer);
    SDL_Delay(1000);
    render_image("image/start2.png",renderer);
    SDL_Delay(1000);
    render_image("image/start3.png",renderer);
    SDL_Delay(1000);

    //tao event
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

    // tao font score
    TTF_Font* font = TTF_OpenFont("score.ttf",50);

    int healthPoint =0;
    long long int countScore =0, highestScore =0;
    bool running = true;

    while (running == true)
    {
        SDL_Texture* tex = NULL;
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
        string str = to_string(countScore); //cast int to string
        showScore(font, renderer,str); //trong header Function.h

        //chay barriers
        barrier1.renderBarrier(renderer);
        barrier1.move1();

        barrier2.renderBarrier(renderer);
        barrier2.move2();

        //kiem tra va cham

        if (barrier1.checkCollision(mainPlayer) ) { healthPoint++; cout <<healthPoint<<endl;};
        if (barrier2.checkCollision(mainPlayer) ) { healthPoint++; cout <<healthPoint<<endl;};

        // chay health
        if (healthPoint ==4)
        {
            running = false;
            highestScore =countScore;
        }
        else createHealth(healthPoint,renderer); //trong header health.h

        SDL_RenderPresent(renderer);

        SDL_RenderClear(renderer);
        if (healthPoint ==3)
        {
            running = false;
            highestScore =countScore;
        }
    }
    cout << highestScore;
    //SDL_Delay(1000);
    render_image("image/gameover.png",renderer); // trong header Function.h

    TTF_CloseFont(font);

}
