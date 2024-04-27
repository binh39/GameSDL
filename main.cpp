#include "CommonFunction.h"
#include "graphics.h"
#include "BaseObject.h"
#include "game_map.h"
#include "mainObject.h"
#include "time.h"
#include "ThreatsObject.h"

BaseObject g_background;

void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,"%s: %s", msg, error);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
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

void close(){
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

vector<ThreatsObject*> MakeThreadList()
{
    vector<ThreatsObject*> list_threats;
    ThreatsObject* dynamic_threats = new ThreatsObject[3];
    for(int i=0; i<3 ; i++)
    {
        ThreatsObject* p_threat = (dynamic_threats+i);
        if(p_threat != NULL)
        {
            p_threat->LoadImg("img/Enemy/BunnyL.png",g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(7*64+i*64*6);
            p_threat->set_y_pos(200);

            int pos1 = p_threat->get_x_pos()-60;
            int pos2 = p_threat->get_x_pos()+60;
            p_threat->SetAnimationPos(pos1,pos2);
            p_threat->set_input_left(1);
            list_threats.push_back(p_threat);
        }
    }

    ThreatsObject* threats_objs = new ThreatsObject[20];
    for(int i=0 ; i<20 ; i++)
    {
        ThreatsObject* p_threat = (threats_objs+i);
        if(i%2==0)
        {
            if(p_threat != NULL)
        {
            p_threat->LoadImg("img/Enemy/Plant.png",g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos(5*64+i*64*3);
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_input_left(0);

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);

            list_threats.push_back(p_threat);
        }
        }
        else
        {
            if(p_threat != NULL)
        {
            p_threat->LoadImg("img/Enemy/Turtle.png",g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos(5*64+i*64*3);
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_input_left(0);
            list_threats.push_back(p_threat);
        }
        }

    }
    return list_threats;
}

using namespace std;

int main(int argc,char* argv[])
{
    int choose=0;
    ImpTimer fps_timer;

    if( InitData() == false) return -1;
    if(LoadBackground() == false) return -2;

    Menu menu;
    menu.StartMenu(g_screen,g_event);
    choose = menu.ChooseCharacter(g_screen,g_event);
    //waitUntilKeyPressed();

    GameMap game_map;
    game_map.LoadMap("map/map02.txt");
    game_map.LoadTiles(g_screen);

    MainObject p_player;

    p_player.SelectCharacter(choose);
    //waitUntilKeyPressed();
    p_player.LoadImg(p_player.RunR,g_screen);
    p_player.set_clips();

    vector<ThreatsObject*> threats_list = MakeThreadList();

    Graphics graphics;
    Mix_Music* gMusic = graphics.loadMusic("sound//cafe_boba_short.mp3");
    graphics.play(gMusic);
    Mix_Chunk *gJump = graphics.loadSound("sound//jump.wav");
    graphics.play(gJump);


    bool is_quit = false;

    while(!is_quit){
            fps_timer.start();
        while(SDL_PollEvent(&g_event)!=0){
            if(g_event.type==SDL_QUIT){
                is_quit = true;
            }
            p_player.HandelInputAction(g_event, g_screen);
        }

        SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        g_background.Render(g_screen,NULL);
        Map map_data = game_map.getMap();
        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data, graphics, gJump);
        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        for(int i=0 ; i<threats_list.size() ; i++){
            ThreatsObject* p_threat = threats_list[i];
            if(p_threat != NULL)
            {
                p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threat->ImpMoveType(g_screen);
                p_threat->DoPlayer(map_data);
                p_threat->MakeBullet(g_screen,SCREEN_WIDTH,SCREEN_HEIGHT,map_data);
                p_threat->Show(g_screen);

                SDL_Rect rect_player = p_player.GetRectFrame();
                bool bCol1 = false;
                vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                for(int jj =0; jj<tBullet_list.size(); jj++){
                    BulletObject* pt_bullet = tBullet_list[jj];
                    if(pt_bullet){
                        bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
                        if(bCol1){
                            p_threat->RemoveBullet(jj);
                            break;
                        }
                    }
                }
                SDL_Rect rect_threat = p_threat->GetRectFrame();
                bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
                if(bCol1 || bCol2){
                    if(MessageBox(NULL, "GAME OVER", "Info", MB_OK | MB_ICONSTOP) == IDOK){
                        p_threat->Free();
                        close();
                        SDL_Quit();
                        return 0;
                    }
                }
            }
        }
        //Hinh anh load sau dong nay
        p_player.Show(g_screen);
        p_player.HandleBullet(g_screen,map_data);

        vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        cout<< bullet_arr.size()<<endl;
        for(int r =0 ; r<bullet_arr.size(); r++){
            BulletObject* p_bullet = bullet_arr[r];
            if(p_bullet!=NULL)
            {
                for(int t=0 ; t<threats_list.size(); t++){
                    ThreatsObject* obj_threat = threats_list[t];
                    if(obj_threat!=NULL){
                        SDL_Rect tRect;
                        tRect.x = obj_threat->GetRect().x;
                        tRect.y = obj_threat->GetRect().y;
                        tRect.w = obj_threat->get_width_frame();
                        tRect.h = obj_threat->get_height_frame();
                        SDL_Rect bRect = p_bullet->GetRect();
                        bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
                        if(bCol){
                            p_player.RemoveBullet(r);
                            obj_threat->Free();
                            threats_list.erase(threats_list.begin()+t);
                        }
                    }
                }
            }

        }

        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND; //ms
        if(real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time >=0 ) SDL_Delay(delay_time);
        }

    }

    for(int i=0; i<threats_list.size(); i++)
    {
        ThreatsObject* p_threat = threats_list[i];
        if(p_threat)
        {
            p_threat->Free();
            p_threat=NULL;
        }
    }

    threats_list.clear();
    close();
    return 0;
}
