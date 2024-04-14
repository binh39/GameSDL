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

    if(events.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if(events.button.button == SDL_BUTTON_RIGHT)
        {

            BulletObject* p_bullet = new BulletObject();
            p_bullet->set_bullet_type(BulletObject::LASER_BULLET);
            p_bullet->LoadImgBullet(screen);

            if(status_ == WALK_LEFT)
            {
                cout<<double((rect_.y-mouseY)*1.0/(mouseX-rect_.x))<<endl;
                if( mouseX >= rect_.x) p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                else if( double((rect_.y-mouseY)*1.0/(rect_.x - mouseX)) > 0.156 ) p_bullet->set_bullet_dir(BulletObject::DIR_UP_LEFT);
                else if( double((rect_.y-mouseY+64)*1.0/(rect_.x - mouseX)) < -0.156 ) p_bullet->set_bullet_dir(BulletObject::DIR_DOWN_LEFT);
                else p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);

                p_bullet->SetRect(rect_.x, rect_.y + height_frame_*0.3);
            }
            else
            {
                cout<<double((rect_.y-mouseY)*1.0/(mouseX-rect_.x))<<endl;
                if( mouseX <= rect_.x) p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                else if( double((rect_.y-mouseY)*1.0/(mouseX-rect_.x)) > 0.156 ) p_bullet->set_bullet_dir(BulletObject::DIR_UP_RIGHT);
                else if( double((rect_.y-mouseY+64)*1.0/(mouseX-rect_.x)) < -0.156 ) p_bullet->set_bullet_dir(BulletObject::DIR_DOWN_RIGHT);
                else p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);

                p_bullet->SetRect(rect_.x + width_frame_ - 20, rect_.y + height_frame_*0.3);
            }
            //toc do
            p_bullet->set_x_val(BULLET_SPEED);
            p_bullet->set_y_val(BULLET_SPEED);
            p_bullet->set_is_move(true);

            p_bullet_list_.push_back(p_bullet);
        }
        else if(events.button.button == SDL_BUTTON_LEFT)
        {
            //cout<<mouseX<<" "<<mouseY<<endl;
            //cout<<"check mouse left\n";

            BulletObject* p_bullet = new BulletObject();
            p_bullet->set_bullet_type(BulletObject::SPHERE_BULLET);
            p_bullet->LoadImgBullet(screen);

            //set vi tri
            if(status_ == WALK_LEFT)
            {
                cout<<double((rect_.y-mouseY)*1.0/(mouseX-rect_.x))<<endl;
                if( mouseX >= rect_.x) p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                else if( double((rect_.y-mouseY)*1.0/(rect_.x - mouseX)) > 0.156 ) p_bullet->set_bullet_dir(BulletObject::DIR_UP_LEFT);
                else if( double((rect_.y-mouseY+64)*1.0/(rect_.x - mouseX)) < -0.156 ) p_bullet->set_bullet_dir(BulletObject::DIR_DOWN_LEFT);
                else p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);

                //p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                p_bullet->SetRect(rect_.x, rect_.y + height_frame_*0.3);

            }
            else
            {
                cout<<double((rect_.y-mouseY)*1.0/(mouseX-rect_.x))<<endl;
                if( mouseX <= rect_.x) p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                else if( double((rect_.y-mouseY)*1.0/(mouseX-rect_.x)) > 0.156 ) p_bullet->set_bullet_dir(BulletObject::DIR_UP_RIGHT);
                else if( double((rect_.y-mouseY+64)*1.0/(mouseX-rect_.x)) < -0.156 ) p_bullet->set_bullet_dir(BulletObject::DIR_DOWN_RIGHT);
                else p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                //p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                p_bullet->SetRect(rect_.x + width_frame_ - 20, rect_.y + height_frame_*0.3);
            }
            //toc do
            p_bullet->set_x_val(BULLET_SPEED);
            p_bullet->set_y_val(BULLET_SPEED);
            p_bullet->set_is_move(true);

            p_bullet_list_.push_back(p_bullet);
        }
    }
    if(events.key.keysym.scancode == SDL_SCANCODE_UP || events.key.keysym.scancode == SDL_SCANCODE_SPACE || events.key.keysym.scancode==SDL_SCANCODE_W)
    {
        input_type_.jump_ =1;
    }

}

void MainObject :: HandleBullet(SDL_Renderer* des){
    for(int i=0 ; i< p_bullet_list_.size(); i++){
        BulletObject* p_bullet = p_bullet_list_[i];
        if(p_bullet != NULL)
        {
            if(p_bullet->get_is_move() == true)
            {
                p_bullet->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
                //p_bullet->PrintRect();
                p_bullet->Render(des);
            }
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


void MainObject :: DoPlayer(Map& map_data, Graphics& graphics, Mix_Chunk * jump)
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
                graphics.play(jump);
                // pass by value

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
                if(status_ == WALK_NONE) status_ == WALK_RIGHT;
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
