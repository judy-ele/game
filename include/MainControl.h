#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Score.h"
#include "Background.h"
#include "Button.h"
#include "constant.h"
#include "MainMenu.h"
#include "SnakeMode.h"

using namespace std;

class MainControl
{
public:
    MainControl();
    ~MainControl();
    void logSDLError(ostream& os, const string &msg, bool fatal = false);
    void initializeSDL(string window_title, const int&x, const int& y, const int& width, const int& height, const int& screen_option);
    void setMode();
    void close();

    void reset();

    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;

    bool isEndLoop() const;

    static int getWidth();
    static int getHeight();

protected:
    static int WIDTH;
    static int HEIGHT;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    bool end_loop;
    int mode;
    int high_score;

    MainMenu main_menu;
    SnakeMode snake_mode;
};

#endif // MAINCONTROL_H
