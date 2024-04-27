#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include "CommonFunction.h"
#include <bits/stdc++.h>

using namespace std;

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
const int MAN_FRAMES = sizeof(MAN_CLIPS)/sizeof(int)/4;

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
    int x=0;
    int y=0;

    void init(SDL_Texture* _texture, int frames, const int _clips[][4]);
    void tick();
    const SDL_Rect* getCurrentClip() const;
    void Render(int x, int y, SDL_Renderer* renderer);
    void move();
};

struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;

    void logErrorAndExit(const char* msg, const char* error);
    void init();

    void prepareScene(SDL_Texture * background);
    void presentScene();

    SDL_Texture *loadTexture(const char *filename);
    void renderTexture(SDL_Texture *texture, int x, int y);
    void render(const ScrollingBackground& bgr);

    Mix_Music *loadMusic(const char* path);
    void play(Mix_Music *gMusic);
    Mix_Chunk* loadSound(const char* path);
    void play(Mix_Chunk* gChunk);
    TTF_Font* loadFont(const char* path, int size);
    SDL_Texture* renderText(const char* text,TTF_Font* font, SDL_Color textColor);

    void quit();
};

struct Menu {
    SDL_Texture *background_menu;
    SDL_Texture *button_menu;



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

    SDL_Texture* LoadButton(const char *filename, SDL_Renderer* renderer,int x ,int y){
        SDL_Texture* button = loadTexture(filename, renderer);
        return button;
    }

    void StartMenu(SDL_Renderer* renderer, SDL_Event event){

        ScrollingBackground SBackground;
        SBackground.setTexture(renderer);

        Sprite Man;
        SDL_Texture* man = IMG_LoadTexture(renderer, "img/NinjaFrog//RunR.png");
        Man.init(man, MAN_FRAMES, MAN_CLIPS);

        SDL_Texture* pixel_adventure = LoadButton("img/button//PixelAdventure.png", renderer, 350, 100);
        SDL_Texture* start1 = LoadButton("img/button//Start1.png", renderer, 500, 200);
        SDL_Texture* start2 = LoadButton("img/button//Start2.png", renderer, 500, 200);

        SDL_RenderPresent(renderer);

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

            renderTexture(pixel_adventure, 350, 100,renderer);

            Man.Render(Man.x-64, Man.y+560, renderer);
            Man.tick(); Man.move();

            if( (500<=x&&x<=756) && (200<=y&&y<=328) ) renderTexture(start2, 500, 200, renderer);
            else renderTexture(start1, 500, 200, renderer);
            if( (500<=x&&x<=756) && (200<=y&&y<=328) && (event.type==SDL_MOUSEBUTTONDOWN || event.type==SDL_MOUSEBUTTONUP) ) quit=true;
            SDL_RenderPresent(renderer);
            SDL_Delay(45);
        }
        SDL_DestroyTexture( man ); man = NULL;
        SDL_DestroyTexture( pixel_adventure ); pixel_adventure = NULL;
        SDL_DestroyTexture( start1 ); start1 = NULL;
        SDL_DestroyTexture( start2 ); start2 = NULL;
    }

    int ChooseCharacter(SDL_Renderer* renderer, SDL_Event event){
        cout<<"check Choose Character\n";
        int A=1;

        ScrollingBackground SBackground;
        SBackground.setTexture(renderer);

        Sprite Frog;
        SDL_Texture* Sfrog = IMG_LoadTexture(renderer, "img/NinjaFrog//BigIdle.png");
        Frog.init(Sfrog, MAN_FRAMES_2, MAN_CLIPS_2);
        Sprite BigFrog;
        SDL_Texture* Sfrog2 = IMG_LoadTexture(renderer, "img/NinjaFrog//BigRun.png");
        BigFrog.init(Sfrog2, MAN_FRAMES_3, MAN_CLIPS_3);

        Sprite Mask;
        SDL_Texture* Smask = IMG_LoadTexture(renderer, "img/MaskDude//BigIdle.png");
        Mask.init(Smask, MAN_FRAMES_2, MAN_CLIPS_2);
        Sprite BigMask;
        SDL_Texture* Smask2 = IMG_LoadTexture(renderer, "img/MaskDude//BigRun.png");
        BigMask.init(Smask2, MAN_FRAMES_3, MAN_CLIPS_3);

        Sprite Pink;
        SDL_Texture* Spink = IMG_LoadTexture(renderer, "img/PinkMan//BigIdle.png");
        Pink.init(Spink, MAN_FRAMES_2, MAN_CLIPS_2);
        Sprite BigPink;
        SDL_Texture* Spink2 = IMG_LoadTexture(renderer, "img/PinkMan//BigRun.png");
        BigPink.init(Spink2, MAN_FRAMES_3, MAN_CLIPS_3);

        Sprite Guy;
        SDL_Texture* Sguy = IMG_LoadTexture(renderer, "img/VirtualGuy//BigIdle.png");
        Guy.init(Sguy, MAN_FRAMES_2, MAN_CLIPS_2);
        Sprite BigGuy;
        SDL_Texture* Sguy2 = IMG_LoadTexture(renderer, "img/VirtualGuy//BigRun.png");
        BigGuy.init(Sguy2, MAN_FRAMES_3, MAN_CLIPS_3);

        SDL_Texture* continue1 = LoadButton("img/button/Continue1.png", renderer, 1030, 10);
        SDL_Texture* continue2 = LoadButton("img/button/Continue2.png", renderer, 1030, 10);

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

            if( (1030<=x&&x<=1270) && (10<=y&&y<=87) ) renderTexture(continue2, 1030, 10,renderer);
            else renderTexture(continue1, 1030, 10,renderer);

            Frog.Render(Frog.x+309, Frog.y+500, renderer);
            Frog.tick();
            Mask.Render(Mask.x+487, Mask.y+500, renderer);
            Mask.tick();
            Pink.Render(Pink.x+665, Pink.y+500, renderer);
            Pink.tick();
            Guy.Render(Guy.x+843, Guy.y+500, renderer);
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
                        BigFrog.Render(BigFrog.x+512, BigFrog.y+192, renderer);
                        BigFrog.tick();
                    } break;
                case 2:
                    {
                        BigMask.Render(BigMask.x+512, BigMask.y+192, renderer);
                        BigMask.tick();
                    } break;
                case 3:
                    {
                        BigPink.Render(BigPink.x+512, BigPink.y+192, renderer);
                        BigPink.tick();
                    } break;
                case 4:
                    {
                        BigGuy.Render(BigGuy.x+512, BigGuy.y+192, renderer);
                        BigGuy.tick();
                    } break;
            }

            SDL_RenderPresent(renderer);
            SDL_Delay(50);
        }
        SDL_DestroyTexture( continue1 ); continue1 = NULL;
        SDL_DestroyTexture( continue2 ); continue2 = NULL;
        SDL_DestroyTexture( Sfrog ); Sfrog = NULL;
        SDL_DestroyTexture( Sfrog2); Sfrog2 = NULL;
        SDL_DestroyTexture( Smask ); Smask = NULL;
        SDL_DestroyTexture( Smask2 ); Smask2 = NULL;
        SDL_DestroyTexture( Spink ); Spink = NULL;
        SDL_DestroyTexture( Spink2 ); Spink2 = NULL;
        SDL_DestroyTexture( Sguy ); Sguy = NULL;
        SDL_DestroyTexture( Sguy2 ); Sguy2 = NULL;
        return A;
    }
};




#endif // _GRAPHICS_H
