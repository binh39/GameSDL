#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include <bits/stdc++.h>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "graphics.h"
#include "BulletObject.h"
#include "ExplosionObject.h"

#define GRAVITY_SPEED 1
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 9
#define PLAYER_JUMP_VAL 13
#define PLAYER_JETPACK 1

using namespace std;

class MainObject : public BaseObject
{
public:
    string RunR;
    string RunL;
    string JumpR;
    string JumpL;
    bool jetpack = false;

    MainObject();
    ~MainObject();

    enum WalkType
    {
        WALK_NONE = 0,
        WALK_RIGHT = 1,
        WALK_LEFT = 2,
    };

    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* gun_sound, Graphics& graphics);
    void set_clips();

    void DoPlayer(Map& map_data, SDL_Renderer* screen, int &num_live, Graphics& graphics, Mix_Chunk* chunk);
    void CheckToMap(Map& map_data, SDL_Renderer* screen, int& num_live, Graphics& graphics, Mix_Chunk* chunk);

    void SetMapXY(const int map_x, const int map_y){map_x_ = map_x; map_y_ = map_y;}
    void CenterEntityOnMap(Map& map_data);
    void SelectCharacter(int choose);
    void UpdateImagePlayer(SDL_Renderer* des);
    SDL_Rect GetRectFrame();

    float get_x_pos(){return x_pos_;}
    float get_y_pos(){return y_pos_;}

    void set_bullet_list(vector<BulletObject*> bullet_list){ p_bullet_list_ = bullet_list;}
    vector<BulletObject*> get_bullet_list() const {return p_bullet_list_;}
    void HandleBullet(SDL_Renderer* des, Map& map_data);
    void RemoveBullet(const int& idx);
    void IncreaseMoney();
    int GetMoneyCount() const {return money_count;}
    bool CollectItem(const Sprite& item);
    bool GetIsCup(){return is_cup;}
    void Vitri(){cout<<x_pos_<<" "<<y_pos_<<endl;}
    void set_come_back_time(const int& cb_time){come_back_time_ = cb_time;}
    void Super(SDL_Renderer* screen, Graphics& graphics, Mix_Chunk* chunk);
    void Nhay(){y_val_ = -5;}
    void Bay(){y_val_ = -27; on_ground_=false;}
    void Khong(){on_ground_ = false;}
    void Plate(){on_ground_ = true; is_on_plate = true;}
    void UnPlate(){is_on_plate = false;}
    void MoveWithPlate(const int& dx);
    void SetBegin();
    void UnSuper(string runR, string runL, string jumpL, string jumpR);

private:
    bool is_cup = false;
    bool is_on_plate = false;
    bool gun = false;

    int money_count;
    vector<BulletObject*> p_bullet_list_;

    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[12];

    Input input_type_;
    int frame_;
    int status_;
    bool on_ground_;
    bool no_key_ = true;

    int map_x_;
    int map_y_;

    int come_back_time_;
};

struct PlayerHeart{
    Sprite heart;
    int num_heart = HEART;

    void SetHeart(const int& num){num_heart = num;}
    void Increase(){num_heart++;}
    void Decrease(){num_heart--;}

    void Init(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
};

#endif // MAIN_OBJECT_H
