#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "CommonFunction.h"

using namespace std;

#define PLATE_SPEED 3
#define ROCKET_SPEED 20
#define MAX_DELAY 48

const int MAN_CLIPS[][4] = {
    {  0, 0, 64, 64},
    { 64, 0, 64, 64},
    { 128, 0, 64, 64},
    { 192, 0, 64, 64},
    {256, 0, 64, 64},
    {320, 0, 64, 64},
    {384, 0, 64, 64},
    {448, 0, 64, 64},
    {512, 0, 64, 64},
    {576, 0, 64, 64},
    {640, 0, 64, 64},
    {704, 0, 64, 64}};
const int MAN_FRAMES = 12;

const int MAN_CLIPS_2[][4] = {
    {  128*0, 0, 128, 128},
    { 128*1, 0, 128, 128},
    { 128*2, 0, 128, 128},
    { 128*3, 0, 128, 128},
    { 128*4, 0, 128, 128},
    { 128*5, 0, 128, 128},
    { 128*6, 0, 128, 128},
    { 128*7, 0, 128, 128},
    { 128*8, 0, 128, 128},
    { 128*9, 0, 128, 128},
    { 128*10, 0, 128, 128},
    { 128*11, 0, 128, 128}};
const int MAN_FRAMES_2 = 12;

const int MAN_CLIPS_3[][4] = {
    {256*0, 0, 256, 256},
    {256*1, 0, 256, 256},
    {256*2, 0, 256, 256},
    {256*3, 0, 256, 256},
    {256*4, 0, 256, 256},
    {256*5, 0, 256, 256},
    {256*6, 0, 256, 256},
    {256*7, 0, 256, 256},
    {256*8, 0, 256, 256},
    {256*9, 0, 256, 256},
    {256*10, 0, 256, 256},
    {256*11, 0, 256, 256}};
const int MAN_FRAMES_3 = 12;

const int FRUITS_CLIPS[][4] = {
    {  0, 0, 32, 32},
    { 32, 0, 32, 32},
    { 64, 0, 32, 32},
    { 96, 0, 32, 32},
    {128, 0, 32, 32},
    {160, 0, 32, 32},
    {192, 0, 32, 32},
    {224, 0, 32, 32},
    {256, 0, 32, 32},
    {288, 0, 32, 32},
    {320, 0, 32, 32},
    {352, 0, 32, 32},
    {384, 0, 32, 32},
    {416, 0, 32, 32},
    {448, 0, 32, 32},
    {480, 0, 32, 32},
    {512, 0, 32, 32}};
const int FRUITS_FRAME = 17;

const int FRUITS_CLIPS_2[][4] = {
    {  0, 0, 64, 64},
    { 64, 0, 64, 64},
    { 128, 0, 64, 64},
    { 192, 0, 64, 64},
    {256, 0, 64, 64},
    {320, 0, 64, 64},
    {384, 0, 64, 64},
    {448, 0, 64, 64},
    {512, 0, 64, 64},
    {576, 0, 64, 64},
    {640, 0, 64, 64},
    {704, 0, 64, 64},
    {768, 0, 64, 64},
    {832, 0, 64, 64},
    {896, 0, 64, 64},
    {960, 0, 64, 64},
    {1024, 0, 64, 64},};
const int FRUITS_FRAME_2 = 12;

const int FLAGS_CLIPS[][4] = {
    {  0, 0, 64, 64},
    { 64, 0, 64, 64},
    { 128, 0, 64, 64},
    { 192, 0, 64, 64},
    {256, 0, 64, 64},
    {320, 0, 64, 64},
    {384, 0, 64, 64},
    {448, 0, 64, 64},
    {512, 0, 64, 64},
    {576, 0, 64, 64},
    {640, 0, 64, 64},
    {704, 0, 64, 64},
    {768, 0, 64, 64},
    {832, 0, 64, 64},
    {896, 0, 64, 64},
    {960, 0, 64, 64}};
const int FLAGS_FRAME = 16;

const int COLLECTED_CLIPS[][4] = {
    {  0, 0, 32, 32},
    { 32, 0, 32, 32},
    { 64, 0, 32, 32},
    { 96, 0, 32, 32},
    {128, 0, 32, 32},
    {160, 0, 32, 32}};
