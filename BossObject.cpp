#include "BossObject.h"

BossObject :: BossObject(){
    boss_life = 10;
    frame_ = 0;
    x_val_=0;
    y_val_=0;
    x_pos_=0;
    y_pos_=0;
    width_frame_=0;
    height_frame_=0;
    think_time_=0;
    map_x_=0;
    map_y_=0;
}

BossObject :: ~BossObject(){

}

void BossObject :: CreateBoss(SDL_Renderer* screen){
    LoadImg(BOSS_IMG, screen);
    heart = IMG_LoadTexture(screen, "img//Heart2.png");
    set_clips();
    int x = MAX_MAP_X*TILE_SIZE - SCREEN_WIDTH*0.8;
    set_xpos(x);
    set_ypos(10);
}

void BossObject :: SetBegin(){
    boss_life = 10;
    int x = MAX_MAP_X*TILE_SIZE - SCREEN_WIDTH*0.8;
    set_xpos(x);
    set_ypos(10);
    bullet_list_.clear();
}

bool BossObject :: LoadImg(string path, SDL_Renderer* screen){
    bool ret = BaseObject :: LoadImg(path, screen);
    if(ret){
        width_frame_ = rect_.w/FRAME_NUM_32;
        height_frame_ = rect_.h;
    }
    return ret;
}

void BossObject :: set_clips(){
    if(width_frame_ >0 && height_frame_>0){
        for(int i=0; i<FRAME_NUM_32; i++){
            frame_clip_[i].x = width_frame_*i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void BossObject :: Show(SDL_Renderer* des){
    if(think_time_ == 0){
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_ = (frame_+1)%FRAME_NUM_32;
    }
    SDL_Rect* currentClip = &frame_clip_[frame_];
    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
    if(currentClip != NULL){
        renderQuad.w = currentClip->w;
        renderQuad.h = currentClip->h;
    }
    SDL_RenderCopy(des, p_object_, currentClip, &renderQuad);
}

void BossObject :: DoPlayer(Map& g_map){
    if(think_time_ == 0)
    {
        x_val_ =0;
        y_val_ += GRAVITY_SPEED;

        if(y_val_ >= MAX_FALL_SPEED) y_val_ = MAX_FALL_SPEED;

        if(input_type_.left_ == 1) x_val_ -= PLAYER_SPEED;
        else if(input_type_.right_ == 1) x_val_ += PLAYER_SPEED;

        if(input_type_.jump_ == 1)
        {
            if(on_ground_ == 1)
            {
                y_val_ = -PLAYER_HIGHT_VAL;
            }
            on_ground_ = 0;
            input_type_.jump_ = 0;
        }
        CheckToMap(g_map);
    }

    if( think_time_ >0)
    {
        think_time_--;
        if(think_time_ == 0) InitPlayer();
    }
}

void BossObject :: InitPlayer(){
    x_val_=0;
    y_val_=0;
    if(x_pos_>256) x_pos_-=256;
    else x_pos_ = 0;

    y_pos_=0;
    think_time_=0;
    input_type_.left_=1;
}

void BossObject :: CheckToMap(Map& map_data)
{
    int x1=0;
    int x2=0;

    int y1=0;
    int y2=0;

    on_ground_=0;

    int test_x = x_pos_;
    int test_y = y_pos_;
    //Check horizontal
    int height_min = height_frame_;

    x1 = (x_pos_ + x_val_)/TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_-1)/TILE_SIZE;

    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_ + height_min- 1)/TILE_SIZE;

    if(x1 >= 0 && x2< MAX_MAP_X && y1 >= 0 && y2<MAX_MAP_Y)
    {
        if(x_val_ > 0)
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if(val1 > BLANK_TILE || val2 > BLANK_TILE)
            {
                x_pos_ = test_x;
                x_val_ =0;
            }

        }
        else if (x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if(val1 > BLANK_TILE || val2 > BLANK_TILE)
            {
                x_pos_ = test_x;
                x_val_ =0;
            }
        }
    }

    //Check vertical
    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_)/TILE_SIZE;
    x2 = (x_pos_ + width_min)/TILE_SIZE;

    y1 = (y_pos_ + y_val_)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1)/TILE_SIZE;

    if( x1>=0 && x2<MAX_MAP_X && y1>=0 && y2 <MAX_MAP_Y)
    {
        if(y_val_>0)
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
            if(val1 > BLANK_TILE || val2 > BLANK_TILE)
            {
                y_pos_ = test_y;
                y_val_ = 0;
                on_ground_ = true;
            }
        }
        else if (y_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if(val1 > BLANK_TILE || val2 > BLANK_TILE)
            {
                y_pos_ = test_y;
                y_val_ = 0;
            }
        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if(x_pos_ < 0)
    {
        x_pos_ =0;
    }
    else if(x_pos_+width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_ - width_frame_ -1;
    }

    if( y_pos_ > map_data.max_y_)
    {
        think_time_ = 60;
    }
}

