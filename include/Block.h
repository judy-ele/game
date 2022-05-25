#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Texture.h"
#include "constant.h"

using namespace std;

class Block: public Texture
{
public:
    Block();
    ~Block();

    void loadMedia(SDL_Renderer* renderer);
    void update(int &score, bool &is_hitting_wall);
    void setRockNumber(int &);

    void setCollider(int &);
    void reset();

    int getRockNumber();

protected:
    vector <float> dy;
    int rock_number;

private:

};

#endif // BLOCK_H
