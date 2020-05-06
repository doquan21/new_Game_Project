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

    //tao cac bien event, music, chunk
    SDL_Event event;
    Mix_Chunk *crash_sound_effect = Mix_LoadWAV("music/Car Crash.mp3");
    Mix_Chunk *speedup_sound_effect = Mix_LoadWAV("music/Speedup.mp3");
    Mix_Chunk *coinCollect_sound_effect = Mix_LoadWAV("music/Coin collect.mp3");
    Mix_Music *bg_music = Mix_LoadMUS("music/BGmusic.mp3");
    Mix_PlayMusic(bg_music,-1);

    // tao background
    SDL_Rect background_rect;
    background_rect.x = 0;
    background_rect.y = -3200;
    background_rect.h = 4000;
    background_rect.w = 500;


    // tao nhan vat
    Player mainPlayer(125,650);
    string nameFilePlayer = "image/Player.png";

    // tao rao chan
    Barrier barrier1(10,0);
    Barrier barrier2(110,0);

    // tao coin
    SDL_Rect coin_rect = {0,-100,50,60};

    // tao font score
    TTF_Font* font = TTF_OpenFont("Roboto.ttf",50);

    int healthPoint =0;
    int countScore =0;
    bool running = true;

    while (running)
    {
        SDL_Texture* tex = NULL;
        int random = rand()%3;
        //chay background
        if (tempNameBG%2==0) tex = load_image("image/BG1.png",renderer);
        else tex = load_image("image/BG2.jpg",renderer);
        SDL_RenderCopy(renderer , tex, NULL, &background_rect);

        //chinh toc do background
        if (countScore == 20000) Mix_PlayChannel(-1,speedup_sound_effect,0);
        if (countScore < 20000) background_rect.y +=5;
        else background_rect.y +=10;

        if (background_rect.y > 0) background_rect.y =-3200;
        SDL_DestroyTexture(tex);

        //chay mainplayer
        mainPlayer.renderPlayer(renderer, nameFilePlayer );
        mainPlayer.inside();
        if(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) running = false;
            mainPlayer.pollEvent(event, renderer, nameFilePlayer);
        }

        //chay coin
        tex = load_image("image/coin.png" ,renderer);
        SDL_RenderCopy(renderer , tex, NULL, &coin_rect);
        SDL_DestroyTexture(tex);
        if (running)
        {
            if (coin_rect.y ==-100)
            {
                if (random == 0) coin_rect.x =25;
                else if (random == 1) coin_rect.x =125;
                else if (random == 2) coin_rect.x =225;
            }
            coin_rect.y += 10;
            if (coin_rect.y > 800) coin_rect.y = -100;

            //collision coin vs player
            if (coin_rect.x == mainPlayer.x && (coin_rect.y +coin_rect.h) > 670 && (coin_rect.y +coin_rect.h) < (670 +85)) //85 la mainplayer.h
            {
                coin_rect.y = -100;
                Mix_PlayChannel(-1,coinCollect_sound_effect,0);
                countScore += 1000;
            }
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

        if (barrier1.checkCollision(mainPlayer) ) {healthPoint++; Mix_PlayChannel(-1,crash_sound_effect,0);}
        if (barrier2.checkCollision(mainPlayer) ) {healthPoint++; Mix_PlayChannel(-1,crash_sound_effect,0);}

        // chay health
        if (healthPoint ==4)
        {
            running = false;
        }
        else createHealth(font,healthPoint,renderer); //trong header health.h

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }

    Mix_VolumeChunk(speedup_sound_effect,0);
    SDL_Delay(200);
    highscore.push_back(countScore);
    // sap xep vector de in highestscore
    sort(highscore.begin(), highscore.end());

    //render gameover menu
    render_image("image/gameover.png",renderer); // trong header Function.h
    //render highest score:
    SDL_Color color = {255,50,147,225};
    SDL_Rect highest_rect1 = {320,503,110,40};
    string highestScore = to_string(highscore.back());
    SDL_Surface* surfScore = TTF_RenderText_Solid(font,highestScore.c_str(), color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer,surfScore);
    SDL_RenderCopy(renderer,tex,NULL,&highest_rect1);
    SDL_FreeSurface(surfScore);
    SDL_DestroyTexture(tex);
    SDL_RenderPresent(renderer);

    //ket thuc
    Mix_HaltMusic();
    Mix_FreeChunk(crash_sound_effect);
    Mix_FreeChunk(speedup_sound_effect);
    Mix_FreeMusic(bg_music);


    TTF_CloseFont(font);

}
