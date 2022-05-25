#include "Texture.h"

using namespace std;

void Texture::logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << IMG_GetError() << endl;
    if (fatal)
    {
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }
}

void Texture::free(SDL_Texture* texture)
{
    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void Texture::loadFromFile(string path, SDL_Renderer* renderer)
{
    SDL_Texture* new_texture = NULL;
    SDL_Surface* loaded_surface = IMG_Load( path.c_str() );

    if( loaded_surface == NULL )
    {
        logSDLError(cout, "IMG_load", true);
    }
    else
    {
        SDL_SetColorKey( loaded_surface, SDL_TRUE, SDL_MapRGB( loaded_surface->format, 0x00, 0xFF, 0xFF ) );
        new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if( new_texture == NULL )
        {
            logSDLError(cout, "SDL_CreateTextureFromSurface", true);
        }
        else
        {
            width.push_back(loaded_surface->w);
            height.push_back(loaded_surface->h);
        }

        SDL_FreeSurface(loaded_surface);
    }

     texture.push_back(new_texture);
     new_texture = NULL;
}

void Texture::render(int i, int x, int y, int width, int height, SDL_Renderer* renderer, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, width, height};
    SDL_RenderCopyEx(renderer, texture.at(i), NULL, &renderQuad, angle, center, flip);
}

void Texture::setColor(const int &i, Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod( texture.at(i), red, green, blue );
}

float Texture::getX(int i)
{
    return x.at(i);
}

float Texture::getY(int i)
{
    return y.at(i);
}

int Texture::getWidth(int i)
{
    return width.at(i);
}

int Texture::getHeight(int i)
{
    return height.at(i);
}

vector<SDL_Rect> Texture::getCollider()
{
    return collider;
}

bool checkCollision(const vector <SDL_Rect> &a, const vector <SDL_Rect> &b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //tới hộp A
    for( int Abox = 0; Abox < a.size(); Abox++ )
    {
        //tính cạnh hcn A
        leftA = a[ Abox ].x;
        rightA = a[ Abox ].x + a[ Abox ].w;
        topA = a[ Abox ].y;
        bottomA = a[ Abox ].y + a[ Abox ].h;

        //Tới hộp B
        for( int Bbox = 0; Bbox < b.size(); Bbox++ )
        {
            //tính cạnh hcn B
            leftB = b[ Bbox ].x;
            rightB = b[ Bbox ].x + b[ Bbox ].w;
            topB = b[ Bbox ].y;
            bottomB = b[ Bbox ].y + b[ Bbox ].h;

            //nếu không có cạnh A nào nằm ngoài B
            if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) == false )
            {
                //phát hiện va chạm
                return true;
            }
        }
    }

    //Nếu 2 hộp k chạm nhau
    return false;
}

bool checkCollision(const vector <SDL_Rect> &a, const vector <SDL_Rect> &b, const int &cap_bot, const int &cap_top)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //tới hộp A
    for( int Abox = 0; Abox < a.size(); Abox++ )
    {
        //tính cạnh hcn A
        leftA = a[ Abox ].x;
        rightA = a[ Abox ].x + a[ Abox ].w;
        topA = a[ Abox ].y;
        bottomA = a[ Abox ].y + a[ Abox ].h;

        //Tới hộp B
        for( int Bbox = cap_bot; Bbox < cap_top; Bbox++ )
        {
            //tính cạnh hcn B
            leftB = b[ Bbox ].x;
            rightB = b[ Bbox ].x + b[ Bbox ].w;
            topB = b[ Bbox ].y;
            bottomB = b[ Bbox ].y + b[ Bbox ].h;

            //nếu không có hcn A nằm ngoài B
            if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) == false )
            {
                //va chạm A được phát hiện
                return true;
            }
        }
    }

    //Nếu 2 hộp k chạm nhau
    return false;
}