const int COLLECTED_FRAME = 6;

const int COLLECTED_CLIPS_2[][4] = {
    {  0, 0, 64, 64},
    { 64, 0, 64, 64},
    { 128, 0, 64, 64},
    { 192, 0, 64, 64},
    {256, 0, 64, 64},
    {320, 0, 64, 64}};
const int COLLECTED_FRAME_2 = 6;

const int HEART_CLIPS_3[][4] = {
    {  0, 0, 60, 60},
    { 60, 0, 60, 60},
    { 120, 0, 60, 60},
    { 180, 0, 60, 60},
    {240, 0, 60, 60},
    {300, 0, 60, 60},
    {360, 0, 60, 60},
    {420, 0, 60, 60}};
const int HEART_FRAME_3 = 8;

const int BOSS_CLIPS[][4] = {
    {0, 0, 91, 132},
    {91, 0, 91, 132},
    {182, 0, 91, 132},
    {273, 0, 91, 132},
    {364, 0, 91, 132},
    {455, 0, 91, 132},
    {546, 0, 91, 132},
    {637, 0, 91, 132},
    {728, 0, 91, 132},
    {819, 0, 91, 132},
    {910, 0, 91, 132},
    {1001, 0, 91, 132},
    {1092, 0, 91, 132},
    {1183, 0, 91, 132},
    {1274, 0, 91, 132},
    {1365, 0, 91, 132},
    {1456, 0, 91, 132},
    {1547, 0, 91, 132},
    {1638, 0, 91, 132},
    {1729, 0, 91, 132},
    {1820, 0, 91, 132},
    {1911, 0, 91, 132},
    {2002, 0, 91, 132},
    {2093, 0, 91, 132},
    {2184, 0, 91, 132},
    {2275, 0, 91, 132},
    {2366, 0, 91, 132},
    {2457, 0, 91, 132},
    {2548, 0, 91, 132},
    {2639, 0, 91, 132},
    {2730, 0, 91, 132},
    {2821, 0, 91, 132}};
const int BOSS_FRAME = 32;

const int FAN_CLIPS[][4] = {
    { 0, 0, 64, 21},
    { 64, 0, 64, 21},
    { 128, 0, 64, 21},
    { 192, 0, 64, 21},
    { 256, 0, 64, 21},
    { 320, 0, 64, 21},
    { 384, 0, 64, 21},
    { 448, 0, 64, 21}};
const int FAN_FRAME = 8;

const int PLATE_CLIPS[][4] = {
    { 0, 0, 64, 14},
    { 64, 0, 64, 14},
    { 128, 0, 64, 14},
    { 192, 0, 64, 14},
    { 256, 0, 64, 14},
    { 320, 0, 64, 14},
    { 384, 0, 64, 14},
    { 448, 0, 64, 14}};
const int PLATE_FRAME = 8;

const int ROCKET_CLIPS[][4] = {
    { 0, 0, 64, 41},
    { 64, 0, 64, 41},
    { 128, 0, 64, 41},
    { 192, 0, 64, 41},
    { 256, 0, 64, 41},
    { 320, 0, 64, 41},
    { 384, 0, 64, 41},
    { 448, 0, 64, 41}};
const int ROCKET_FRAME = 8;

const int BOX_CLIPS[][4] = {
    {  0, 0, 64, 64},
    { 64, 0, 64, 64},
    {128, 0, 64, 64},
    {192, 0, 64, 64},
    {256, 0, 64, 64},
    {320, 0, 64, 64},
    {384, 0, 64, 64},
    {448, 0, 64, 64},
    {512, 0, 64, 64},
    {576, 0, 64, 64}};
const int BOX_FRAME = 10;

const int DOOR_CLIPS[][4] = {
    {0, 0, 64, 128},
    {64, 0, 64, 128}};
const int DOOR_FRAME  = 2;

const int KEY_CLIPS[][4] = {
    {0, 0, 12, 30}};
const int KEY_FRAME = 1;

struct ScrollingBackground{
    SDL_Texture* texture;
    int scrollingOffset = 0;
    int width, height;

    void setTexture(SDL_Renderer* renderer);
    void scroll(int distance);
};

