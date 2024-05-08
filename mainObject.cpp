#include <bits/stdc++.h>
#include "mainObject.h"
#include "CommonFunction.h"
#include "graphics.h"
#include "ExplosionObject.h"

using namespace std;

void MainObject :: SelectCharacter(int choose){
    if(choose==1)
    {
        RunR = "img/NinjaFrog//RunR.png";
        RunL = "img/NinjaFrog//RunL.png";
        JumpR = "img/NinjaFrog//JumpR.png";
        JumpL = "img/NinjaFrog//JumpL.png";
    }
    else if ( choose==2 )
    {
        RunR = "img/MaskDude//RunR.png";
        RunL = "img/MaskDude//RunL.png";
        JumpR = "img/MaskDude//JumpR.png";
        JumpL = "img/MaskDude//JumpL.png";
    }
    else if ( choose==3 )
    {
        RunR = "img/PinkMan//RunR.png";
        RunL = "img/PinkMan//RunL.png";
        JumpR = "img/PinkMan//JumpR.png";
        JumpL = "img/PinkMan//JumpL.png";
    }
    else
    {
        RunR = "img/VirtualGuy//RunR.png";
        RunL = "img/VirtualGuy//RunL.png";
        JumpR = "img/VirtualGuy//JumpR.png";
        JumpL = "img/VirtualGuy//JumpL.png";
    }
}

MainObject :: MainObject(){
    RunR = "img/NinjaFrog//RunR.png";
    RunL = "img/NinjaFrog//RunL.png";
    JumpR = "img/NinjaFrog//JumpR.png";
    JumpL = "img/NinjaFrog//JumpL.png";
    gun = false;
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ =0 ;
    x_val_ =0;
    y_val_ =0;
    width_frame_ =0;
    height_frame_ =0;
    status_ = WALK_NONE;
    input_type_.left_ = 0;
    input_type_.right_ =0;
    input_type_.jump_ =0;
    input_type_.down_=0;
    input_type_.up_=0;
    on_ground_ = false;
    map_x_ =0;
    map_y_ =0;
    come_back_time_ =0;
    money_count = 0;
}

MainObject :: ~MainObject(){
}

bool MainObject :: LoadImg(string path,SDL_Renderer* screen)
{
    bool ret = BaseObject :: LoadImg(path,screen);
    if(ret==true)
    {
        width_frame_ = rect_.w/12;
        height_frame_ = rect_.h;
    }
    return ret;
}

void MainObject :: set_clips()
{
    if(width_frame_ > 0 && height_frame_ > 0){
        for(int i = 0; i < 12 ; i++)
        {
            frame_clip_[i].x = i*width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void MainObject :: Show(SDL_Renderer* des)
{
    UpdateImagePlayer(des);

    if(input_type_.left_ == 1 || input_type_.right_ == 1){
        frame_ = (frame_+1)%12;
    }
    else{
      frame_=0;
    }
    //if(frame_ >= 12) frame_ =0;
    //if(frame_stand_ >= 11) frame_stand_ = 0;

    if(come_back_time_ == 0 )
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;

        SDL_Rect* current_clip = &frame_clip_[frame_];
        SDL_Rect renderQuad = {rect_.x,rect_.y, width_frame_,height_frame_};
        SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
    }
}

void MainObject :: HandelInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* gun_sound, Graphics& graphics)
{
    if(events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
            case SDLK_RIGHT: case SDLK_d:
                {
                    status_ = WALK_RIGHT;
                    input_type_.right_ = 1;
                    input_type_.left_ =0;
                    UpdateImagePlayer(screen);
                } break;

            case SDLK_LEFT: case SDLK_a:
                {
                    status_ = WALK_LEFT;
                    input_type_.left_ = 1;
                    input_type_.right_ =0;
                    UpdateImagePlayer(screen);
                } break;

            default:
                break;
        }
    }
    else if( events.type == SDL_KEYUP )
    {
        switch(events.key.keysym.sym)
        {
            case SDLK_RIGHT: case SDLK_d:
                {
                    input_type_.right_ = 0;
                } break;
            case SDLK_LEFT: case SDLK_a:
                {
                    input_type_.left_ = 0;
                } break;
            default:
                break;
        }
    }

    if(events.type== SDL_MOUSEBUTTONDOWN && events.button.button == SDL_BUTTON_LEFT && gun && come_back_time_ ==0)
    {
        graphics.play(gun_sound);
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        BulletObject* p_bullet = new BulletObject();
        p_bullet->set_bullet_type(BulletObject::LASER_BULLET);
        p_bullet->LoadImgBullet(screen);
        if(status_ == WALK_LEFT)
        {
            if( mouseX >= rect_.x) p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            else if( double((rect_.y-mouseY)*1.0/(rect_.x - mouseX)) > 0.156 ) p_bullet->set_bullet_dir(BulletObject::DIR_UP_LEFT);
            else if( double((rect_.y-mouseY+64)*1.0/(rect_.x - mouseX)) < -0.156 ) p_bullet->set_bullet_dir(BulletObject::DIR_DOWN_LEFT);
            else p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            p_bullet->set_position(x_pos_+18, y_pos_+height_frame_*0.68);
        }
        else
        {
            if( mouseX <= rect_.x) p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
            else if( double((rect_.y-mouseY)*1.0/(mouseX-rect_.x)) > 0.156 ) p_bullet->set_bullet_dir(BulletObject::DIR_UP_RIGHT);
            else if( double((rect_.y-mouseY+64)*1.0/(mouseX-rect_.x)) < -0.156 ) p_bullet->set_bullet_dir(BulletObject::DIR_DOWN_RIGHT);
            else p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
            p_bullet->set_position(x_pos_+width_frame_-23, y_pos_+height_frame_*0.68);
        }
        p_bullet->set_x_val(BULLET_SPEED);
        p_bullet->set_y_val(BULLET_SPEED);
        p_bullet->set_is_move(true);

        p_bullet_list_.push_back(p_bullet);
    }
    if(events.key.keysym.scancode == SDL_SCANCODE_UP || events.key.keysym.scancode == SDL_SCANCODE_SPACE || events.key.keysym.scancode==SDL_SCANCODE_W)
    {
        input_type_.jump_ =1;
    }

}