void BossObject :: InitBullet(SDL_Renderer* screen){
    BulletObject* p_bullet = new BulletObject();
    bool ret = p_bullet->LoadImg("img/Boss//BossBullet.png", screen);
    if(ret){
        p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
        p_bullet->set_is_move(true);
        p_bullet->set_position(x_pos_+10, y_pos_+height_frame_*0.45);
        p_bullet->set_x_val(BOSS_FIRE);
        p_bullet->set_y_val(BOSS_FIRE);
        bullet_list_.push_back(p_bullet);
    }
}

void BossObject :: MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit, Map& map_data, const float& xPlayer, const float& yPlayer, Graphics& graphics, Mix_Chunk* boss_gun){
    if(frame_ == 31){
        InitBullet(des);
        graphics.play(boss_gun);
    }
    for(int i=0; i<bullet_list_.size(); i++){
        BulletObject* p_bullet = bullet_list_[i];
        if(p_bullet!=NULL){
            if(p_bullet->get_is_move()){
                int bullet_distance = x_pos_ +width_frame_ - p_bullet->get_pos_x();
                if(0<bullet_distance && bullet_distance < 9*64){
                    p_bullet->HandleMove2(x_limit, y_limit, map_data, xPlayer, yPlayer);
                    p_bullet->Render(des);
                }
            }
            else{
                p_bullet->Free();
                bullet_list_.erase(bullet_list_.begin()+i);
            }
        }
    }
}

void BossObject :: RemoveBullet(const int& idx){
    int size = bullet_list_.size();
    if( 0< size && idx <size){
        BulletObject* p_bullet = bullet_list_[idx];
        p_bullet->SetRect(-10,-10);
        bullet_list_.erase(bullet_list_.begin()+idx);
        if(p_bullet){ delete p_bullet;  p_bullet=NULL;}
    }
}

void BossObject :: ClearBullet(){
    int n = bullet_list_.size();
    for(int i=n-1 ; i>=0 ; i--){
        BulletObject* p_bullet = bullet_list_[i];
        bullet_list_.pop_back();
        if(p_bullet){
            delete p_bullet;
            p_bullet = NULL;
        }
    }
    bullet_list_.clear();
}

bool BossObject :: IsLive(){
    if(boss_life>0) return true;
    return false;
}

SDL_Rect BossObject :: GetRectFrame(){
    SDL_Rect rect = {rect_.x, rect_.y, width_frame_, height_frame_};
    return rect;
}

void BossObject :: ShowHeart(SDL_Renderer* screen, Map& map_data){
    for(int i=0; i<boss_life;i++){
        int x = x_pos_ - map_data.start_x_;
        int y = y_pos_ - map_data.start_y_;
        SDL_Rect rect = {x+i*10, y-22, 21, 20};
        SDL_RenderCopy(screen, heart, NULL, &rect);
    }
}



