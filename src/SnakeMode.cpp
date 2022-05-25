#include "SnakeMode.h"

using namespace std;

SnakeMode::SnakeMode()
{
    frame = 0;
    is_hitting_wall = false;
    status = GOING_RIGHT;
    score = 0;
    playMusic = false;
}

SnakeMode::~SnakeMode()
{

    sound.clear();
    sound.shrink_to_fit();
}

void SnakeMode::loadMedia(SDL_Renderer* renderer)
{
    background.loadMedia(renderer);
    snake.loadMedia(renderer);
    s_score.loadMedia(renderer);
    rock.loadMedia(renderer);

    sound.push_back(Mix_LoadWAV("assets/audio/jump.wav"));
    sound.push_back(Mix_LoadWAV("assets/audio/point.wav"));
    sound.push_back(Mix_LoadWAV("assets/audio/dead.wav"));
    sound.push_back(Mix_LoadWAV("assets/audio/candy.wav"));

}

void SnakeMode::handleEvent(SDL_Event event, bool& end_loop, int &mode)
{
    if(status != DEATH)
    {
        while(SDL_PollEvent(&event))
        {
            snake.handleEvent(event, status, sound);
            switch(event.type)
            {
            case SDL_QUIT:
            {
                end_loop = true;
                break;
            }
            case SDL_KEYUP:
            {
                if(event.key.keysym.sym==SDLK_ESCAPE)
                {
                    status = DEATH;
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
    else if(status == DEATH)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
            {
                end_loop = true;
                break;
            }
            case SDL_KEYUP:
            {
                if(event.key.keysym.sym==SDLK_ESCAPE)
                {
                    status = DEATH;
                }
                else if(event.key.keysym.sym==SDLK_SPACE)
                {
                    mode = MENU;
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
                mode = MENU;
            default:
            {
                break;
            }
            }
        }
    }
}

void SnakeMode::update(bool &end_loop, int &mode)
{
    snake.update(status, score, is_hitting_wall);
    rock.update(score, is_hitting_wall);

    for(int i = 0; i < rock.getRockNumber(); i++)
    {
        snake.setCollider(status);
        rock.setCollider(i);
        if(checkCollision(snake.getCollider(), rock.getCollider()) == true)
        {
            if(snake.isInvincible() == false)
            {
                status =  DEATH;
            }
        }
    }

    if(is_hitting_wall == true)
    {
        snake.setInvincible(false);
    }

    if(snake.getY(0) == 30 || snake.getY(0) == SCREEN_HEIGHT-48-70)
    {
        status = DEATH;
    }
    if(status == DEATH)
    {
        snake.pause();
        if (playMusic == false)
        {
            Mix_PlayChannel( -1, sound.at(2), 0 ); //only play once
            playMusic = true;
        }
    }
    else
    {
        playMusic = false;
    }

}

void SnakeMode::playSound()
{
    snake.playSound(sound, is_hitting_wall);
}

void SnakeMode::render(SDL_Renderer* renderer, bool end_loop)
{
    srand((int) time(0));
    if(!end_loop)
    {
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        if(score%5 == 0)
        {
            int temp1 = 200+ rand()%50;
            int temp2 = 200+ rand()%50;
            int temp3 = 200+ rand()%50;
            background.setColor(0, temp1, temp2, temp3);
            background.setColor(1, temp1, temp2, temp3);
            rock.setColor(0, temp1, temp2, temp3);
        }
        if(score == 0)
        {
            background.setColor(0, 255, 255, 255);
            background.setColor(1, 255, 255, 255);
            rock.setColor(0, 255, 255, 255);
        }
        if(status == GOING_RIGHT)
        {
            background.render(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer, 0, NULL, SDL_FLIP_NONE);

            if(snake.isInvincible() == true)
            {
                snake.render(9, snake.getX(0)-12, snake.getY(0)-15, snake.getWidth(9), snake.getHeight(9), renderer, 0, NULL,SDL_FLIP_NONE);
            }

            snake.render(frame/3, snake.getX(0), snake.getY(0), snake.getWidth(0), snake.getHeight(0), renderer, 0, NULL,SDL_FLIP_NONE);

            for(int i = 0; i < rock.getRockNumber(); i++)
            {
                rock.render(0, rock.getX(i), rock.getY(i), rock.getWidth(0), rock.getHeight(0), renderer, 0, NULL, SDL_FLIP_NONE);

            }
        }
        else if(status == GOING_LEFT)
        {
            background.render(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer, 0, NULL, SDL_FLIP_NONE);

            if(snake.isInvincible() == true)
            {
                snake.render(9, snake.getX(0)-12, snake.getY(0)-15, snake.getWidth(9), snake.getHeight(9), renderer, 0, NULL,SDL_FLIP_NONE);
            }
            snake.render(frame/3, snake.getX(0), snake.getY(0), snake.getWidth(0), snake.getHeight(0), renderer, 0, NULL,SDL_FLIP_HORIZONTAL);

            for(int i = 0; i < rock.getRockNumber(); i++)
            {
                rock.render(0, rock.getX(i), rock.getY(i), rock.getWidth(0), rock.getHeight(0), renderer, 0, NULL, SDL_FLIP_NONE);

            }
        }
        else if(status >= DEATH)
        {
            background.render(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer, 0, NULL, SDL_FLIP_NONE);
            background.render(1, (SCREEN_WIDTH-background.getWidth(1))/2, (SCREEN_HEIGHT-background.getHeight(1))/2-50, background.getWidth(1), background.getHeight(1), renderer, 0, NULL, SDL_FLIP_NONE);
        }
        s_score.renderScore(renderer, score);
        frame++;
        if(frame/3 >= 3)
            frame = 0;

        SDL_RenderPresent(renderer);
        if (status >= DEATH)
        {
            SDL_Delay(1000);
        }
    }
}

int SnakeMode::getScore()
{
    return score;
}

void SnakeMode::reset()
{
    snake.reset();
    rock.reset();
    frame = 0;
    is_hitting_wall = false;
    status = GOING_RIGHT;
    score = 0;
    playMusic = false;
}
