#ifndef PLAYER_POWER_H
#define PLAYER_POWER_H

#include "CommonFunction.h"
#include "BaseObject.h"

using namespace std;

class PlayerPower : public BaseObject{
public:
    PlayerPower();
    ~PlayerPower();
    void SetNum(const int& num){number_ = num;}
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);

    void InitCrease();
    void Decrease();
private:
    int number_;
    vector<int> pos_list_;

};

class PlayerMoney : public BaseObject{
public:
    PlayerMoney();
    ~PlayerMoney();
    void Init(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetPos(const int& x, const int& y){x_pos = x; y_pos = y;}

private:
    int x_pos;
    int y_pos;
};

#endif // PLAYER_POWER_H
