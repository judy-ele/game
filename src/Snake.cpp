#include "Snake.h"

using namespace std;

Snake::Snake()
{
    x.push_back(SCREEN_WIDTH/2.0-26);
    y.push_back(SCREEN_HEIGHT/2.0-76);
    //van toc
    dx = 0;
    dy = 0;

    //gia toc
    ddx = 0.05;
    ddy = 0.3;
    change_press_dx = 2;
    change_press_dy = -7.5;
    is_key_pressed = false;
    //fix loi dap tuong
    invincible = false;
    //set per pixel collider
    collider.resize(3);
}

Snake::~Snake()
{
    x.clear();
    y.clear();
    width.clear();
    height.clear();
    texture.clear();

    x.shrink_to_fit();
    y.shrink_to_fit();
    width.shrink_to_fit();
    height.shrink_to_fit();
    texture.shrink_to_fit();
}

void Snake::loadMedia(SDL_Renderer* renderer)
{
    loadFromFile("assets/sprites/snake5.png", renderer);
    loadFromFile("assets/sprites/snake7.png", renderer);
    loadFromFile("assets/sprites/snake6.png", renderer);
}

void Snake::handleEvent(SDL_Event event, int &status, vector<Mix_Chunk*> sound)
{

    switch (event.key.keysym.sym)
    {
        //bấm sang phải thì nó đi sang phải
    case SDLK_RIGHT:
        status = GOING_RIGHT;
        dx = change_press_dx;
        break;
    case SDLK_LEFT:
        status = GOING_LEFT;
        dx = -change_press_dx;
        break;
    }
}

void Snake::update(int &status, int &score, bool &is_hitting_wall)
{


    x.at(0) += dx;
    if(x.at(0) > SCREEN_WIDTH-48-20)
    {
        x.at(0) = SCREEN_WIDTH-48-20;
        dx *= -1;
        status = GOING_LEFT;
        is_hitting_wall = true; //for playing sound effect
        score++;

    }
    else if(x.at(0) < 18)
    {
        x.at(0) = 18;
        dx *= -1;
        status = GOING_RIGHT;
        is_hitting_wall = true;
        score++;
    }
    else
    {
        is_hitting_wall = false;
    }

    if(y.at(0) >= SCREEN_HEIGHT-70-48)
    {
        y.at(0) = SCREEN_HEIGHT-70-48;
    }
    if(y.at(0) <= 30)
    {
        y.at(0) = 30;
    }

}

void Snake::playSound(vector <Mix_Chunk*> sound, bool & is_hitting_wall)
{
    if(is_key_pressed == true)
    {
        Mix_PlayChannel( -1, sound.at(0), 0 );
        is_key_pressed = false;
    }
    if(is_hitting_wall == true)
    {
        Mix_PlayChannel(-1, sound.at(1), 0);
    }
}

void Snake::pause()
{
    x.at(0) = 18;
    y.at(0) = 24+24; //what is thissss
    dx = 0;
    dy = 0;
    ddx = 0;
    ddy = 0;
    change_press_dx = 0;
    change_press_dy = 0;

}

void Snake::reset()
{
    x.at(0)=(SCREEN_WIDTH/2.0-26);
    y.at(0)=(SCREEN_HEIGHT/2.0-76);
    dx = 0;
    dy = 0;
    ddx = 0.05;
    ddy = 0.3;
    change_press_dx = 2;
    change_press_dy = -7.5;
    is_key_pressed = false;
}

float Snake::getDx()
{
    return dx;
}

float Snake::getDy()
{
    return dy;
}

void Snake::setCollider(int &status)
{
    if(status == GOING_LEFT)
    {
        collider.at(0).x = x.at(0)+10;
        collider.at(0).y = y.at(0)+7;
        collider.at(0).w = 33;
        collider.at(0).h = 12;
        collider.at(1).x = x.at(0);
        collider.at(1).y = y.at(0)+19;
        collider.at(1).w = 48;
        collider.at(1).h = 12;
        collider.at(2).x = x.at(0)+10;
        collider.at(2).y = y.at(0)+31;
        collider.at(2).w = 33;
        collider.at(2).h = 12;
    }
    else if(status == GOING_RIGHT)
    {
        collider.at(0).x = x.at(0)+7;
        collider.at(0).y = y.at(0)+7;
        collider.at(0).w = 33;
        collider.at(0).h = 12;
        collider.at(1).x = x.at(0);
        collider.at(1).y = y.at(0)+19;
        collider.at(1).w = 48;
        collider.at(1).h = 12;
        collider.at(2).x = x.at(0)+7;
        collider.at(2).y = y.at(0)+31;
        collider.at(2).w = 33;
        collider.at(2).h = 12;
    }

}

bool Snake::isInvincible()
{
    return invincible;
}

void Snake::setInvincible(const bool &temp)
{
    invincible = temp;
}

int Snake::getPower()
{
    return power;
}

void Snake::setPower(int &temp)
{
    power = temp;
}
