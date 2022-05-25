#include "MainMenu.h"

using namespace std;

MainMenu::MainMenu()
{
    frame = 0;
    high_score = 0;
}

MainMenu::~MainMenu()
{
    button.clear();
    button.shrink_to_fit();
    sound.clear();
    sound.shrink_to_fit();
}

void MainMenu::loadMedia(SDL_Renderer* renderer)
{
    background.loadMedia(renderer);
    s_high_score.loadMedia(renderer);

    button.push_back(Button());
    button.at(0).loadFromFile("assets/sprites/text.png", renderer);
    button.at(0).loadFromFile("assets/sprites/message1.png", renderer);
    button.at(0).setPosition((SCREEN_WIDTH-button.at(0).getWidth(0))/2, 50);
    button.at(0).setPosition((SCREEN_WIDTH-button.at(0).getWidth(1))/2, 300);
    button.push_back(Button());
    button.at(1).loadFromFile("assets/sprites/snake5.png", renderer);
    button.at(1).loadFromFile("assets/sprites/snake6.png", renderer);
    button.at(1).loadFromFile("assets/sprites/snake7.png", renderer);
    button.at(1).setPosition((SCREEN_WIDTH-button.at(1).getWidth(0))/2, 220);
    button.push_back(Button());
    button.at(2).loadFromFile("assets/sprites/highscore.png", renderer);
    button.at(2).setPosition(70,400);
    sound.push_back(Mix_LoadWAV("assets/audio/jump.wav"));
}

void MainMenu::handleEvent(SDL_Event event, bool &end_loop, int &mode)
{
    while(SDL_PollEvent(&event))
    {
        button.at(0).handleEvent(event);
        button.at(1).handleEvent(event);
        button.at(2).handleEvent(event);

        switch(event.type)
        {
        case SDL_QUIT:
        {
            end_loop = true;
            break;
        }
        case SDL_KEYUP:
        {
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                end_loop = true;
            }
            else if(event.key.keysym.sym == SDLK_SPACE)
            {
                mode = SNAKE;
            }
            break;
        }
        default:
        {
            break;
        }
        }
    }
}

void MainMenu::update(bool &end_loop, int &mode)
{
    if(button.at(0).isHittingButton() == true || button.at(1).isHittingButton() == true)
    {
        mode = SNAKE;
        Mix_PlayChannel( -1, sound.at(0), 0 );
    }
}

void MainMenu::render(SDL_Renderer* renderer, bool end_loop)
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer,255,0,0,255);

    background.render(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer, 0, NULL, SDL_FLIP_NONE);

    button.at(0).render(0, button.at(0).getX(0), button.at(0).getY(1), button.at(0).getWidth(0), button.at(0).getHeight(0), renderer, 0, NULL, SDL_FLIP_NONE);
   // button.at(0).render(1, button.at(0).getX(1), button.at(0).getY(1), button.at(0).getWidth(1), button.at(0).getHeight(1), renderer, 0, NULL, SDL_FLIP_NONE);

    button.at(1).render(frame/3, button.at(1).getX(0), button.at(1).getY(0), button.at(1).getWidth(0), button.at(1).getHeight(0), renderer, 0, NULL, SDL_FLIP_NONE);
    button.at(2).render(0, button.at(2).getX(0), button.at(2).getY(0), button.at(2).getWidth(0), button.at(2).getHeight(0), renderer, 0, NULL, SDL_FLIP_NONE);

    string score_string = to_string(high_score);        // convert score to string
    for(unsigned int i = 0; i < score_string.length(); i++)
    {
        s_high_score.render(score_string.at(i)-48, (SCREEN_WIDTH-24*score_string.length()-10*(score_string.length()-1))/2 + i*24 + 100, 400,s_high_score.getWidth(score_string.at(i)-48), s_high_score.getHeight(score_string.at(i)-48), renderer, 0, NULL, SDL_FLIP_NONE);
    }
    frame++;
    if(frame/3 >= 3)
        frame = 0;

    SDL_RenderPresent(renderer);
}

void MainMenu::reset()
{
    button.at(0).reset();
    button.at(1).reset();
    button.at(2).reset();

}

void MainMenu::setHighScore(int score)
{
    high_score = score;
}