SDL_Rect MainObject :: GetRectFrame(){
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;
    return rect;
}

void MainObject :: HandleBullet(SDL_Renderer* des, Map& map_data){
    for(int i=0 ; i< p_bullet_list_.size(); i++){
        BulletObject* p_bullet = p_bullet_list_[i];
        if(p_bullet != NULL)
        {
            if(p_bullet->get_is_move() == true)
            {
                p_bullet->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT, map_data);
                p_bullet->Render(des);
            }
            else
            {
                p_bullet_list_.erase(p_bullet_list_.begin()+i);
                if(p_bullet !=NULL){
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}

void MainObject :: RemoveBullet(const int& idx){
    int size = p_bullet_list_.size();
    if(size>0 && idx <size){
        BulletObject* p_bullet = p_bullet_list_[idx];
        p_bullet_list_.erase(p_bullet_list_.begin()+idx);
        if(p_bullet){ delete p_bullet;  p_bullet=NULL;}
    }
}

void MainObject :: DoPlayer(Map& map_data, SDL_Renderer* screen, int& num_live, Graphics& graphics, Mix_Chunk* chunk)
{
    if( come_back_time_ == 0)
    {
        x_val_ =0;
        y_val_ += GRAVITY_SPEED;

        if(y_val_ >= MAX_FALL_SPEED) y_val_ = MAX_FALL_SPEED;

        if(input_type_.left_ == 1){
            x_val_ -= PLAYER_SPEED;
        }
        else if(input_type_.right_ == 1){
            x_val_ += PLAYER_SPEED;
        }

        if(input_type_.jump_ == 1)
        {
            if(on_ground_ == true)
            {
                y_val_ = -PLAYER_JUMP_VAL;
            }
            on_ground_ = false;
            input_type_.jump_ = 0;
        }


        CheckToMap(map_data, screen, num_live, graphics, chunk);
        CenterEntityOnMap(map_data);
    }

    if( come_back_time_ >0)
    {
        come_back_time_--;
        if(come_back_time_ == 0)
        {
            on_ground_ = false;
            if(x_pos_ > 256)
            {
                x_pos_ -=256; //4 tile
            }
            else
            {
                x_pos_ =0;

            }
            y_pos_ = 0;
            x_val_ = 0;
            y_val_ =0;
        }
    }

}

void MainObject :: CenterEntityOnMap(Map& map_data)
{
    map_data.start_x_ = x_pos_ - (SCREEN_WIDTH/2);
    if(map_data.start_x_ < 0)   map_data.start_x_=0;
    else if(map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_) map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;

    map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT/2);
    if(map_data.start_y_ < 0) map_data.start_y_ =0;
    else if(map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_) map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
}

void MainObject :: CheckToMap(Map& map_data, SDL_Renderer* screen, int &num_live, Graphics& graphics, Mix_Chunk* chunk)
{
    int x1=0;
    int x2=0;
    int y1=0;
    int y2=0;
    int test_x = x_pos_;
    int test_y = y_pos_;

    //Check horizontal
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_)/TILE_SIZE; //vi tri hien tai + di chuyen x_val_, chia TILE_SIZE ra duoc o dang dung
    x2 = (x_pos_ + x_val_ + width_frame_-1)/TILE_SIZE; //x2 la ria phai cua nhan vat

    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_ + height_min- 1)/TILE_SIZE;

    if(x1 >= 0 && x2< MAX_MAP_X && y1 >= 0 && y2<MAX_MAP_Y)
    {
        if(x_val_ > 0) //main obbject di chuyen sang phai
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];
            if(val1 == SUPER_POWER || val2 == SUPER_POWER)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                Super(screen, graphics, chunk);
            }
            else
            {
                if(val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    x_pos_ = test_x;
                    x_val_ =0;
                }
            }
        }
        else if (x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];
            if(val1 == SUPER_POWER || val2 == SUPER_POWER)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                Super(screen, graphics, chunk);
            }
            if(val1 != BLANK_TILE || val2 != BLANK_TILE)
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
            if(val1 == SUPER_POWER || val2 == SUPER_POWER)
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                Super(screen, graphics, chunk);
            }
            else
            {
                if(val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    y_pos_ = test_y;
                    y_val_ = 0;
                    on_ground_ = true;
                    if(status_ == WALK_NONE) status_ == WALK_RIGHT;
                }
            }
        }
        else if (y_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            if(val1 == SUPER_POWER || val2 == SUPER_POWER)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                Super(screen, graphics, chunk);
            }
            else
            {
                if(val1 != BLANK_TILE || val2 !=BLANK_TILE)
                {
                    y_pos_ = test_y;
                    y_val_ = 0;
                }
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
        come_back_time_ = 60;
        num_live--;
    }
}

