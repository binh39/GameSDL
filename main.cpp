#include "CommonFunction.h"
#include "graphics.h"
#include "BaseObject.h"
#include "game_map.h"
#include "mainObject.h"
#include "time.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include "BossObject.h"

BaseObject g_background;
TTF_Font* font_time;

void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,"%s: %s", msg, error);
    SDL_Quit();
}

bool InitData(){
    bool success = true;
    int res = SDL_Init(SDL_INIT_VIDEO);
    if(res < 0) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

    g_window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(g_window == NULL ) success=false;
    else {
        g_screen = SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL) success =false;
        else{
            SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success= false;
        }
        if(TTF_Init()==-1){
            cout<<"Error init font\n";
            success = false;
        }
        font_time = TTF_OpenFont(FONT_NAME, FONT_SIZE);
        if(font_time == NULL){
            success = false;
        }
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",Mix_GetError() );
    if (TTF_Init() == -1) logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",TTF_GetError());
    return success;
}

bool LoadBackground(){
    bool ret = g_background.LoadImg("img\\Background.png",g_screen);
    if(ret == false) return false;
    return true;
}

void renderTexture(SDL_Texture *texture, int x, int y, SDL_Renderer* renderer){
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void RenderWithMap(Map& map_data, SDL_Texture* texture, SDL_Renderer* renderer, const int& x_pos, const int& y_pos){
    int x = x_pos - map_data.start_x_;
    int y = y_pos - map_data.start_y_;
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}

void close(){
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

vector<ThreatsObject*> MakeThreadList1(){
    vector<ThreatsObject*> list_threats;
    ThreatsObject* dynamic_threats = new ThreatsObject[2];
    for(int i=0; i<2 ; i++)
    {
        ThreatsObject* p_threat = (dynamic_threats+i);
        if(p_threat != NULL)
        {
            p_threat->LoadImg("img/Enemy/BunnyL.png",g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            if(i==0){
                p_threat->set_x_pos(60*64);
                p_threat->set_y_pos(7*64-10);
            }
            else if(i==1){
                p_threat->set_x_pos(73*64);
                p_threat->set_y_pos(7*64-10);
            }
            int pos1 = p_threat->get_x_pos()-128;
            int pos2 = p_threat->get_x_pos()+64;
            p_threat->SetAnimationPos(pos1,pos2);
            p_threat->set_input_left(1);
            list_threats.push_back(p_threat);
        }
    }

    ThreatsObject* threats_objs = new ThreatsObject[3];
    for(int i=0 ; i<3 ; i++)
    {
        ThreatsObject* p_threat = (threats_objs+i);
        if(p_threat!=nullptr){
            p_threat->LoadImg("img/Enemy/Turtle.png",g_screen);
            p_threat->set_clips();
            if(i==0){
                p_threat->set_x_pos(49*64-2);
                p_threat->set_y_pos(4*64-50);
            }
            else if(i==1){
                p_threat->set_x_pos(66*64);
                p_threat->set_y_pos(5*64-50);
            }
            else{
                p_threat->set_x_pos(77*64-2);
                p_threat->set_y_pos(6*64-50);
            }
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_input_left(0);
            list_threats.push_back(p_threat);

        }
    }

    return list_threats;
}

vector<ThreatsObject*> MakeThreadList2(){
    vector<ThreatsObject*> list_threats;
    ThreatsObject* dynamic_threats = new ThreatsObject[4];
    for(int i=0; i<4 ; i++)
    {
        ThreatsObject* p_threat = (dynamic_threats+i);
        if(p_threat != NULL)
        {
            p_threat->LoadImg("img/Enemy/BunnyL.png",g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            if(i==0){
                p_threat->set_x_pos(5*64);
                p_threat->set_y_pos(6*64-10);
            }
            else if(i==1){
                p_threat->set_x_pos(30*64);
                p_threat->set_y_pos(6*64-10);
            }
            else if(i==2){
                p_threat->set_x_pos(41*64);
                p_threat->set_y_pos(7*64-10);
            }
            else if(i==3){
                p_threat->set_x_pos(61*64);
                p_threat->set_y_pos(7*64-10);
            }
            int pos1 = p_threat->get_x_pos()-128;
            int pos2 = p_threat->get_x_pos()+64;
            p_threat->SetAnimationPos(pos1,pos2);
            p_threat->set_input_left(1);
            list_threats.push_back(p_threat);
        }
    }

    ThreatsObject* threats_objs = new ThreatsObject[3];
    for(int i=0 ; i<3 ; i++)
    {
        ThreatsObject* p_threat = (threats_objs+i);
        if(p_threat!=nullptr){
            p_threat->LoadImg("img/Enemy/Turtle.png",g_screen);
            p_threat->set_clips();
            if(i==0){
                p_threat->set_x_pos(17*64);
                p_threat->set_y_pos(7*64-50);
            }
            else if(i==1){
                p_threat->set_x_pos(38*64);
                p_threat->set_y_pos(2*64-50);
            }
            else{
                p_threat->set_x_pos(73*64);
                p_threat->set_y_pos(7*64-50);
            }
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_input_left(0);
            list_threats.push_back(p_threat);

        }
    }

    return list_threats;
}

vector<ThreatsObject*> MakeThreadList3(){
    vector<ThreatsObject*> list_threats;
    ThreatsObject* dynamic_threats = new ThreatsObject[4];
    for(int i=0; i<4 ; i++)
    {
        ThreatsObject* p_threat = (dynamic_threats+i);
        if(p_threat != NULL)
        {
            p_threat->LoadImg("img/Enemy/BunnyL.png",g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            if(i==0){
                p_threat->set_x_pos(4*64);
                p_threat->set_y_pos(7*64-10);
            }
            else if(i==1){
                p_threat->set_x_pos(17*64);
                p_threat->set_y_pos(7*64-10);
            }
            else if(i==2){
                p_threat->set_x_pos(31*64);
                p_threat->set_y_pos(7*64-10);
            }
            else if(i==3){
                p_threat->set_x_pos(34*64);
                p_threat->set_y_pos(0*64-10);
            }
            int pos1 = p_threat->get_x_pos()-128;
            int pos2 = p_threat->get_x_pos()+64;
            p_threat->SetAnimationPos(pos1,pos2);
            p_threat->set_input_left(1);
            list_threats.push_back(p_threat);
        }
    }

    ThreatsObject* threats_objs = new ThreatsObject[7];
    for(int i=0 ; i<7 ; i++)
    {
        ThreatsObject* p_threat = (threats_objs+i);
        if(i==0)
        {
            if(p_threat != NULL)
            {
                p_threat->LoadImg("img/Enemy/Plant.png",g_screen);
                p_threat->set_clips();
                p_threat->set_x_pos(24*64);
                p_threat->set_y_pos(5*64-10);
                p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
                p_threat->set_input_left(0);
                BulletObject* p_bullet = new BulletObject();
                p_threat->InitBullet(p_bullet, g_screen);
                list_threats.push_back(p_threat);
            }
        }
        else if(i==1){
            if(p_threat != NULL)
            {
                p_threat->LoadImg("img/Enemy/Plant.png",g_screen);
                p_threat->set_clips();
                p_threat->set_x_pos(38*64);
                p_threat->set_y_pos(7*64-10);
                p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
                p_threat->set_input_left(0);
                BulletObject* p_bullet = new BulletObject();
                p_threat->InitBullet(p_bullet, g_screen);
                list_threats.push_back(p_threat);
            }
        }
        else if(i==2){
            if(p_threat != NULL)
            {
                p_threat->LoadImg("img/Enemy/Plant.png",g_screen);
                p_threat->set_clips();
                p_threat->set_x_pos(76*64-10);
                p_threat->set_y_pos(7*64-10);
                p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
                p_threat->set_input_left(0);
                BulletObject* p_bullet = new BulletObject();
                p_threat->InitBullet(p_bullet, g_screen);
                list_threats.push_back(p_threat);
            }
        }
        else if(i==3){
            if(p_threat != NULL)
            {
                p_threat->LoadImg("img/Enemy/Turtle.png",g_screen);
                p_threat->set_clips();
                p_threat->set_x_pos(14*64);
                p_threat->set_y_pos(7*64-50);
                p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
                p_threat->set_input_left(0);
                list_threats.push_back(p_threat);
            }
        }
        else if(i==4){
            if(p_threat != NULL)
            {
                p_threat->LoadImg("img/Enemy/Turtle.png",g_screen);
                p_threat->set_clips();
                p_threat->set_x_pos(48*64-10);
                p_threat->set_y_pos(5*64-10);
                p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
                p_threat->set_input_left(0);
                list_threats.push_back(p_threat);
            }
        }
        else if(i==5){
            if(p_threat != NULL)
            {
                p_threat->LoadImg("img/Enemy/Turtle.png",g_screen);
                p_threat->set_clips();
                p_threat->set_x_pos(59*64);
                p_threat->set_y_pos(7*64-10);
                p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
                p_threat->set_input_left(0);
                list_threats.push_back(p_threat);
            }
        }
        else if(i==6){
            if(p_threat != NULL)
            {
                p_threat->LoadImg("img/Enemy/Turtle.png",g_screen);
                p_threat->set_clips();
                p_threat->set_x_pos(67*64);
                p_threat->set_y_pos(5*64-10);
                p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
                p_threat->set_input_left(0);
                list_threats.push_back(p_threat);
            }
        }
    }

    return list_threats;
}

vector<Sprite*> MakeFruitList1(){
    vector<Sprite*> fruit_list;

    Sprite* apple = new Sprite[6];
    for(int i=0;i<6;i++){
        Sprite* apple_ = (apple+i);
        if(apple_!=nullptr){
            apple_->LoadImg("img/Items/Fruits//Strawberry.png", g_screen);
            apple_->init(FRUITS_FRAME_2, FRUITS_CLIPS_2);
            if(i==0) apple_->set_pos(21*64, 4*64);
            else if(i==1) apple_->set_pos(22*64, 4*64);
            else if(i==2) apple_->set_pos(23*64, 4*64);
            else if(i==3) apple_->set_pos(24*64, 4*64);
            else if(i==4) apple_->set_pos(25*64, 4*64);
            else if(i==5) apple_->set_pos(26*64, 4*64);
            else apple_->set_pos(i*TILE_SIZE, 2*64);
            fruit_list.push_back(apple_);
        }
    }

    Sprite* banana = new Sprite[15];
    for(int i=0;i<15;i++){
        Sprite* banana_ = (banana+i);
        if(banana_!=nullptr){
            banana_->LoadImg("img/Items/Fruits//Pineapple.png", g_screen);
            banana_->init(FRUITS_FRAME_2, FRUITS_CLIPS_2);
            if(i==0) banana_->set_pos(59*64, 6*64);
            else if(i==1) banana_->set_pos(60*64, 6*64);
            else if(i==2) banana_->set_pos(61*64, 6*64);
            else if(i==3) banana_->set_pos(62*64, 5*64);
            else if(i==4) banana_->set_pos(63*64, 4*64);
            else if(i==5) banana_->set_pos(64*64, 4*64);
            else if(i==6) banana_->set_pos(65*64, 3*64);
            else if(i==7) banana_->set_pos(30*64, 6*64);
            else if(i==8) banana_->set_pos(31*64, 6*64);
            else if(i==9) banana_->set_pos(32*64, 6*64);
            else if(i==10) banana_->set_pos(33*64, 6*64);
            else if(i==11) banana_->set_pos(34*64, 6*64);
            else if(i==12) banana_->set_pos(35*64, 6*64);
            else if(i==13) banana_->set_pos(36*64, 6*64);
            else if(i==14) banana_->set_pos(37*64, 6*64);
            else banana_->set_pos(i*TILE_SIZE, 3*64);
            fruit_list.push_back(banana_);
        }
    }



    return fruit_list;
}

vector<Sprite*> MakeFruitList2(){
    vector<Sprite*> fruit_list;

    Sprite* apple = new Sprite[6];
    for(int i=0;i<6;i++){
        Sprite* apple_ = (apple+i);
        if(apple_!=nullptr){
            apple_->LoadImg("img/Items/Fruits//Strawberry.png", g_screen);
            apple_->init(FRUITS_FRAME_2, FRUITS_CLIPS_2);
            if(i==0) apple_->set_pos(3*64, 5*64);
            else if(i==1) apple_->set_pos(4*64, 5*64);
            else if(i==2) apple_->set_pos(5*64, 5*64);
            else if(i==3) apple_->set_pos(6*64, 5*64);
            else if(i==4) apple_->set_pos(7*64, 5*64);
            else if(i==5) apple_->set_pos(8*64, 5*64);
            else apple_->set_pos(i*TILE_SIZE, 2*64);
            fruit_list.push_back(apple_);
        }
    }

    Sprite* banana = new Sprite[13];
    for(int i=0;i<13;i++){
        Sprite* banana_ = (banana+i);
        if(banana_!=nullptr){
            banana_->LoadImg("img/Items/Fruits//Pineapple.png", g_screen);
            banana_->init(FRUITS_FRAME_2, FRUITS_CLIPS_2);
            if(i==0) banana_->set_pos(12*64, 5*64);
            else if(i==1) banana_->set_pos(13*64, 5*64);
            else if(i==2) banana_->set_pos(14*64, 5*64);
            else if(i==3) banana_->set_pos(15*64, 5*64);
            else if(i==4) banana_->set_pos(16*64, 6*64);
            else if(i==5) banana_->set_pos(17*64, 6*64);
            else if(i==6) banana_->set_pos(23*64, 6*64);
            else if(i==7) banana_->set_pos(24*64, 5*64);
            else if(i==8) banana_->set_pos(25*64, 5*64);
            else if(i==9) banana_->set_pos(26*64, 5*64);
            else if(i==10) banana_->set_pos(27*64, 5*64);
            else if(i==11) banana_->set_pos(28*64, 5*64);
            else if(i==12) banana_->set_pos(29*64, 5*64);
            else banana_->set_pos(i*TILE_SIZE, 3*64);
            fruit_list.push_back(banana_);
        }
    }
    Sprite* kiwi = new Sprite[5];
    for(int i=0;i<5;i++){
        Sprite* kiwi_ = (kiwi+i);
        if(kiwi_!=nullptr){
            kiwi_->LoadImg("img/Items/Fruits//Kiwi.png", g_screen);
            kiwi_->init(FRUITS_FRAME_2, FRUITS_CLIPS_2);
            kiwi_->set_pos(33*64, (6-i)*64);
            fruit_list.push_back(kiwi_);
        }
    }

    Sprite* kiwi2 = new Sprite[7];
    for(int i=0;i<7;i++){
        Sprite* kiwi_ = (kiwi2+i);
        if(kiwi_!=nullptr){
            kiwi_->LoadImg("img/Items/Fruits//Kiwi.png", g_screen);
            kiwi_->init(FRUITS_FRAME_2, FRUITS_CLIPS_2);
            kiwi_->set_pos((38+i)*64, 6*64);
            fruit_list.push_back(kiwi_);
        }
    }

    Sprite* melon = new Sprite[6];
    for(int i=0;i<6;i++){
        Sprite* melon_ = (melon+i);
        if(melon_!=nullptr){
            melon_->LoadImg("img/Items/Fruits//Melon.png", g_screen);
            melon_->init(FRUITS_FRAME_2, FRUITS_CLIPS_2);
            melon_->set_pos((36+i)*64, 2*64);
            fruit_list.push_back(melon_);
        }
    }

    Sprite* orange = new Sprite[6];
    for(int i=0;i<6;i++){
        Sprite* orange_ = (orange+i);
        if(orange_!=nullptr){
            orange_->LoadImg("img/Items/Fruits//Orange.png", g_screen);
            orange_->init(FRUITS_FRAME_2, FRUITS_CLIPS_2);
            orange_->set_pos((57+i)*64, 6*64);
            fruit_list.push_back(orange_);
        }
    }

    return fruit_list;
}

vector<Sprite*> MakeFruitList3(){
    vector<Sprite*> fruit_list;
    Sprite* apple = new Sprite[5];
    for(int i=0;i<5;i++){
        Sprite* apple_ = (apple+i);
        if(apple_!=nullptr){
            apple_->LoadImg("img/Items/Fruits//Strawberry.png", g_screen);
            apple_->init(FRUITS_FRAME_2, FRUITS_CLIPS_2);
            if(i==0) apple_->set_pos(9*64, 2*64);
            else if(i==1) apple_->set_pos(10*64, 3*64);
            else if(i==2) apple_->set_pos(11*64, 3*64);
            else if(i==3) apple_->set_pos(12*64, 4*64);
            else if(i==4) apple_->set_pos(13*64, 5*64);
            else apple_->set_pos(i*TILE_SIZE, 2*64);
            fruit_list.push_back(apple_);
        }
    }

    Sprite* banana = new Sprite[7];
    for(int i=0;i<7;i++){
        Sprite* banana_ = (banana+i);
        if(banana_!=nullptr){
            banana_->LoadImg("img/Items/Fruits//Pineapple.png", g_screen);
            banana_->init(FRUITS_FRAME_2, FRUITS_CLIPS_2);
            if(i==0) banana_->set_pos(31*64, 2*64);
            else if(i==1) banana_->set_pos(32*64, 2*64);
            else if(i==2) banana_->set_pos(33*64, 2*64);
            else if(i==3) banana_->set_pos(34*64, 2*64);
            else if(i==4) banana_->set_pos(35*64, 2*64);
            else if(i==5) banana_->set_pos(36*64, 2*64);
            else if(i==6) banana_->set_pos(37*64, 2*64);
            else banana_->set_pos(i*TILE_SIZE, 3*64);
            fruit_list.push_back(banana_);
        }
    }

    return fruit_list;
}

vector<Sprite*> MakeCollected1(){
    vector<Sprite*> fruit_list;

    Sprite* apple = new Sprite[6];
    for(int i=0;i<6;i++){
        Sprite* apple_ = (apple+i);
        if(apple_!=nullptr){
            apple_->LoadImg("img/Items/Fruits//Collect.png", g_screen);
            apple_->init(COLLECTED_FRAME_2, COLLECTED_CLIPS_2);
            if(i==0) apple_->set_pos(21*64, 4*64);
            else if(i==1) apple_->set_pos(22*64, 4*64);
            else if(i==2) apple_->set_pos(23*64, 4*64);
            else if(i==3) apple_->set_pos(24*64, 4*64);
            else if(i==4) apple_->set_pos(25*64, 4*64);
            else if(i==5) apple_->set_pos(26*64, 4*64);
            else apple_->set_pos(i*TILE_SIZE, 2*64);
            fruit_list.push_back(apple_);
        }
    }

    Sprite* banana = new Sprite[15];
    for(int i=0;i<15;i++){
        Sprite* banana_ = (banana+i);
        if(banana_!=nullptr){
            banana_->LoadImg("img/Items/Fruits//Collect.png", g_screen);
            banana_->init(COLLECTED_FRAME_2, COLLECTED_CLIPS_2);
            if(i==0) banana_->set_pos(59*64, 6*64);
            else if(i==1) banana_->set_pos(60*64, 6*64);
            else if(i==2) banana_->set_pos(61*64, 6*64);
            else if(i==3) banana_->set_pos(62*64, 5*64);
            else if(i==4) banana_->set_pos(63*64, 4*64);
            else if(i==5) banana_->set_pos(64*64, 4*64);
            else if(i==6) banana_->set_pos(65*64, 3*64);
            else if(i==7) banana_->set_pos(30*64, 6*64);
            else if(i==8) banana_->set_pos(31*64, 6*64);
            else if(i==9) banana_->set_pos(32*64, 6*64);
            else if(i==10) banana_->set_pos(33*64, 6*64);
            else if(i==11) banana_->set_pos(34*64, 6*64);
            else if(i==12) banana_->set_pos(35*64, 6*64);
            else if(i==13) banana_->set_pos(36*64, 6*64);
            else if(i==14) banana_->set_pos(37*64, 6*64);
            else banana_->set_pos(i*TILE_SIZE, 3*64);
            fruit_list.push_back(banana_);
        }
    }
    return fruit_list;
}

vector<Sprite*> MakeCollected2(){
    vector<Sprite*> fruit_list;

    Sprite* apple = new Sprite[6];
    for(int i=0;i<6;i++){
        Sprite* apple_ = (apple+i);
        if(apple_!=nullptr){
            apple_->LoadImg("img/Items/Fruits//Collect.png", g_screen);
            apple_->init(COLLECTED_FRAME_2, COLLECTED_CLIPS_2);
            if(i==0) apple_->set_pos(3*64, 5*64);
            else if(i==1) apple_->set_pos(4*64, 5*64);
            else if(i==2) apple_->set_pos(5*64, 5*64);
            else if(i==3) apple_->set_pos(6*64, 5*64);
            else if(i==4) apple_->set_pos(7*64, 5*64);
            else if(i==5) apple_->set_pos(8*64, 5*64);
            else apple_->set_pos(i*TILE_SIZE, 2*64);
            fruit_list.push_back(apple_);
        }
    }

    Sprite* banana = new Sprite[13];
    for(int i=0;i<13;i++){
        Sprite* banana_ = (banana+i);
        if(banana_!=nullptr){
            banana_->LoadImg("img/Items/Fruits//Collect.png", g_screen);
            banana_->init(COLLECTED_FRAME_2, COLLECTED_CLIPS_2);
            if(i==0) banana_->set_pos(12*64, 5*64);
            else if(i==1) banana_->set_pos(13*64, 5*64);
            else if(i==2) banana_->set_pos(14*64, 5*64);
            else if(i==3) banana_->set_pos(15*64, 5*64);
            else if(i==4) banana_->set_pos(16*64, 6*64);
            else if(i==5) banana_->set_pos(17*64, 6*64);
            else if(i==6) banana_->set_pos(23*64, 6*64);
            else if(i==7) banana_->set_pos(24*64, 5*64);
            else if(i==8) banana_->set_pos(25*64, 5*64);
            else if(i==9) banana_->set_pos(26*64, 5*64);
            else if(i==10) banana_->set_pos(27*64, 5*64);
            else if(i==11) banana_->set_pos(28*64, 5*64);
            else if(i==12) banana_->set_pos(29*64, 5*64);
            else banana_->set_pos(i*TILE_SIZE, 3*64);
            fruit_list.push_back(banana_);
        }
    }
    Sprite* kiwi = new Sprite[5];
    for(int i=0;i<5;i++){
        Sprite* kiwi_ = (kiwi+i);
        if(kiwi_!=nullptr){
            kiwi_->LoadImg("img/Items//Fruits//Collect.png", g_screen);
            kiwi_->init(COLLECTED_FRAME_2, COLLECTED_CLIPS_2);
            kiwi_->set_pos(33*64, (6-i)*64);
            fruit_list.push_back(kiwi_);
        }
    }

    Sprite* kiwi2 = new Sprite[7];
    for(int i=0;i<7;i++){
        Sprite* kiwi_ = (kiwi2+i);
        if(kiwi_!=nullptr){
            kiwi_->LoadImg("img/Items//Fruits//Collect.png", g_screen);
            kiwi_->init(COLLECTED_FRAME_2, COLLECTED_CLIPS_2);
            kiwi_->set_pos((38+i)*64, 6*64);
            fruit_list.push_back(kiwi_);
        }
    }

    Sprite* melon = new Sprite[6];
    for(int i=0;i<6;i++){
        Sprite* melon_ = (melon+i);
        if(melon_!=nullptr){
            melon_->LoadImg("img/Items/Fruits//Collect.png", g_screen);
            melon_->init(COLLECTED_FRAME_2, COLLECTED_CLIPS_2);
            melon_->set_pos((36+i)*64, 2*64);
            fruit_list.push_back(melon_);
        }
    }

    Sprite* orange = new Sprite[6];
    for(int i=0;i<6;i++){
        Sprite* orange_ = (orange+i);
        if(orange_!=nullptr){
            orange_->LoadImg("img/Items/Fruits//Collect.png", g_screen);
            orange_->init(COLLECTED_FRAME_2, COLLECTED_CLIPS_2);
            orange_->set_pos((57+i)*64, 6*64);
            fruit_list.push_back(orange_);
        }
    }

    return fruit_list;

}

vector<Sprite*> MakeCollected3(){
    vector<Sprite*> collect_list;
    Sprite* collect = new Sprite[12];
    for(int i=0;i<5;i++){
        Sprite* apple_ = (collect+i);
        if(apple_!=nullptr){
            apple_->LoadImg("img/Items/Fruits//Collect.png", g_screen);
            apple_->init(COLLECTED_FRAME_2, COLLECTED_CLIPS_2);
            if(i==0) apple_->set_pos(9*64, 2*64);
            else if(i==1) apple_->set_pos(10*64, 3*64);
            else if(i==2) apple_->set_pos(11*64, 3*64);
            else if(i==3) apple_->set_pos(12*64, 4*64);
            else if(i==4) apple_->set_pos(13*64, 5*64);
            else apple_->set_pos(i*TILE_SIZE, 2*64);
            collect_list.push_back(apple_);
        }
    }
    for(int i=5;i<12;i++){
        Sprite* banana_ = (collect+i);
        if(banana_!=nullptr){
            banana_->LoadImg("img/Items/Fruits//Collect.png", g_screen);
            banana_->init(COLLECTED_FRAME_2, COLLECTED_CLIPS_2);
            if(i==5) banana_->set_pos(31*64, 2*64);
            else if(i==6) banana_->set_pos(32*64, 2*64);
            else if(i==7) banana_->set_pos(33*64, 2*64);
            else if(i==8) banana_->set_pos(34*64, 2*64);
            else if(i==9) banana_->set_pos(35*64, 2*64);
            else if(i==10) banana_->set_pos(36*64, 2*64);
            else if(i==11) banana_->set_pos(37*64, 2*64);
            else banana_->set_pos(i*TILE_SIZE, 3*64);
            collect_list.push_back(banana_);
        }
    }

    return collect_list;
}

vector<Sprite*> MakeBox3(){
    vector<Sprite*> box_list;
    Sprite* box = new Sprite[6];
    for(int i=0; i<6; i++){
        Sprite* box_ = (box+i);
        if(box_!=nullptr){
            box_->LoadImg("img/Items/Box.png", g_screen);
            box_->init(BOX_FRAME, BOX_CLIPS);
            if(i==0) box_->set_pos(11*64, 6*64);
            else if(i==1) box_->set_pos(39*64, 8*64);
            else if(i==2) box_->set_pos(40*64, 8*64);
            else if(i==3) box_->set_pos(41*64, 8*64);
            else if(i==4) box_->set_pos(42*64, 8*64);
            else if(i==5) box_->set_pos(43*64, 8*64);
            box_list.push_back(box_);
        }
    }

    return box_list;
}

vector<Sprite*> MakeGreenPortal(){
    vector<Sprite*> green_list;
    Sprite* portal = new Sprite[3];
    for(int i=0;i<3;i++){
        Sprite* portal_ = (portal+i);
        if(portal_!=nullptr){
            portal_->LoadImg("img/Items//GreenPortal.png", g_screen);
            portal_->init(MAN_FRAMES, MAN_CLIPS);
            if(i==0) portal_->set_pos(6*64, 6*64);
            else if(i==1) portal_->set_pos(21*64, 7*64);
            else if(i==2) portal_->set_pos(33*64, 1*64);
            green_list.push_back(portal_);
        }
    }
    return green_list;
}

vector<Sprite*> MakeGreyPortal(){
    vector<Sprite*> grey_list;
    Sprite* portal = new Sprite[2];
    for(int i=0;i<2;i++){
        Sprite* portal_ = (portal+i);
        if(portal_!=nullptr){
            portal_->LoadImg("img/Items//GreyPortal.png", g_screen);
            portal_->init(MAN_FRAMES, MAN_CLIPS);
            if(i==0) portal_->set_pos(3*64, 2*64);
            else if(i==1) portal_->set_pos(33*64, 5*64);
            grey_list.push_back(portal_);
        }
    }
    return grey_list;
}
using namespace std;

int main(int argc,char* argv[])
{

    if( InitData() == false) return -1;
    if(LoadBackground() == false) return -2;

    int lv1=0, lv2=0, lv3=0, lv4=0;
    ifstream fileLevel("map//Level.txt");
    fileLevel>>lv1>>lv2>>lv3>>lv4;
    fileLevel.close();
    int HighScore = 0;
    ifstream fileScore("map//HighScore.txt");
    fileScore>>HighScore;
    fileScore.close();

    SDL_Texture* hMove = IMG_LoadTexture(g_screen, "map//Move.png");
    SDL_Texture* hCollect = IMG_LoadTexture(g_screen, "map//Collect.png");
    SDL_Texture* hClick = IMG_LoadTexture(g_screen, "map//Click.png");

    ImpTimer fps_timer;
    SDL_Texture* vien = IMG_LoadTexture(g_screen, "img//vien.png");

    Graphics graphics;
    Mix_Music* gMusic = graphics.loadMusic("sound//cafe_boba_short.mp3");
    Mix_Chunk *gJump = graphics.loadSound("sound//jump.wav");
    Mix_Chunk *gun_sound = graphics.loadSound("sound//Gun2.wav");
    Mix_Chunk *fruit_sound = graphics.loadSound("sound//Fruit.wav");
    Mix_Chunk *super_power = graphics.loadSound("sound//SuperPower.wav");
    Mix_Chunk *boss_gun = graphics.loadSound("sound//GunBoss.wav");
    Mix_Chunk *disappear = graphics.loadSound("sound//Disappear.wav");

    ExplosionObject explosion_;
    bool tRet = explosion_.LoadImg("img//Explosion.png", g_screen);
    if(!tRet){
        cout << "Error LoadImg Explosion\n";
        return -1;
    }
    explosion_.set_clip();

    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);
    TextObject mark_game;
    mark_game.SetColor(TextObject::WHITE_TEXT);
    TextObject high_score;
    high_score.SetColor(TextObject::WHITE_TEXT);

    Menu menu;
    menu.LoadVolumnButton(g_screen);
    menu.LoadRestart(g_screen);
    menu.LoadPause(g_screen);

    vector<ThreatsObject*> threats_list;
    vector<Sprite*> fruit_list;
    vector<Sprite*> collect_list;
    vector<Sprite*> box_list;
    vector<Sprite*> green_portal;
    vector<Sprite*> grey_portal;

    Sprite Fan;
    Fan.LoadImg("img/Items//Fan.png", g_screen);
    Fan.init(FAN_FRAME, FAN_CLIPS);
    Sprite Start_Flag;
    Start_Flag.LoadImg("img/Items//Start.png", g_screen);
    Start_Flag.init(FLAGS_FRAME, FLAGS_CLIPS);
    Start_Flag.set_pos(0,6*64);
    Sprite Cup;
    Cup.LoadImg("img/Items//End.png", g_screen);
    Cup.init(FLAGS_FRAME, FLAGS_CLIPS);
    Cup.set_pos(79*64, 5*64);
    Sprite Gun;
    Gun.LoadImg("img//GunPower.png", g_screen);
    Gun.init(BOX_FRAME, BOX_CLIPS);
    Sprite Door;
    Door.LoadImg("img/Items//Door.png", g_screen);
    Door.init(DOOR_FRAME, DOOR_CLIPS);
    Sprite Key;
    Key.LoadImg("img/Items//Key.png", g_screen);
    Key.init(KEY_FRAME, KEY_CLIPS);
    Sprite Grey;
    Grey.LoadImg("img/Items//Grey.png", g_screen);
    Grey.init(PLATE_FRAME, PLATE_CLIPS);
    Sprite Brown;
    Brown.LoadImg("img/Items//Brown.png", g_screen);
    Brown.init(PLATE_FRAME, PLATE_CLIPS);
    Sprite JetPack;
    JetPack.LoadImg("img/Items//JetPack.png", g_screen);
    JetPack.init(MAN_FRAMES, MAN_CLIPS);
    Sprite DangerSign;
    DangerSign.LoadImg("img/Items//DangerSign.png", g_screen);
    DangerSign.init(MAN_FRAMES, MAN_CLIPS);
    Sprite Rocket;
    Rocket.LoadImg("img/Items//Rocket.png", g_screen);
    Rocket.init(ROCKET_FRAME, ROCKET_CLIPS);

    BossObject bossObject;
    bossObject.CreateBoss(g_screen);
    Sprite BossDie;
    BossDie.LoadImg("img/Boss//BossDie.png", g_screen);
    BossDie.init(BOSS_FRAME, BOSS_CLIPS);
    BossDie.set_pos(MAX_MAP_X*TILE_SIZE - SCREEN_WIDTH*0.8, 4*64);

    string runR;
    string runL;
    string jumpL;
    string jumpR;
    int choose=0;
    int level = 1;

    MainObject p_player;

    p_player.SetBegin();
    p_player.UnSuper(runR, runL, jumpL, jumpR);
    PlayerHeart p_heart;
    p_heart.Init(g_screen);

    GameMap game_map;
    game_map.LoadTiles(g_screen);

    UINT mark_value = 0;
    int num_live = HEART;
    p_heart.SetHeart(HEART);
    bool is_quit = false;
    bool gap_boss = false;
    bool map_break = false;
    int time_real = SDL_GetTicks()/1000;
    bool update_power = false;
    int transition = 1;

    bool is_restart = false;
    bool is_lose = false;
    bool is_win = false;
    bool is_continue = false;
    bool is_stop = false;
    bool is_start = true;

    menu.StartMenu(g_screen,g_event);

    while(!is_quit){
        if(is_start){
            is_start = false;
            is_restart = false;
            is_lose = false;
            is_win = false;
            is_stop = false;
            is_continue = true;
            menu.restart_ = false;
            choose = menu.ChooseCharacter(g_screen,g_event);
            p_player.SelectCharacter(choose);
            p_player.LoadImg(p_player.RunR,g_screen);
            p_player.set_clips();
            runR = p_player.RunR;
            runL = p_player.RunL;
            jumpL = p_player.JumpL;
            jumpR = p_player.JumpR;

            level = menu.SellectLevel(g_screen, g_event, lv1, lv2, lv3, lv4);
            //level = 4;
            threats_list.clear();
            fruit_list.clear();
            collect_list.clear();
            box_list.clear();
            green_portal.clear();
            grey_portal.clear();

            if(level == 1){
                game_map.LoadMap("map/map01.txt");
                Gun.set_pos(41*64, 6*64);
                Fan.set_pos(81*64, 11*64+45);
                Door.set_pos(81*64, 11*64);
                Key.set_pos(81*64, 11*64);
                Grey.set_pos(81*64, 11*64);
                Brown.set_pos(81*64, 11*64);
                JetPack.set_pos(81*64, 11*64);
                Rocket.set_pos(81*64, 11*64);
                threats_list = MakeThreadList1();
                fruit_list = MakeFruitList1();
                collect_list = MakeCollected1();
            }
            else if(level == 2){
                game_map.LoadMap("map/map02.txt");
                Fan.set_pos(33*64, 6*64+45);
                Gun.set_pos(81*64, 11*64);
                Door.set_pos(81*64, 11*64);
                Key.set_pos(81*64, 11*64);
                Grey.set_pos(81*64, 11*64);
                Brown.set_pos(81*64, 11*64);
                JetPack.set_pos(81*64, 11*64);
                Rocket.set_pos(81*64, 11*64);
                threats_list = MakeThreadList2();
                fruit_list = MakeFruitList2();
                collect_list = MakeCollected2();
            }
            else if(level == 3){
                game_map.LoadMap("map/map03.txt");
                Fan.set_pos(29*64, 7*64+45);
                Gun.set_pos(34*64, 5*64);
                Door.set_pos(81*64, 11*64);
                Key.set_pos(81*64, 11*64);
                Grey.set_pos(81*64, 11*64);
                Brown.set_pos(81*64, 11*64);
                JetPack.set_pos(81*64, 11*64);
                Rocket.set_pos(81*64, 11*64);
                threats_list = MakeThreadList3();
                fruit_list = MakeFruitList3();
                collect_list = MakeCollected3();
                box_list = MakeBox3();
            }
            else if(level == 4){
                game_map.LoadMap("map/map04a.txt");
                Fan.set_pos(8*64, 7*64+45);
                Gun.set_pos(81*64, 11*64);
                Door.set_pos(34*64, 4*64);
                Key.set_pos(23*64+21, 2*64+17);
                Grey.set_pos(15*64, 8*64-10);
                Brown.set_pos(26*64, 6*64-10);
                JetPack.set_pos(37*64, 5*64);
                Rocket.set_pos(81*64, 11*64);
                green_portal = MakeGreenPortal();
                grey_portal = MakeGreyPortal();
            }
            else{
                game_map.LoadMap("map/map01.txt");
                Fan.set_pos(81*64, 11*64+45);
                Gun.set_pos(81*64, 11*64);
                Door.set_pos(81*64, 11*64);
                Key.set_pos(81*64, 11*64);
                Grey.set_pos(81*64, 11*64);
                Brown.set_pos(81*64, 11*64);
                JetPack.set_pos(81*64, 11*64);
                Rocket.set_pos(81*64, 11*64);
            }

            transition = 1;
            num_live = HEART;
            p_heart.SetHeart(HEART);
            is_quit = false;
            gap_boss = false;
            map_break = false;
            time_real = SDL_GetTicks()/1000;
            update_power = false;
            mark_value = 0;
            Gun.is_collect = false;
            Key.is_collect = false;
            Door.is_collect = false;
            JetPack.is_collect = false;
            Rocket.SetBegin();
            Grey.SetBegin();
            Brown.SetBegin();
            p_player.SetBegin();
            p_player.UnSuper(runR, runL, jumpL, jumpR);

        }
        if(is_continue){
            is_stop = false;
            is_win = false;
            is_lose = false;
            is_start = false;
            graphics.play(gMusic);
            fps_timer.start();
            while(SDL_PollEvent(&g_event)!=0){
                if(g_event.type==SDL_QUIT){
                is_quit = true;
            }
            p_player.HandelInputAction(g_event, g_screen, gun_sound, graphics);
            menu.ChangeVolumn(g_event, gJump, gun_sound, fruit_sound, super_power, boss_gun, disappear);
            menu.SellectRestart(g_event, is_restart);
            menu.Pause(g_event ,g_screen);
            }
            if(is_restart){
                is_restart = false;
                is_win = false;
                is_lose = false;
                is_stop = false;

                p_player.SetBegin();
                p_player.SetRect(-64,-64);
                p_player.UnSuper(runR, runL, jumpL, jumpR);
                Mix_HaltMusic();
                graphics.play(gMusic);

                num_live = HEART;
                p_heart.SetHeart(HEART);
                is_quit = false;
                gap_boss = false;
                map_break = false;
                time_real = SDL_GetTicks()/1000;
                update_power = false;
                mark_value = 0;
                transition = 1;
                Key.is_collect = false;
                Door.is_collect = false;
                Door.currentFrame = 0;
                Gun.is_collect = false;
                JetPack.is_collect = false;
                JetPack.set_pos(37*64, 5*64);
                DangerSign.SetBegin();
                Rocket.set_pos(81*64, 11*64);
                Rocket.SetBegin();
                Brown.SetBegin();
                Grey.SetBegin();
                bossObject.SetBegin();
                BossDie.is_collect = false;

                threats_list.clear();
                fruit_list.clear();
                collect_list.clear();
                box_list.clear();
                green_portal.clear();
                grey_portal.clear();

                if(level==1){
                    game_map.LoadMap("map/map01.txt");
                    threats_list = MakeThreadList1();
                    fruit_list = MakeFruitList1();
                    collect_list = MakeCollected1();
                }
                else if(level==2){
                    game_map.LoadMap("map/map02.txt");
                    threats_list = MakeThreadList2();
                    fruit_list = MakeFruitList2();
                    collect_list = MakeCollected2();
                }
                else if(level==3){
                    game_map.LoadMap("map/map03.txt");
                    threats_list = MakeThreadList3();
                    fruit_list = MakeFruitList3();
                    collect_list = MakeCollected3();
                    box_list = MakeBox3();
                }
                else if(level==4){
                    green_portal = MakeGreenPortal();
                    grey_portal = MakeGreyPortal();
                    game_map.LoadMap("map/map04a.txt");
                    Grey.set_pos(15*64, 8*64-10);
                    Brown.set_pos(26*64, 6*64-10);
                }

            }

            //SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);
            g_background.Render(g_screen,NULL);
            Map map_data = game_map.getMap();
            p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
            p_player.DoPlayer(map_data, g_screen, num_live, graphics, super_power);
            game_map.SetMap(map_data);
            game_map.DrawMap(g_screen);

            renderTexture(vien, 0, 0, g_screen);
            menu.RenderVolumnButton(g_screen);
            menu.RenderRestartButton(g_screen);
            menu.RenderPauseButton(g_screen);
            p_heart.SetHeart(num_live);
            p_heart.Show(g_screen);

            if(level == 1){
                RenderWithMap(map_data, hMove, g_screen, 20, 3*64);
                RenderWithMap(map_data, hCollect, g_screen, 21*64, 80);
                RenderWithMap(map_data, hClick, g_screen, 39*64, 4*64);
            }
            if(level != 4){
                Fan.RenderWithMap(map_data, g_screen);
                Fan.tick();
                Start_Flag.RenderWithMap(map_data, g_screen);
                Start_Flag.tick();
            }
            else{
                if(!transition){
                    Fan.RenderWithMap(map_data, g_screen);
                    Fan.tick();
                    if(!JetPack.is_collect){
                        JetPack.RenderWithMap(map_data, g_screen);
                    }
                    else{
                        JetPack.Render(p_player.GetRect().x +64, p_player.GetRect().y+14, g_screen);
                        JetPack.tick();
                    }
                    if(p_player.CollectItem(JetPack) && !JetPack.is_collect){
                        JetPack.is_collect = true;
                        p_player.jetpack = true;
                        Door.is_collect = false;
                        game_map.MapLock();
                    }
                    if(JetPack.is_collect == true){
                        if(Rocket.is_collect == false){
                            DangerSign.Render(SCREEN_WIDTH, p_player.GetRect().y, g_screen);
                            DangerSign.tick();
                            if(DangerSign.delay == MAX_DELAY - 1){
                                Rocket.is_collect = true;
                                Rocket.is_move = true;
                                Rocket.set_pos(p_player.get_x_pos() + SCREEN_WIDTH/2 , p_player.get_y_pos());
                            }
                        }
                        if(Rocket.is_move){
                            Rocket.RenderWithMap(map_data, g_screen);
                            Rocket.move3();
                            Rocket.tick();
                        }

                    }
                    Brown.RenderWithMap(map_data, g_screen);
                    if(p_player.CollectItem(Brown)){
                        p_player.Plate();
                        Brown.tick();
                        Brown.is_move = true;
                        Brown.move2(26*64, 26*64+4*64);
                        p_player.MoveWithPlate(Brown.dx);
                    }
                    else p_player.UnPlate();
                }
                else{
                    Start_Flag.RenderWithMap(map_data, g_screen);
                    Start_Flag.tick();
                    Grey.RenderWithMap(map_data, g_screen);
                    if(p_player.CollectItem(Grey)){
                        p_player.Plate();
                        Grey.tick();
                        Grey.is_move = true;
                        Grey.move2(15*64, 15*64+4*64);
                        p_player.MoveWithPlate(Grey.dx);
                    }
                    else p_player.UnPlate();
                }
                if(transition && !Key.is_collect) Key.RenderWithMap(map_data, g_screen);
                else if(!transition) Door.RenderWithMap(map_data, g_screen);
                if(transition && p_player.CollectItem(Key) && !Key.is_collect) Key.is_collect = true;
                if(Key.is_collect) Key.Render(1100, 6, g_screen);
                if(Key.is_collect && !transition && !Door.is_collect && p_player.CollectItem(Door)){
                    Door.is_collect = true;
                    Key.is_collect = false;
                }
                if(Door.is_collect) Door.currentFrame = 1;
                else Door.currentFrame = 0;
            }

            Cup.RenderWithMap(map_data,g_screen);
            Cup.tick();

            if(update_power && !Gun.is_collect){
                Gun.RenderWithMap(map_data, g_screen);
                Gun.tick();
                if(p_player.CollectItem(Gun)){
                    p_player.Super(g_screen, graphics, super_power);
                    Gun.is_collect = true;
                }
            }
            if(p_player.CollectItem(Fan)) p_player.Bay();

            for(int i=0; i<green_portal.size(); i++){
                Sprite* portal = green_portal[i];
                if(portal!=nullptr && transition){
                    portal->RenderWithMap(map_data, g_screen);
                    portal->tick();
                    bool isCollect = p_player.CollectItem(*portal);
                    if(isCollect) portal->is_collect = true;
                    if(portal->is_collect){
                        transition = (transition+1)%2;
                        game_map.LoadMap("map/map04b.txt");
                        portal->Free();
                        green_portal.erase(green_portal.begin()+i);
                    }
                }
                else if(portal == nullptr) portal->Free();
            }
            for(int i=0; i<grey_portal.size(); i++){
                Sprite* portal = grey_portal[i];
                if(portal!=nullptr && !transition){
                    portal->RenderWithMap(map_data, g_screen);
                    portal->tick();
                    bool isCollect = p_player.CollectItem(*portal);
                    if(isCollect) portal->is_collect = true;
                    if(portal->is_collect){
                        transition = (transition+1)%2;
                        game_map.LoadMap("map/map04a.txt");
                        portal->Free();
                        grey_portal.erase(grey_portal.begin()+i);
                    }
                }
                else if(portal == nullptr) portal->Free();
            }
            for(int i=0; i<fruit_list.size() ; i++){
                Sprite* fruit = fruit_list[i];
                Sprite* collect = collect_list[i];
                if(fruit!=nullptr){
                    fruit->RenderWithMap(map_data,g_screen);
                    fruit->tick();
                    bool isCollect = p_player.CollectItem(*fruit);
                    if(isCollect) collect->is_collect = true;
                    if(collect->is_collect){
                        collect->RenderWithMap(map_data, g_screen);
                        collect->tick();
                        if(collect->currentFrame == 5){
                            fruit->Free();
                            fruit_list.erase(fruit_list.begin()+i);
                            collect->Free();
                            collect_list.erase(collect_list.begin()+i);
                            mark_value += 100;
                            graphics.play(fruit_sound);
                        }
                    }
                }
                else{
                    fruit->Free();
                    collect->Free();
                }
            }
            for(int i=0; i<box_list.size(); i++){
                Sprite* box = box_list[i];
                if(box!=nullptr){
                    box->RenderWithMap(map_data, g_screen);
                    bool isCollect = p_player.CollectItem(*box);
                    if(isCollect) box->is_collect=true;
                    if(box->is_collect){
                        box->tick();
                        if(box->currentFrame == 9){
                            p_player.Khong();
                            box->Free();
                            box_list.erase(box_list.begin()+i);
                        }
                    }
                }
                else box->Free();
            }
            bool Va1 = false;
            bool Va2 = false;
            for(int i=0 ; i<threats_list.size() ; i++){
                ThreatsObject* p_threat = threats_list[i];
                if(p_threat != NULL)
                {
                    p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                    p_threat->ImpMoveType(g_screen);
                    p_threat->DoPlayer(map_data);
                    p_threat->MakeBullet(g_screen,SCREEN_WIDTH,SCREEN_HEIGHT,map_data);
                    p_threat->Show(g_screen);
                    SDL_Rect tRect = p_threat->GetRectFrame();
                    SDL_Rect pRect = p_player.GetRectFrame();
                    bool killquai = SDLCommonFunc::CheckVaQuai(pRect,tRect);
                    if(killquai){
                        p_player.Nhay();
                        graphics.play(disappear);
                        for(int ex = 0; ex<NUM_FRAME_EXP ; ex++){
                                    int x_pos = p_threat->GetRect().x;
                                    int y_pos = p_threat->GetRect().y;
                                    explosion_.set_frame(ex);
                                    explosion_.SetRect(x_pos, y_pos);
                                    explosion_.Show(g_screen);
                                }
                        p_threat->Free();
                        threats_list.erase(threats_list.begin()+i);
                        mark_value += 100;
                    }
                    else{
                        vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                        for(int j =0; j<tBullet_list.size(); j++){
                            BulletObject* pt_bullet = tBullet_list[j];
                            if(pt_bullet){
                                Va1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), pRect);
                                if(Va1){
                                    p_threat->RemoveBullet(j);
                                    break;
                                }
                            }
                        }
                        Va2 = SDLCommonFunc::CheckCollision(pRect, tRect);
                        if(Va1 || Va2) break;
                    }
                }
            }
            if(!bossObject.IsLive() && !BossDie.is_collect && level==3){
                BossDie.RenderWithMap(map_data, g_screen);
                BossDie.tick();
                if(BossDie.currentFrame == 31) BossDie.is_collect = true;
            }
            bool VaBoss = false;
            bool BulletBoss = false;
            if(level==3 && bossObject.get_x_pos() - p_player.get_x_pos() <= (SCREEN_WIDTH/2)) gap_boss = true;
            if(gap_boss && bossObject.IsLive() ){
                bossObject.SetMapXY(map_data.start_x_, map_data.start_y_);
                bossObject.DoPlayer(map_data);
                bossObject.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT, map_data, p_player.get_x_pos(), p_player.get_y_pos(), graphics, boss_gun);
                bossObject.Show(g_screen);
                bossObject.ShowHeart(g_screen, map_data);
                SDL_Rect bossRect = bossObject.GetRectFrame();
                SDL_Rect pRect = p_player.GetRectFrame();
                VaBoss = SDLCommonFunc::CheckCollision(pRect, bossRect);
                vector<BulletObject*> bullet_boss = bossObject.get_bullet_list();
                for(int j =0; j<bullet_boss.size(); j++){
                    BulletObject* bullet_ = bullet_boss[j];
                    if(bullet_){
                        BulletBoss = SDLCommonFunc::CheckCollision(bullet_->GetRect(), pRect);
                        if(BulletBoss){
                            bossObject.ClearBullet();
                            break;
                        }
                    }
                }
            }
            if(Va1 || Va2 || VaBoss || BulletBoss){
                graphics.play(disappear);
                int width_exp_frame = explosion_.get_frame_width();
                int height__exp_frame = explosion_.get_frame_height();
                for(int ex=0; ex<NUM_FRAME_EXP; ex++){
                    int x_pos = (p_player.GetRectFrame().x + p_player.GetRectFrame().w*0.5 - width_exp_frame*0.5);
                    int y_pos = (p_player.GetRectFrame().y + p_player.GetRectFrame().h*0.5 - height__exp_frame*0.5);
                    explosion_.set_frame(ex);
                    explosion_.SetRect(x_pos, y_pos);
                    explosion_.Show(g_screen);
                    SDL_RenderPresent(g_screen);
                    SDL_Delay(30);
                }
                num_live--;
                if(num_live > 0){
                    p_player.SetRect(-64,-64);
                    p_player.set_come_back_time(60);
                    p_heart.Decrease();
                    SDL_Delay(1000);
                    continue;
                }
            }
            bool VaRocket = SDLCommonFunc::CheckCollision(p_player.GetRectFrame(), Rocket.GetRect());
            if(VaRocket){
                graphics.play(disappear);
                int width_exp_frame = explosion_.get_frame_width();
                int height__exp_frame = explosion_.get_frame_height();
                for(int ex=0; ex<NUM_FRAME_EXP; ex++){
                    int x_pos = (p_player.GetRectFrame().x + p_player.GetRectFrame().w*0.5 - width_exp_frame*0.5);
                    int y_pos = (p_player.GetRectFrame().y + p_player.GetRectFrame().h*0.5 - height__exp_frame*0.5);
                    explosion_.set_frame(ex);
                    explosion_.SetRect(x_pos, y_pos);
                    explosion_.Show(g_screen);
                    SDL_RenderPresent(g_screen);
                    SDL_Delay(30);
                }
                num_live--;
                if(num_live > 0){
                    p_player.SetRect(-64,-64);
                    p_player.set_come_back_time(60);
                    p_heart.Decrease();
                    SDL_Delay(1000);
                    continue;
                }
            }
            if(num_live<=0){
                is_lose = true;
                is_continue = false;
            }

            //Hinh anh load sau dong nay
            p_player.Show(g_screen);
            p_player.HandleBullet(g_screen,map_data);

            int frame_exp_width = explosion_.get_frame_width();
            int frame_exp_height = explosion_.get_frame_height();

            vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
            for(int r =0 ; r<bullet_arr.size(); r++){
                BulletObject* p_bullet = bullet_arr[r];
                if(p_bullet!=NULL)
                {
                    SDL_Rect bRect = p_bullet->GetRect();
                    for(int t=0 ; t<threats_list.size(); t++){
                        ThreatsObject* obj_threat = threats_list[t];
                        if(obj_threat!=NULL){
                            SDL_Rect tRect = obj_threat->GetRectFrame();
                            bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
                            if(bCol){
                                graphics.play(disappear);
                                mark_value += 100;
                                for(int ex = 0; ex<NUM_FRAME_EXP ; ex++){
                                    int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
                                    int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;
                                    explosion_.set_frame(ex);
                                    explosion_.SetRect(x_pos, y_pos);
                                    explosion_.Show(g_screen);
                                }
                                p_player.RemoveBullet(r);
                                obj_threat->Free();
                                threats_list.erase(threats_list.begin()+t);
                            }
                        }
                    }
                    bool BanBoss = false;
                    if(gap_boss && bossObject.IsLive()){
                        SDL_Rect bossRect = bossObject.GetRectFrame();
                        BanBoss = SDLCommonFunc::CheckCollision(bRect, bossRect);
                        if(BanBoss){
                            p_player.RemoveBullet(r);
                            bossObject.BanBoss();
                        }
                    }
                }
            }

            if(p_player.CollectItem(Cup)){
                is_win = true;
                is_continue = false;
                ofstream ghifile("map//Level.txt");
                if(level == 1){
                    lv2 = 1;
                    ghifile<<lv1<<" "<<lv2<<" "<<lv3<<" "<<lv4<<endl;
                }
                else if(level == 2){
                    lv3 =1;
                    ghifile<<lv1<<" "<<lv2<<" "<<lv3<<" "<<lv4<<endl;
                }
                else if(level ==3){
                    lv4 = 1;
                    ghifile<<lv1<<" "<<lv2<<" "<<lv3<<" "<<lv4<<endl;
                }
                else{
                    ghifile<<lv1<<" "<<lv2<<" "<<lv3<<" "<<lv4<<endl;
                }
                ghifile.close();
                ofstream ghidiem("map//HighScore.txt");
                ghidiem<<HighScore;
                ghidiem.close();
            }

            string str_time = "Map break in: ";
            Uint32 time_tick = SDL_GetTicks()/1000;
            int val_time = time_tick - time_real;
            int idx = val_time;

            if(level == 3){
                if(val_time == MAX_TIME){
                    map_break = true;
                }
                else if(!map_break){
                    string str_val = to_string(MAX_TIME - val_time);
                    str_time += str_val;
                    time_game.SetText(str_time);
                    time_game.LoadFromRenderText(font_time, g_screen);
                    time_game.RenderText(g_screen,SCREEN_WIDTH-400, -2);
                }
                else{
                    string s = "Map is breaking!!";
                    time_game.SetText(s);
                    time_game.LoadFromRenderText(font_time, g_screen);
                    time_game.RenderText(g_screen,SCREEN_WIDTH-450, -2);
                }
            }

            if(map_break  && level==3){
                game_map.MapBreak(idx-MAX_TIME);
            }
            if((mark_value == 1700 && level==3) || level ==1){
                update_power = true;
            }

            string val_str_mark = to_string(mark_value);
            string strMark("Score: ");
            strMark+= val_str_mark;
            mark_game.SetText(strMark);
            mark_game.LoadFromRenderText(font_time, g_screen);
            mark_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 50, -2);

            if(mark_value > HighScore) HighScore = mark_value;
            string high_val = to_string(HighScore);
            string highMark("Highscore: ");
            highMark +=high_val;
            high_score.SetText(highMark);
            high_score.LoadFromRenderText(font_time, g_screen);
            high_score.RenderText(g_screen, 200, -2);

            SDL_RenderPresent(g_screen);

            int real_imp_time = fps_timer.get_ticks();
            int time_one_frame = 1000/FRAME_PER_SECOND;
            if(real_imp_time < time_one_frame)
            {
                int delay_time = time_one_frame - real_imp_time;
                if(delay_time >=0 ) SDL_Delay(delay_time);
            }
        }
        if(is_stop){
            Mix_HaltMusic();

            threats_list.clear();
            is_continue = false;
            is_win = false;
            is_lose = false;
            is_quit = true;
        }
        if(is_win){
            Mix_HaltMusic();
            is_lose = false;

            menu.MenuWin(g_screen, g_event);
            is_start = menu.restart_;
            is_stop = !is_start;

            is_win = false;
        }
        if(is_lose){
            is_win = false;
            Mix_HaltMusic();

            menu.MenuGameOver(g_screen, g_event);
            is_start = menu.restart_;
            is_stop = !is_start;

            is_lose = false;
        }

    }

    close();
    return 0;
}
