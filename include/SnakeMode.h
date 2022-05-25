
#ifndef SnakeMode_H
#define SnakeMode_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Block.h"
#include "Score.h"
#include "Snake.h"
#include "Background.h"
#include "Button.h"
#include "constant.h"
#include "MainMenu.h"
#include "time.h"
#include "random"

using namespace std;

class SnakeMode
{
public:
    SnakeMode();
    ~SnakeMode();
    void loadMedia(SDL_Renderer* renderer);

    void handleEvent(SDL_Event event, bool &end_loop, int &mode);
    void update(bool &end_loop, int& mode);
    void playSound();
    void render(SDL_Renderer* renderer, bool end_loop);

    int getScore();
    void reset();

protected:
    Background background;
    Snake snake;
    Block rock;
    Score s_score;

    vector<Mix_Chunk*> sound;
    int score;
    int frame;
    bool is_hitting_wall;
    int status;
    bool playMusic;

private:

};

#endif // SnakeMode_H
