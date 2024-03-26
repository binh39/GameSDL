#include <bits/stdc++.h>
#include "mainObject.h"
#include "CommonFunction.h"
#include "graphics.h"

using namespace std;

void MainObject :: SelectCharacter(){
    int x = 1;
    cout<<"Select character: "<<endl;
    cout<<"1. Ninja Frog"<<endl;
    cout<<"2. Mask Dude"<<endl;
    cout<<"3. Pink Man"<<endl;
    cout<<"4. Virtual Guy"<<endl;
    do
    {
        cin>>x;
        if(x==1)
        {
            RunR = "img/NinjaFrog//RunR.png";
            RunL = "img/NinjaFrog//RunL.png";
            JumpR = "img/NinjaFrog//JumpR.png";
            JumpL = "img/NinjaFrog//JumpL.png";
        }
        else if ( x==2 )
        {
            RunR = "img/MaskDude//RunR.png";
            RunL = "img/MaskDude//RunL.png";
            JumpR = "img/MaskDude//JumpR.png";
            JumpL = "img/MaskDude//JumpL.png";
        }
        else if ( x==3 )
        {
            RunR = "img/PinkMan//RunR.png";
            RunL = "img/PinkMan//RunL.png";
            JumpR = "img/PinkMan//JumpR.png";
            JumpL = "img/PinkMan//JumpL.png";
        }
        else if ( x==4 )
        {
            RunR = "img/VirtualGuy//RunR.png";
            RunL = "img/VirtualGuy//RunL.png";
            JumpR = "img/VirtualGuy//JumpR.png";
            JumpL = "img/VirtualGuy//JumpL.png";
        }

    } while(!( 1<=x && x<=4));
    cout<<"Game Start!"<<endl;
    return;
}

MainObject :: MainObject()
{
    RunR = "img/NinjaFrog//RunR.png";
    RunL = "img/NinjaFrog//RunL.png";
    JumpR = "img/NinjaFrog//JumpR.png";
    JumpL = "img/NinjaFrog//JumpL.png";
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ =0 ;
    x_val_ =0;
    y_val_ =0;
    width_frame_ =0;
    height_frame_ =0;
    status_ =-1;
    input_type_.left_ = 0;
    input_type_.right_ =0;
    input_type_.jump_ =0;
    input_type_.down_=0;
    input_type_.up_=0;
    on_ground_ = false;
    map_x_ =0;
    map_y_ =0;
    come_back_time_ =0;
}

MainObject :: ~MainObject()
{

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
    if(input_type_.left_ == 1 || input_type_.right_ == 1) frame_++;
    else frame_=0;

    if(frame_ >= 12) frame_ =0;

    if(come_back_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;

        SDL_Rect* current_clip = &frame_clip_[frame_];
        SDL_Rect renderQuad = {rect_.x,rect_.y, width_frame_,height_frame_};
        SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
    }
}

void MainObject :: HandelInputAction(SDL_Event events, SDL_Renderer* screen)
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
                    if(on_ground_ == true) LoadImg(RunR,screen);
                    else LoadImg(JumpR,screen);
                } break;

            case SDLK_LEFT: case SDLK_a:
                {
                    status_ = WALK_LEFT;
                    input_type_.left_ = 1;
                    input_type_.right_ =0;
                    if(on_ground_ == true) LoadImg(RunL,screen);
                    else LoadImg(JumpL,screen);
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

    /*if(events.type == SDL_MOUSEBUTTONDOWN)
    {
        if(events.button.button == SDL_BUTTON_RIGHT)
        {
            input_type_.jump_ = 1;
        }
    }*/
    if(events.key.keysym.scancode == SDL_SCANCODE_UP || events.key.keysym.scancode == SDL_SCANCODE_SPACE || events.key.keysym.scancode==SDL_SCANCODE_W)
    {
        input_type_.jump_ =1;
    }

}

void MainObject :: DoPlayer(Map& map_data)
{
    if( come_back_time_ == 0)
    {
            x_val_ =0;
        y_val_ += GRAVITY_SPEED;

        if(y_val_ >= MAX_FALL_SPEED){
            y_val_ = MAX_FALL_SPEED;
        }

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


        CheckToMap(map_data);
        CenterEntityOnMap(map_data);
    }

    if( come_back_time_ >0)
    {
        come_back_time_--;
        if(come_back_time_ == 0)
        {
            if(x_pos_ > 256)
            {
                x_pos_ -=256;
                map_x_ -=256;
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

void MainObject :: CheckToMap(Map& map_data)
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
            if(map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                //x_pos_ = x2*TILE_SIZE;
                //x_pos_ -= width_frame_ +1;
                x_pos_ = test_x;
                x_val_ =0;
            }
        }
        else if (x_val_ < 0)
        {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
            {
                //x_pos_ = (x1 +1)*TILE_SIZE;
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
            if(map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                //y_pos_ = y2*TILE_SIZE;
                //y_pos_ -= (height_frame_+ 1);
                y_pos_ = test_y;
                y_val_ = 0;
                on_ground_ = true;
            }
        }
        else if (y_val_ < 0)
        {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2]!=BLANK_TILE)
            {
                //y_pos_ = (y1 + 1)*TILE_SIZE;
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
        come_back_time_ = 60;
    }
}

