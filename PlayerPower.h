#ifndef PLAYER_POWER_H
#define PLAYER_POWER_H

#include "CommonFunction.h"
#include "BaseObject.h"
#include "graphics.h"

using namespace std;

struct PlayerHeart{
    //vector<Sprite*> heart_list;
    Sprite heart;
    int num_heart=3;

    void SetHeart(const int& num){num_heart = num;}
    void Increase(){num_heart++;}
    void Decrease(){num_heart--;}

    void Init(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
};


#endif // PLAYER_POWER_H
