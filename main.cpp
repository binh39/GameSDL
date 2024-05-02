#include "CommonFunction.h"
#include "graphics.h"
#include "BaseObject.h"
#include "game_map.h"
#include "mainObject.h"
#include "time.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include "PlayerPower.h"
#include "Geometric.h"
#include "BossObject.h"

BaseObject g_background;
TTF_Font* font_time;

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

    if( InitData() == false) return -1;
    if(LoadBackground() == false) return -2;

    Begin:

    int choose=0;
    ImpTimer fps_timer;

    bool is_lose = false;
    bool is_win = false;
    bool is_continue = false;
    bool is_stop = false;
    Menu menu;
    menu.restart_ = false;
    menu.StartMenu(g_screen,g_event);
    choose = menu.ChooseCharacter(g_screen,g_event);
    menu.LoadVolumnButton(g_screen);

    Graphics graphics;
    Mix_Music* gMusic = graphics.loadMusic("sound//cafe_boba_short.mp3");
    graphics.play(gMusic);
    Mix_Chunk *gJump = graphics.loadSound("sound//jump.wav");
    graphics.play(gJump);

    MainObject p_player;
    p_player.SelectCharacter(choose);
    p_player.LoadImg(p_player.RunR,g_screen);
    p_player.set_clips();

    PlayerPower player_power;
    player_power.Init(g_screen);
    PlayerMoney player_money;
    player_money.Init(g_screen);
    player_money.SetPos(SCREEN_WIDTH*0.5-300, 8);

    GameMap game_map;
    game_map.LoadMap("map/map02.txt");
    game_map.LoadTiles(g_screen);

    vector<ThreatsObject*> threats_list = MakeThreadList();

    //Boss
    BossObject bossObject;
    bossObject.LoadImg("img/Boss//boss_object.png", g_screen);
    bossObject.set_clips();
    int xPosBoss = MAX_MAP_X*TILE_SIZE - SCREEN_WIDTH*0.8;
    bossObject.set_xpos(xPosBoss);
    bossObject.set_ypos(10);

    ExplosionObject explosion_;
    bool tRet = explosion_.LoadImg("img//Explosion.png", g_screen);
    if(!tRet){
        cout << "Error LoadImg Explosion\n";
        return -1;
    }
    explosion_.set_clip();

    int num_die = 0;

    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);
    TextObject mark_game;
    mark_game.SetColor(TextObject::WHITE_TEXT);
    UINT mark_value = 0;
    TextObject money_game;
    money_game.SetColor(TextObject::WHITE_TEXT);




    bool is_quit = false;
    bool gap_boss = false;
    bool map_break = false;

    while(!is_quit){
        fps_timer.start();
        SDL_Event test;
        while(SDL_PollEvent(&g_event)!=0){
            if(g_event.type==SDL_QUIT){
                is_quit = true;
            }
            p_player.HandelInputAction(g_event, g_screen);
            menu.ChangeVolumn(g_event, gJump);
        }

        SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        g_background.Render(g_screen,NULL);
        Map map_data = game_map.getMap();
        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data, graphics, gJump, g_screen);
        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        GeomytricFormat rectangle_size(0,0, SCREEN_WIDTH, 40);
        ColorData color_data(0,50,180);
        Geomytric :: RenderRectangle(rectangle_size, color_data, g_screen);
        GeomytricFormat outlineSize(1, 1, SCREEN_WIDTH-2, 38);
        ColorData color_data2(255,255,255);
        Geomytric :: RenderOutline(outlineSize, color_data2, g_screen);

        player_power.Show(g_screen);
        player_money.Show(g_screen);

        menu.RenderVolumnButton(g_screen);

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
                    for(int ex = 0; ex<NUM_FRAME_EXP ; ex++){
                                int x_pos = p_threat->GetRect().x;
                                int y_pos = p_threat->GetRect().y;
                                explosion_.set_frame(ex);
                                explosion_.SetRect(x_pos, y_pos);
                                explosion_.Show(g_screen);
                            }
                    p_threat->Free();
                    threats_list.erase(threats_list.begin()+i);
                    cout<<"Kill Threat success\n";
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

        //Boss
        bool VaBoss = false;
        bool BulletBoss = false;
        if( bossObject.get_x_pos() - p_player.get_x_pos() <= (SCREEN_WIDTH/2)) gap_boss = true;
        if(gap_boss && bossObject.IsLive()){
            bossObject.SetMapXY(map_data.start_x_, map_data.start_y_);
            bossObject.DoPlayer(map_data);
            bossObject.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT, map_data);
            bossObject.Show(g_screen);

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
            num_die++;
            if(num_die < 3){
                p_player.SetRect(0,0);
                p_player.set_come_back_time(60);
                player_power.Decrease();
                player_power.Render(g_screen);
                SDL_Delay(1000);
                continue;
            }
            else{
                        /*if(MessageBox(NULL, "GAME OVER", "Info", MB_OK | MB_ICONSTOP) == IDOK){
                            p_threat->Free();
                            close();
                            SDL_Quit();
                            return 0;
                            }*/
                is_lose = true;
                is_quit = true;
                break;
            }
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
                            p_player.IncreaseMoney();
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
                        cout<<bossObject.CheckLive()<<endl;
                    }
                }
            }
        }
        //Show game time
        string str_time = "Map break in: ";
        Uint32 time_val = SDL_GetTicks()/1000;
        Uint32 val_time = MAX_TIME - time_val;
        int idx = time_val;
        if(val_time <= 0){
            map_break = true;
        }
        else if(!map_break){
            string str_val = to_string(val_time);
            str_time += str_val;
            time_game.SetText(str_time);
            time_game.LoadFromRenderText(font_time, g_screen);
            time_game.RenderText(g_screen,SCREEN_WIDTH-400, 0);
        }
        else{
            string s = "Map is breaking!!";
            time_game.SetText(s);
            time_game.LoadFromRenderText(font_time, g_screen);
            time_game.RenderText(g_screen,SCREEN_WIDTH-400, 0);
        }

        if(map_break){
            game_map.MapBreak(idx-20);
        }

        string val_str_mark = to_string(mark_value);
        string strMark("Score: ");
        strMark+= val_str_mark;
        mark_game.SetText(strMark);
        mark_game.LoadFromRenderText(font_time, g_screen);
        mark_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 50, 0);

        int money_count = p_player.GetMoneyCount();
        string money_str = to_string(money_count);
        money_game.SetText(money_str);
        money_game.LoadFromRenderText(font_time, g_screen);
        money_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 200, 0);

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
    if(is_lose){
        menu.MenuGameOver(g_screen, g_event);
        is_continue = menu.restart_;
        if(is_continue) goto Begin;
    }
    else if(is_win){
        menu.MenuWin(g_screen, g_event);
        is_continue = menu.restart_;
        if(is_continue) goto Begin;
    }

    close();
    return 0;
}