struct Sprite{
    SDL_Texture* texture;
    vector<SDL_Rect> clips;
    int currentFrame = 0;
    int delay = 0;
    int x=0;
    int y=0;

    int dx=0;
    int x_pos=0;
    int y_pos=0;
    int width_frame_=0;
    int height_frame_=0;

    bool is_collect = false;
    bool is_move = false;
    int huong = 1;

    void init(int frames, const int _clips[][4]);
    void tick();
    const SDL_Rect* getCurrentClip() const;
    void LoadImg(const char* name, SDL_Renderer* renderer);
    void Render(int x, int y, SDL_Renderer* renderer);
    void RenderWithMap(Map& map_data, SDL_Renderer* renderer);
    void set_pos(const int& xp, const int& yp){x_pos = xp; y_pos = yp;}
    void move();
    void move2(const int& x_left, const int& x_right);
    void move3();
    SDL_Rect GetRect();
    void SetBegin();
    void Free();
};

struct Graphics {
    Mix_Music *loadMusic(const char* path);
    void play(Mix_Music *gMusic);
    Mix_Chunk* loadSound(const char* path);
    void play(Mix_Chunk* gChunk);
};

struct Menu {
    SDL_Texture *background_menu;
    bool restart_ = false;
    int volumn_ = 1;
    SDL_Texture* volumn_on;
    SDL_Texture* volumn_off;
    SDL_Texture* res;
    SDL_Texture* pause;
    SDL_Texture* backgr;

    SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,"Loading %s", filename);
        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,"Load texture %s", IMG_GetError());
        }
        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y, SDL_Renderer* renderer)
    {
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void LoadBackgroundMenu(const char *filename, SDL_Renderer* renderer){
        background_menu = loadTexture(filename, renderer);
        SDL_RenderCopy(renderer, background_menu,NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_Texture* LoadButton(const char *filename, SDL_Renderer* renderer){
        SDL_Texture* button = loadTexture(filename, renderer);
        return button;
    }

    void StartMenu(SDL_Renderer* renderer, SDL_Event event){

        ScrollingBackground SBackground;
        SBackground.setTexture(renderer);

        Sprite Man;
        Man.LoadImg("img/NinjaFrog//RunR.png", renderer);
        Man.init(MAN_FRAMES, MAN_CLIPS);

        SDL_Texture* pixel_adventure = LoadButton("img/button//PixelAdventure.png", renderer);
        SDL_Texture* start1 = LoadButton("img/button//Start1.png", renderer);
        SDL_Texture* start2 = LoadButton("img/button//Start2.png", renderer);

        SDL_RenderPresent(renderer);

        bool quit=false;
        int x=0,y=0;
        while(!quit)
        {
            //SDL_Texture* start1 = LoadButton("img/button//Start1.png", renderer);
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT) exit(0);
            SDL_GetMouseState(&x,&y);

            SBackground.scroll(1);
            renderTexture(SBackground.texture, SBackground.scrollingOffset, 0, renderer);
            renderTexture(SBackground.texture, SBackground.scrollingOffset - SBackground.width, 0, renderer);

            renderTexture(pixel_adventure, 350, 100,renderer);


            Man.Render(Man.x, Man.y+560, renderer);
            Man.Render(Man.x, Man.y, renderer);
            Man.tick(); Man.move();

            if( (500<=x&&x<=756) && (200<=y&&y<=328) ) renderTexture(start2, 500, 200, renderer);
            else renderTexture(start1, 500, 200, renderer);
            if( (500<=x&&x<=756) && (200<=y&&y<=328) && (event.type==SDL_MOUSEBUTTONDOWN || event.type==SDL_MOUSEBUTTONUP) ) quit=true;
            SDL_RenderPresent(renderer);
            SDL_Delay(45);
        }
        SDL_DestroyTexture( pixel_adventure ); pixel_adventure = NULL;
        SDL_DestroyTexture( start1 ); start1 = NULL;
        SDL_DestroyTexture( start2 ); start2 = NULL;
        Man.Free();
    }

    int ChooseCharacter(SDL_Renderer* renderer, SDL_Event event){
        int A=1;

        ScrollingBackground SBackground;
        SBackground.setTexture(renderer);

        Sprite Frog;
        Frog.LoadImg("img/NinjaFrog//BigIdle.png", renderer);
        Frog.init(MAN_FRAMES_2, MAN_CLIPS_2);
        Sprite BigFrog;
        BigFrog.LoadImg("img/NinjaFrog//BigRun.png", renderer);
        BigFrog.init(MAN_FRAMES_3, MAN_CLIPS_3);

        Sprite Mask;
        Mask.LoadImg("img/MaskDude//BigIdle.png", renderer);
        Mask.init(MAN_FRAMES_2, MAN_CLIPS_2);
        Sprite BigMask;
        BigMask.LoadImg("img/MaskDude//BigRun.png", renderer);
        BigMask.init(MAN_FRAMES_3, MAN_CLIPS_3);

        Sprite Pink;
        Pink.LoadImg("img/PinkMan//BigIdle.png", renderer);
        Pink.init(MAN_FRAMES_2, MAN_CLIPS_2);
        Sprite BigPink;
        BigPink.LoadImg("img/PinkMan//BigRun.png", renderer);
        BigPink.init(MAN_FRAMES_3, MAN_CLIPS_3);

        Sprite Guy;
        Guy.LoadImg("img/VirtualGuy//BigIdle.png", renderer);
        Guy.init(MAN_FRAMES_2, MAN_CLIPS_2);
        Sprite BigGuy;
        BigGuy.LoadImg("img/VirtualGuy//BigRun.png", renderer);
        BigGuy.init(MAN_FRAMES_3, MAN_CLIPS_3);

        SDL_Texture* continue1 = LoadButton("img/button/Continue1.png", renderer);
        SDL_Texture* continue2 = LoadButton("img/button/Continue2.png", renderer);
        SDL_Texture* selectcharacter = LoadButton("img/button//SelectCharacter.png", renderer);

        bool quit=false;
        int x=0,y=0;
        while(!quit)
        {
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT) exit(0);
            SDL_GetMouseState(&x,&y);

            SBackground.scroll(1);
            renderTexture(SBackground.texture, SBackground.scrollingOffset, 0, renderer);
            renderTexture(SBackground.texture, SBackground.scrollingOffset - SBackground.width, 0, renderer);
            renderTexture(selectcharacter, 317, 100, renderer);

            if( (1030<=x&&x<=1270) && (10<=y&&y<=87) ) renderTexture(continue2, 1030, 10,renderer);
            else renderTexture(continue1, 1030, 10,renderer);

            Frog.Render(Frog.x+309+64, Frog.y+500, renderer);
            Frog.tick();
            Mask.Render(Mask.x+487+64, Mask.y+500, renderer);
            Mask.tick();
            Pink.Render(Pink.x+665+64, Pink.y+500, renderer);
            Pink.tick();
            Guy.Render(Guy.x+843+64, Guy.y+500, renderer);
            Guy.tick();

            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if( (1030<=x&&x<=1270) && (10<=y&&y<=87)) quit=true;
                if( (309<=x&&x<=437) && (500<=y&&y<=628)) A=1;
                else if( (487<=x&&x<=615) && (500<=y&&y<=628)) A=2;
                else if( (665<=x&&x<=793) && (500<=y&&y<=628)) A=3;
                else if( (843<=x&&x<=971) && (500<=y&&y<=628)) A=4;
            }

            switch(A)
            {
                case 1:
                    {
                        BigFrog.Render(BigFrog.x+512+64, BigFrog.y+192, renderer);
                        BigFrog.tick();
                    } break;
                case 2:
                    {
                        BigMask.Render(BigMask.x+512+64, BigMask.y+192, renderer);
                        BigMask.tick();
                    } break;
                case 3:
                    {
                        BigPink.Render(BigPink.x+512+64, BigPink.y+192, renderer);
                        BigPink.tick();
                    } break;
                case 4:
                    {
                        BigGuy.Render(BigGuy.x+512+64, BigGuy.y+192, renderer);
                        BigGuy.tick();
                    } break;
            }

            SDL_RenderPresent(renderer);
            SDL_Delay(50);
        }
        SDL_DestroyTexture( continue1 ); continue1 = NULL;
        SDL_DestroyTexture( continue2 ); continue2 = NULL;
        SDL_DestroyTexture( selectcharacter); selectcharacter = NULL;
        Frog.Free(); BigFrog.Free();
        Mask.Free(); BigMask.Free();
        Pink.Free(); BigPink.Free();
        Guy.Free(); BigGuy.Free();
        return A;
    }

    int SellectLevel(SDL_Renderer* renderer, SDL_Event event, const int& lv1, const int& lv2, const int& lv3, const int& lv4){
        int level = 1;
        ScrollingBackground SBackground;
        SBackground.setTexture(renderer);

        SDL_Texture* selectLevel = LoadButton("img/button//SelectLevel.png", renderer);
        SDL_Texture* lv1On = LoadButton("img/button//Level1On.png", renderer);
        SDL_Texture* lv1Off = LoadButton("img/button//Level1Off.png", renderer);
        SDL_Texture* lv2On = LoadButton("img/button//Level2On.png", renderer);
        SDL_Texture* lv2Off = LoadButton("img/button//Level2Off.png", renderer);
        SDL_Texture* lvBossOn = LoadButton("img/button//LevelBossOn.png", renderer);
        SDL_Texture* lvBossOff = LoadButton("img/button//LevelBossOff.png", renderer);
        SDL_Texture* lv4On = LoadButton("img/button//Level4On.png", renderer);
        SDL_Texture* lv4Off = LoadButton("img/button//Level4Off.png", renderer);
        bool quit = false;
        int x,y;
        while(!quit){
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT) exit(0);
            SDL_GetMouseState(&x, &y);
            SBackground.scroll(1);
            renderTexture(SBackground.texture, SBackground.scrollingOffset, 0, renderer);
            renderTexture(SBackground.texture, SBackground.scrollingOffset - SBackground.width, 0, renderer);

            renderTexture(selectLevel, 385, 100, renderer);

            if(lv1) renderTexture(lv1On, 454, 250, renderer);
            else renderTexture(lv1Off, 454, 250, renderer);
            if(lv2) renderTexture(lv2On, 554, 250, renderer);
            else renderTexture(lv2Off, 554, 250, renderer);
            if(lv3) renderTexture(lvBossOn, 654, 250, renderer);
            else renderTexture(lvBossOff, 654, 250, renderer);
            if(lv4) renderTexture(lv4On, 754, 250, renderer);
            else renderTexture(lv4Off, 754, 250, renderer);
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if( (454<=x&&x<=454 + 72) && (250<=y&&y<=250 + 62) && lv1 ){
                    level=1;
                    quit=true;
                }
                else if( (554<=x&&x<=554 + 72) && (250<=y&&y<=250+62) && lv2){
                    level=2;
                    quit=true;
                }
                else if( (654<=x&&x<=654 + 72) && (250<=y&&y<=250+62) && lv3){
                    level=3;
                    quit = true;
                }
                else if( (754<=x&&x<=754 + 72) && (250<=y&&y<=250+62) && lv4){
                    level = 4;
                    quit = true;
                }
            }

            SDL_RenderPresent(renderer);
            SDL_Delay(50);

        }

        SDL_DestroyTexture(lv1On); lv1On = nullptr;
        SDL_DestroyTexture(lv2On); lv2On = nullptr;
        SDL_DestroyTexture(lvBossOn); lvBossOn = nullptr;
        SDL_DestroyTexture(lv1Off); lv1Off = nullptr;
        SDL_DestroyTexture(lv2Off); lv2Off = nullptr;
        SDL_DestroyTexture(lvBossOff); lvBossOff = nullptr;
        SDL_DestroyTexture(lv4On); lv4On = nullptr;
        SDL_DestroyTexture(lv4Off); lv4Off = nullptr;

        return level;
    }

    void MenuGameOver(SDL_Renderer* renderer, SDL_Event event){

        ScrollingBackground SBackground;
        SBackground.setTexture(renderer);

        Sprite Man;
        Man.LoadImg("img/NinjaFrog//RunR.png", renderer);
        Man.init(MAN_FRAMES, MAN_CLIPS);

        SDL_Texture* game_over = LoadButton("img/button//GameOver.png", renderer);
        SDL_Texture* play_again1 = LoadButton("img/button//PlayAgain1.png", renderer);
        SDL_Texture* play_again2 = LoadButton("img/button//PlayAgain2.png", renderer);
        SDL_Texture* quit1 = LoadButton("img/button//Quit1.png", renderer);
        SDL_Texture* quit2 = LoadButton("img/button//Quit2.png", renderer);

        bool quit=false;
        int x=0,y=0;
        while(!quit)
        {
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT) exit(0);
            SDL_GetMouseState(&x,&y);

            SBackground.scroll(1);
            renderTexture(SBackground.texture, SBackground.scrollingOffset, 0, renderer);
            renderTexture(SBackground.texture, SBackground.scrollingOffset - SBackground.width, 0, renderer);

            renderTexture(game_over, 405, 100,renderer);

            Man.Render(Man.x, Man.y+560, renderer);
            Man.Render(Man.x, Man.y, renderer);
            Man.tick(); Man.move();

            if( (440<=x&&x<=840) && (200<=y&&y<=328) ) renderTexture(play_again2, 440, 200, renderer);
            else renderTexture(play_again1, 440, 200, renderer);
            if( (512<=x&&x<=768) && (350<=y&&y<=478) ) renderTexture(quit2, 512, 350, renderer);
            else renderTexture(quit1, 512, 350, renderer);

            if( (440<=x&&x<=840) && (200<=y&&y<=328) && (event.type==SDL_MOUSEBUTTONUP) ){
                restart_ = true;
                quit=true;
            }
            if((512<=x&&x<=768) && (350<=y&&y<=478) && (event.type==SDL_MOUSEBUTTONUP)){
                restart_ = false;
                quit = true;
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(45);
        }
        SDL_DestroyTexture( game_over ); game_over = NULL;
        SDL_DestroyTexture( play_again1 ); play_again1 = NULL;
        SDL_DestroyTexture( play_again2 ); play_again2 = NULL;
        SDL_DestroyTexture( quit1 ); quit1 = NULL;
        SDL_DestroyTexture( quit2 ); quit2 = NULL;
        Man.Free();
    }

    void MenuWin(SDL_Renderer* renderer, SDL_Event event){

        ScrollingBackground SBackground;
        SBackground.setTexture(renderer);

        Sprite Man;
        Man.LoadImg("img/NinjaFrog//RunR.png", renderer);
        Man.init(MAN_FRAMES, MAN_CLIPS);

        Sprite Cup;
        Cup.LoadImg("img/Items//End.png", renderer);
        Cup.init(FLAGS_FRAME, FLAGS_CLIPS);

        SDL_Texture* game_win = LoadButton("img/button//Win.png", renderer);
        SDL_Texture* play_again1 = LoadButton("img/button//NextChallenge1.png", renderer);
        SDL_Texture* play_again2 = LoadButton("img/button//NextChallenge2.png", renderer);
        SDL_Texture* quit1 = LoadButton("img/button//Quit1.png", renderer);
        SDL_Texture* quit2 = LoadButton("img/button//Quit2.png", renderer);

        bool quit=false;
        int x=0,y=0;
        while(!quit)
        {
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT) exit(0);
            SDL_GetMouseState(&x,&y);

            SBackground.scroll(1);
            renderTexture(SBackground.texture, SBackground.scrollingOffset, 0, renderer);
            renderTexture(SBackground.texture, SBackground.scrollingOffset - SBackground.width, 0, renderer);

            renderTexture(game_win, 454, 100,renderer);

            Man.Render(Man.x, Man.y+560, renderer);
            Man.Render(Man.x, Man.y, renderer);
            Man.tick(); Man.move();
            Cup.Render(Cup.x + 640, Cup.y+560, renderer);
            Cup.Render(Cup.x + 640, Cup.y, renderer);
            Cup.tick(); Cup.move();

            if( (440<=x&&x<=840) && (200<=y&&y<=328) ) renderTexture(play_again2, 440, 200, renderer);
            else renderTexture(play_again1, 440, 200, renderer);
            if( (512<=x&&x<=768) && (350<=y&&y<=478) ) renderTexture(quit2, 512, 350, renderer);
            else renderTexture(quit1, 512, 350, renderer);

            if( (440<=x&&x<=840) && (200<=y&&y<=328) && (event.type==SDL_MOUSEBUTTONUP) ){
                restart_ = true;
                quit=true;
            }
            if((512<=x&&x<=768) && (350<=y&&y<=478) && (event.type==SDL_MOUSEBUTTONUP)){
                restart_ = false;
                quit = true;
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(45);
        }
        SDL_DestroyTexture( game_win ); game_win = NULL;
        SDL_DestroyTexture( play_again1 ); play_again1 = NULL;
        SDL_DestroyTexture( play_again2 ); play_again2 = NULL;
        SDL_DestroyTexture( quit1 ); quit1 = NULL;
        SDL_DestroyTexture( quit2 ); quit2 = NULL;
        Man.Free();
        Cup.Free();
    }

    void LoadVolumnButton(SDL_Renderer* renderer){
        volumn_on = LoadButton("img/button//VolumeOn.png", renderer);
        volumn_off = LoadButton("img/button//VolumeOff.png", renderer);
    }

    void RenderVolumnButton(SDL_Renderer* renderer){
        if(volumn_) renderTexture(volumn_on, 1249, 11, renderer);
        else renderTexture(volumn_off, 1249, 11, renderer);
    }

    void ChangeVolumn(SDL_Event event, Mix_Chunk* chunk, Mix_Chunk* chunk2, Mix_Chunk* chunk3, Mix_Chunk* chunk4, Mix_Chunk* chunk5, Mix_Chunk* chunk6){
        int x=0, y=0;
        SDL_GetMouseState(&x, &y);
        if(event.type == SDL_MOUSEBUTTONDOWN && (1249<=x && x<=1268) && (11<=y && y<=30) ){
            if(volumn_ == 1){
                Mix_VolumeMusic(0);
                Mix_VolumeChunk(chunk, 0);
                Mix_VolumeChunk(chunk2, 0);
                Mix_VolumeChunk(chunk3, 0);
                Mix_VolumeChunk(chunk4, 0);
                Mix_VolumeChunk(chunk5, 0);
                Mix_VolumeChunk(chunk6, 0);
            }
            else{
                Mix_VolumeMusic(MIX_MAX_VOLUME);
                Mix_VolumeChunk(chunk, MIX_MAX_VOLUME);
                Mix_VolumeChunk(chunk2, MIX_MAX_VOLUME);
                Mix_VolumeChunk(chunk3, MIX_MAX_VOLUME);
                Mix_VolumeChunk(chunk4, MIX_MAX_VOLUME);
                Mix_VolumeChunk(chunk5, MIX_MAX_VOLUME);
                Mix_VolumeChunk(chunk6, MIX_MAX_VOLUME);
            }
            volumn_ = (volumn_+1)%2;
        }
    }

    void LoadRestart(SDL_Renderer* renderer){
        res = LoadButton("img/button//Restart.png", renderer);
    }

    void RenderRestartButton(SDL_Renderer* renderer){
        renderTexture(res, 1209, 11, renderer);
    }

    void SellectRestart(SDL_Event event, bool& is_restart){
        int x=0, y=0;
        SDL_GetMouseState(&x, &y);
        if(event.type == SDL_MOUSEBUTTONDOWN && (1209<=x && x<=1228) && (11<=y && y<=30) ) is_restart = true;
    }

    void LoadPause(SDL_Renderer* renderer){
        pause = LoadButton("img/button//Pause.png", renderer);
        backgr = LoadButton("img/button//PauseBackground.png", renderer);
    }
    void RenderPauseButton(SDL_Renderer* renderer){
        renderTexture(pause, 1167, 11, renderer);
    }
    void Pause(SDL_Event& event, SDL_Renderer* renderer){
        int x, y;
        SDL_GetMouseState(&x, &y);
        if((1167<=x&&x<=1186) && (11<=y&&y<=30) && event.type == SDL_MOUSEBUTTONUP){
            SDL_Event e;
            bool is_quit = false;
            while(!is_quit){
                SDL_PollEvent(&e);
                SDL_GetMouseState(&x, &y);
                if( (565<=x&&x<=565+150) && (300<=y&&y<=300+150) && e.type == SDL_MOUSEBUTTONDOWN){
                    is_quit = true;
                    return;
                }
                renderTexture(backgr, 0, 0, renderer);
                SDL_RenderPresent(renderer);
                SDL_Delay(50);
            }
        }
        return;
    }
};




#endif // _GRAPHICS_H
