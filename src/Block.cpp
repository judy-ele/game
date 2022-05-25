#include "Block.h"
#include "time.h"
#include "random"

using namespace std;

Block::Block()
{
    rock_number = 3;
    x.resize(3);
    y.resize(3);
    y.at(0) = -40;
    dy.resize(3);
    dy.at(0) = 5;
    collider.resize(3);
}

Block::~Block()
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

void Block::loadMedia(SDL_Renderer* renderer)
{
    loadFromFile("assets/sprites/Rock.png", renderer);
}

void Block::update(int &score, bool &is_hitting_wall)
{

    srand((int) time(0));
//    if(is_hitting_wall == true) //when bird hit wall, generate randomly-positioned spikes

    setRockNumber(score);

    for(int i = 0; i < rock_number; i++)
    {

        if (y.at(i) >= SCREEN_HEIGHT)
        {
            x.at(i) = 40 + rand() % (9)*height.at(0);
            dy.at(i) = 0.5;
            y.at(i) = (0);
        }
    }
//    }
    for(int i = 0 ; i < rock_number; i++)
        y.at(i) = y.at(i) + dy.at(i);
    for(int i = 0; i < rock_number; i++)
        dy.at(i) += 0;
}

void Block::setRockNumber(int &score)
{
    if(score <= 30)
        rock_number = 0;
    else if(score <= 60)
        rock_number = 1;
    else if(score <= 100)
        rock_number = 2;
    else
        rock_number = 3;

    rock_number = 3;
}

int Block::getRockNumber()
{
    return rock_number;
}

void Block::setCollider(int &i)
{
    collider.at(0).x = x.at(i)+11;
    collider.at(0).y = y.at(i)+5;
    collider.at(0).w = 6;
    collider.at(0).h = 13;

    collider.at(1).x = x.at(i)+12;
    collider.at(1).y = y.at(i)+7;
    collider.at(1).w = 16;
    collider.at(1).h = 22;

    collider.at(2).x = x.at(i)+27;
    collider.at(2).y = y.at(i)+7;
    collider.at(2).w = 4;
    collider.at(2).h = 10;
}

void Block::reset()
{
    srand((int) time(0));
    for(int i = 0; i < rock_number; i++)
    {
        x.at(i) = 48 + rand() % (9)*height.at(0);
        y.at(i) = 0;
        dy.at(i) = 0.5;
    }
}
