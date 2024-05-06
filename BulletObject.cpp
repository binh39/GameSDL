#include "BulletObject.h"

BulletObject :: BulletObject(){
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    bullet_type_ = SPHERE_BULLET;

    x_pos_=0;
    y_pos_=0;
    map_x=0;
    map_y=0;
    goc=0;
}

BulletObject :: ~BulletObject(){
}

bool BulletObject :: LoadImgBullet(SDL_Renderer* des)
{
    if(bullet_type_ == LASER_BULLET)
    {
        return LoadImg("img//LaserBullet.png",des);
    }
    else
    {
        return LoadImg("img//ShpereBullet.png",des);
    }
    return false;
}

void BulletObject :: HandleMove(const int& x_border, const int& y_border, Map& map_data)
{
    map_x = map_data.start_x_;
    map_y = map_data.start_y_;

    rect_.x = x_pos_ - map_x;
    rect_.y = y_pos_ - map_y;

    if(bullet_dir_ == DIR_RIGHT)
    {
        x_pos_ += x_val_;
        rect_.x = x_pos_ - map_x;
        if(rect_.x > x_border) is_move_ = false;
    }
    else if(bullet_dir_ == DIR_LEFT)
    {
        x_pos_ -= x_val_;
        rect_.x = x_pos_ - map_x;
        if(rect_.x < 0) is_move_ = false;
    }
    else if(bullet_dir_ == DIR_UP)
    {
        y_pos_ -=y_val_;
        rect_.y = y_pos_ - map_y;
        if(rect_.y<0) is_move_ = false;
    }
    else if(bullet_dir_ == DIR_UP_LEFT)
    {
        x_pos_ -= x_val_*0.7;
        y_pos_ -= y_val_*0.7;
        rect_.x = x_pos_ - map_x;
        rect_.y = y_pos_ - map_y;
        if(rect_.x < 0 || rect_.y < 0) is_move_ = false;
    }
    else if(bullet_dir_ == DIR_UP_RIGHT)
    {
        x_pos_ += x_val_*0.7;
        y_pos_ -= y_val_*0.7;
        rect_.x = x_pos_ - map_x;
        rect_.y = y_pos_ - map_y;
        if(rect_.x > x_border || rect_.y < 0) is_move_ = false;
    }
    else if(bullet_dir_ == DIR_DOWN_LEFT)
    {
        x_pos_ -= x_val_*0.7;
        y_pos_ += y_val_*0.7;
        rect_.x = x_pos_ - map_x;
        rect_.y = y_pos_ - map_y;
        if(rect_.x < 0 || rect_.y > y_border) is_move_ = false;
    }
    else if(bullet_dir_ == DIR_DOWN_RIGHT)
    {
        x_pos_ += x_val_*0.7;
        y_pos_ += y_val_*0.7;
        rect_.x = x_pos_ - map_x;
        rect_.y = y_pos_ - map_y;
        if(rect_.x > x_border || rect_.y > y_border) is_move_ = false;
    }
}

void BulletObject :: HandleMove2(const int& x_border, const int& y_border, Map& map_data, const float& xPlayer, const float& yPlayer){

    map_x = map_data.start_x_;
    map_y = map_data.start_y_;

    float A = atan( (x_pos_ - xPlayer) / (yPlayer - y_pos_) );

    if(yPlayer >= y_pos_){
        x_pos_ -= x_val_ * sin(A);
        y_pos_ += y_val_ * cos(A);
    }
    else{
        x_pos_ += x_val_ * sin(A);
        y_pos_ -= y_val_ * cos(A);
    }
    rect_.x = x_pos_ - map_x;
    rect_.y = y_pos_ - map_y;
    if(rect_.x < 0 || rect_.y > y_border || rect_.y<0 || rect_.y > y_border) is_move_ = false;
}

