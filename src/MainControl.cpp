#include "MainControl.h"
#include <fstream>
using namespace std;

int MainControl::WIDTH;
int MainControl::HEIGHT;

MainControl::MainControl()
{
    window = NULL;
    renderer = NULL;
    end_loop = false;
    mode = MENU;
    high_score = 0;
}

MainControl::~MainControl()
{

}

void MainControl::logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void MainControl::initializeSDL(string window_title, const int&x, const int& y, const int& width, const int& height, const int& screen_option)
{

    WIDTH = width;
    HEIGHT = height;
    //khoi tao moi thu check loi
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(cout, "SDL_Init", true);
    }

    window = SDL_CreateWindow(window_title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        logSDLError(cout, "SDL_CreateWindow", true);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
    {
        logSDLError(cout, "SDL_CreateRenderer", true);
    }

    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        logSDLError(cout, "IMG_Init", true);
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        logSDLError(cout, "Mix_OpenAudio", true);
    }

    main_menu.loadMedia(renderer);
    snake_mode.loadMedia(renderer);
}

void MainControl::setMode()
{
    ifstream infile ("data.txt");
    if( infile.is_open() )
    {
        infile >> high_score;
    }
    else
    {
        high_score = 0;
    }
    infile.close();
    switch(mode)
    {
    case MENU:
    {
        main_menu.reset();
        while(!end_loop)
        {
            main_menu.setHighScore(high_score);
            main_menu.handleEvent(event, end_loop, mode);
            main_menu.update(end_loop, mode);
            if(mode != MENU)
                break;
            main_menu.render(renderer, end_loop);
        }
        break;
    }
    case SNAKE:
    {
        snake_mode.reset();
        while(!end_loop)
        {
            snake_mode.handleEvent(event, end_loop, mode);
            snake_mode.update(end_loop, mode);
            snake_mode.playSound();
            if(mode != SNAKE)
            {
                reset();
                break;
            }
            snake_mode.render(renderer, end_loop);
            if(high_score < snake_mode.getScore())
            {
                high_score = snake_mode.getScore();
            }
        }
        break;
    }
    }
    ofstream outfile("data.txt");
    if(outfile.is_open())
    {
        outfile << high_score;
    }
    outfile.close();
}

void MainControl::reset()
{
    mode  = MENU;
}

void MainControl::close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

SDL_Window* MainControl::getWindow() const
{
    return window;
}

SDL_Renderer* MainControl::getRenderer()const
{
    return renderer;
}

bool MainControl::isEndLoop() const
{
    return end_loop;
}

int MainControl::getWidth()
{
    return WIDTH;
}

int MainControl::getHeight()
{
    return HEIGHT;
}
