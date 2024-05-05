#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <windows.h>
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int FONT_SIZE = 30;
const int MAX_TIME = 20;

#define HEART 3
#define WINDOW_TITLE "Pixel Adventure"
#define FONT_NAME "font//VNI-Souvir.ttf"
#define BACKGROUND_IMG "img//Background.png"
#define BOSS_IMG "img/Boss//Boss.png"
//Screen
const int FRAME_PER_SECOND = 32; //fps
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;

//Bullet
const int BULLET_SPEED = 20;
const int BULLET_SPEED_ENEMY = 10;

#define TILE_SIZE 64
#define BLANK_TILE 0
#define SUPER_POWER 1

#define MAX_MAP_X 80
#define MAX_MAP_Y 10

typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};

typedef struct Map{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;

};

namespace SDLCommonFunc{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    bool CheckVaQuai(const SDL_Rect& player, const SDL_Rect& object);
}


#endif // COMMON_FUNCTION_H
