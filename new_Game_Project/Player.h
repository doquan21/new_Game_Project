#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;

struct Player{
    int x;
    int y;
    int step =100;
    Player () {};
    Player (int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    void renderPlayer(SDL_Renderer* renderer,string file_path);

    void inside();

    void pollEvent(SDL_Event event,SDL_Renderer* renderer,Player mainPlayer);
};

#endif // MAINPLAYER_H

