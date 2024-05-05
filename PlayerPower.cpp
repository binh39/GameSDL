#include "PlayerPower.h"
#include "graphics.h"

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


