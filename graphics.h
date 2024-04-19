#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include "CommonFunction.h"
#include <bits/stdc++.h>

using namespace std;

struct ScrollingBackground{
    SDL_Texture* texture;
    int scrollingOffset = 0;
    int width, height;

    void setTexture(SDL_Texture* _texture);
    void scroll(int distance);
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

    //SDL_Renderer *renderer_menu;
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
        if(background_menu == NULL) cout<<"Error Load Background Menu\n";
        SDL_RenderCopy(renderer, background_menu,NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    void LoadButton(const char *filename, SDL_Renderer* renderer,int x ,int y){
        button_menu = loadTexture(filename, renderer);
        if(button_menu == NULL) cout<<"Error Load Button\n";
        renderTexture(button_menu, x, y,renderer);
        SDL_RenderPresent(renderer);
    }

    void StartMenu(SDL_Renderer* renderer, SDL_Event event){
        cout<<"check Start"<<endl;
        LoadBackgroundMenu("img//Background.png", renderer);
        LoadButton("img/button//PixelAdventure.png", renderer, 350, 100);
        LoadButton("img/button//Start2.png", renderer, 500, 200);
        LoadButton("img/button//Start1.png", renderer, 500, 200);
        SDL_RenderPresent(renderer);

        bool quit=false;
        int x=0,y=0;
        while(!quit)
        {
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT) exit(0);
            SDL_GetMouseState(&x,&y);
            cout<<x<<" "<<y<<endl;
            if( (500<=x&&x<=756) && (200<=y&&y<=328) ) LoadButton("img/button//Start2.png", renderer, 500, 200);
            else LoadButton("img/button//Start1.png", renderer, 500, 200);
            if( (500<=x&&x<=756) && (200<=y&&y<=328) && (event.type==SDL_MOUSEBUTTONDOWN || event.type==SDL_MOUSEBUTTONUP) ) quit=true;
            SDL_Delay(60);
        }
    }

    int ChooseCharacter(SDL_Renderer* renderer, SDL_Event event){
        cout<<"check Choose Character\n";
        int A=1;
        LoadBackgroundMenu("img//Background.png", renderer);
        LoadButton("img/button/Continue1.png", renderer, 1030, 10);
        LoadButton("img/button/IdleFrog.png", renderer, 309, 500);
        LoadButton("img/button/IdleMaskDude.png", renderer, 487, 500);
        LoadButton("img/button/IdlePinkMan.png", renderer, 665, 500);
        LoadButton("img/button/IdleVirtualGuy.png", renderer, 843, 500);
        SDL_RenderPresent(renderer);

        bool quit=false;
        int x=0,y=0;
        while(!quit)
        {
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT) exit(0);
            SDL_GetMouseState(&x,&y);
            cout<<x<<" "<<y<<endl;
            if( (1030<=x&&x<=1270) && (10<=y&&y<=87) ) LoadButton("img/button//Continue2.png", renderer, 1030, 10);
            else LoadButton("img/button//Continue1.png", renderer, 1030, 10);
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if( (1030<=x&&x<=1270) && (10<=y&&y<=87)) quit=true;
                if( (309<=x&&x<=437) && (500<=y&&y<=628)) A=1;
                else if( (487<=x&&x<=615) && (500<=y&&y<=628)) A=2;
                else if( (665<=x&&x<=793) && (500<=y&&y<=628)) A=3;
                else if( (843<=x&&x<=971) && (500<=y&&y<=628)) A=4;

                switch(A)
                {
                    case 1:
                        {
                            LoadButton("img/button//FrogBack.png", renderer, 512, 192);
                        } break;
                    case 2:
                        {
                            LoadButton("img/button//MaskBack.png", renderer, 512, 192);
                        } break;
                    case 3:
                        {
                            LoadButton("img/button//PinkBack.png", renderer, 512, 192);
                        } break;
                    case 4:
                        {
                            LoadButton("img/button//VirtualBack.png", renderer, 512, 192);
                        } break;
                }
            }

            SDL_Delay(60);
        }

        return A;
    }

};




#endif // _GRAPHICS_H
