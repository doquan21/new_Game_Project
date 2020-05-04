#include "Game.h"

void game(SDL_Renderer* renderer, vector<int> &highscore,int tempNameBG)
{
    //tao main menu start && chay menu start
    render_image("image/start.png",renderer); // trong header Function.h
    waitUntilKeyPressed();

    //tao man hinh howtoplay
    render_image("image/howtoplay.png",renderer); // trong header Function.h
    waitUntilKeyPressed();

    //tao menu dung 3s
    if (tempNameBG%2 ==0){
        render_image("image/start1.png",renderer);
        SDL_Delay(1000);
        render_image("image/start2.png",renderer);
        SDL_Delay(1000);
        render_image("image/start3.png",renderer);
        SDL_Delay(1000);
    }
    else{
        render_image("image/start4.png",renderer);
        SDL_Delay(1000);
        render_image("image/start5.png",renderer);
        SDL_Delay(1000);
        render_image("image/start6.png",renderer);
        SDL_Delay(1000);
    }

    //tao cac bien
    SDL_Event event;
    Mix_Chunk *sound_effect = Mix_LoadWAV("music/Car Crash.mp3");
    Mix_Music *bg_music = Mix_LoadMUS("music/BGmusic.mp3");
    Mix_PlayMusic(bg_music,-1);

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
    TTF_Font* font = TTF_OpenFont("Roboto.ttf",50);

    int healthPoint =0;
    int countScore =0;
    bool running = true;

    while (running == true)
    {
        SDL_Texture* tex = NULL;
        //chay background
        if (tempNameBG%2==0) tex = load_image("image/BG1.png",renderer);
        else tex = load_image("image/BG2.jpg",renderer);
        SDL_RenderCopy(renderer , tex, NULL, &background_rect);

        //chinh toc do background
        if (countScore < 10000) background_rect.y +=5;
        else background_rect.y +=10;

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
        showScore(font, renderer,str, highscore.back()); //trong header Function.h

        //chay barriers
        barrier1.renderBarrier(renderer);
        barrier1.move1(countScore);

        barrier2.renderBarrier(renderer);
        barrier2.move2(countScore);

        //kiem tra va cham

        if (barrier1.checkCollision(mainPlayer) ) {healthPoint++; Mix_PlayChannel(-1,sound_effect,0);}
        if (barrier2.checkCollision(mainPlayer) ) {healthPoint++; Mix_PlayChannel(-1,sound_effect,0);}

        // chay health
        if (healthPoint ==4)
        {
            running = false;
        }
        else createHealth(healthPoint,renderer); //trong header health.h

        SDL_RenderPresent(renderer);

        SDL_RenderClear(renderer);
    }
    SDL_Delay(200);
    highscore.push_back(countScore);
    // sap xep vector de in highestscore
    sort(highscore.begin(), highscore.end());

    //render gameover menu
    render_image("image/gameover.png",renderer); // trong header Function.h

    SDL_Color color = {255,50,147,225};
    SDL_Rect highest_rect1;
    highest_rect1.x = 320;
    highest_rect1.y = 503;
    highest_rect1.w = 110;
    highest_rect1.h = 40;
    string highestScore = to_string(highscore.back());
    SDL_Surface* surfScore = TTF_RenderText_Solid(font,highestScore.c_str(), color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer,surfScore);
    SDL_RenderCopy(renderer,tex,NULL,&highest_rect1);
    SDL_FreeSurface(surfScore);
    SDL_DestroyTexture(tex);
    SDL_RenderPresent(renderer);

    Mix_HaltMusic();
    Mix_FreeChunk(sound_effect);
    Mix_FreeMusic(bg_music);


    TTF_CloseFont(font);

}