void MainObject :: UpdateImagePlayer(SDL_Renderer* des){
    if(on_ground_ == true)
    {
        if(status_ == WALK_LEFT)
        {
            LoadImg(RunL,des);
        }
        else
        {
            LoadImg(RunR,des);
        }
    }
    else
    {
        if(status_ == WALK_LEFT)
        {
            LoadImg(JumpL,des);
        }
        else
        {
            LoadImg(JumpR,des);
        }
    }
}

void MainObject :: IncreaseMoney(){
    money_count++;
}

void MainObject :: Super(SDL_Renderer* screen, Graphics& graphics, Mix_Chunk* chunk){
    graphics.play(chunk);
    gun = true;
    RunL = "img/Super//RunL.png";
    RunR = "img/Super//RunR.png";
    JumpL = "img/Super//JumpL.png";
    JumpR = "img/Super//JumpR.png";
    ExplosionObject super_power;
    bool sRet = super_power.LoadImg("img/Super//SuperWhite.png", screen);
    if(!sRet){
        cout<<"Error LoadImg SuperPower\n";
    }
    super_power.set_clip();
    SDL_Texture* text_power = IMG_LoadTexture(screen, "img/Super//TextSuper.png");
    for(int i=0; i<8 ; i++){
        int x_pos = rect_.x;
        int y_pos = rect_.y;
        super_power.set_frame(i);
        super_power.SetRect(x_pos, y_pos);
        super_power.Show(screen);

        SDL_Rect text = {rect_.x-23, rect_.y - i*1, 112, 20};
        SDL_RenderCopy(screen, text_power, NULL, &text);

        SDL_RenderPresent(screen);
        SDL_Delay(80);
    }
}

void MainObject :: UnSuper(string runR, string runL, string jumpL, string jumpR){
    gun=false;
    RunR = runR;
    RunL = runL;
    JumpL = jumpL;
    JumpR = jumpR;
}

bool MainObject :: CollectItem(const Sprite& item){
    int left_a = x_pos_;
    int right_a = x_pos_ + width_frame_;
    int top_a = y_pos_;
    int bottom_a = y_pos_ + height_frame_;

    int left_b = item.x_pos;
    int right_b = item.x_pos + item.width_frame_;
    int top_b = item.y_pos;
    int bottom_b = item.y_pos + item.height_frame_;

  if( (left_a<=right_b && right_a>=left_b) && (top_a<=bottom_b && bottom_a>=top_b) ) return true;

  return false;
}

void PlayerHeart :: Init(SDL_Renderer* screen){
    heart.LoadImg("img//Heart3.png", screen);
    heart.init(HEART_FRAME_3, HEART_CLIPS_3);
}

void PlayerHeart :: Show(SDL_Renderer* screen){
    for(int i=0;i<num_heart;i++){
        heart.Render(97 + i*20, -9, screen);
    }
    heart.tick();
}
