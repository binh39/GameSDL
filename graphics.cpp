#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "CommonFunction.h"

// Graphics

Mix_Music* Graphics :: loadMusic(const char* path)
{
    Mix_Music *gMusic = Mix_LoadMUS(path);
    if (gMusic == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,"Could not load music! SDL_mixer Error: %s", Mix_GetError());
    }
    return gMusic;
}
void Graphics :: play(Mix_Music *gMusic)
{
    if (gMusic == nullptr) return;
    if (Mix_PlayingMusic() == 0) Mix_PlayMusic( gMusic, -1 );
    else if( Mix_PausedMusic() == 1 ) Mix_ResumeMusic();
}

Mix_Chunk* Graphics :: loadSound(const char* path) {
    Mix_Chunk* gChunk = Mix_LoadWAV(path);
    if (gChunk == nullptr) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,"Could not load sound! SDL_mixer Error: %s", Mix_GetError());
    return gChunk;
}
void Graphics :: play(Mix_Chunk* gChunk) {
    if (gChunk != nullptr) Mix_PlayChannel( -1, gChunk, 0 );
}


//Scrolling Background
void ScrollingBackground::setTexture(SDL_Renderer* renderer) {
    texture = IMG_LoadTexture(renderer, "img/Background.png");
    if (texture == NULL) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void ScrollingBackground::scroll(int distance) {
    scrollingOffset -= distance;
    if( scrollingOffset < 0 ) { scrollingOffset = width; }
}

//Sprite
void Sprite :: LoadImg(const char* name, SDL_Renderer* renderer){
    texture = IMG_LoadTexture(renderer, name);
}
void Sprite :: SetBegin(){
    x = 0;
    y = SCREEN_HEIGHT + 64;
    dx = 0;
    huong = 1;
    delay = 0;
    is_collect = false;
    is_move = false;
}
void Sprite::init(int frames, const int _clips [][4]) {
    SDL_Rect clip;
    for (int i = 0; i < frames; i++) {
        clip.x = _clips[i][0];
        clip.y = _clips[i][1];
        clip.w = _clips[i][2];
        clip.h = _clips[i][3];
        clips.push_back(clip);
    }
    width_frame_ = _clips[0][2];
    height_frame_ = _clips[0][3];
}
void Sprite::tick() {
    currentFrame = (currentFrame + 1) % clips.size();
    delay = (delay+1) % MAX_DELAY;
}

void Sprite::move(){
    x = (x+4)%(1280+64);
}
void Sprite :: move2(const int& x_left, const int& x_right){
    if(huong) dx = PLATE_SPEED;
    else  dx = -PLATE_SPEED;
    if(is_move) x_pos += dx;
    if(x_pos >= x_right){
        is_move = false;
        dx=0;
        huong = (huong+1)%2;
    }
    if(x_pos <= x_left){
        is_move = false;
        dx = 0;
        huong = (huong+1)%2;
    }
}
void Sprite :: move3(){
    x_pos -= ROCKET_SPEED;
    if(x < 0-width_frame_) SetBegin();
}

SDL_Rect Sprite :: GetRect(){
    SDL_Rect rect = {x, y, width_frame_, height_frame_};
    return rect;
}
const SDL_Rect* Sprite::getCurrentClip() const {
    return &(clips[currentFrame]);
}

void Sprite :: Render(int x, int y, SDL_Renderer* renderer) {
    x=x%(1280+64);
    const SDL_Rect* clip = getCurrentClip();
    SDL_Rect renderQuad = {x-64, y, clip->w, clip->h};
    SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}
void Sprite :: RenderWithMap(Map& map_data, SDL_Renderer* renderer){
    x = x_pos - map_data.start_x_;
    y = y_pos - map_data.start_y_;
    const SDL_Rect* clip = getCurrentClip();
    SDL_Rect renderquad = {x, y, width_frame_, height_frame_};
    SDL_RenderCopy(renderer, texture, clip, &renderquad);
}

void Sprite :: Free(){
    if(texture != NULL){
        SDL_DestroyTexture(texture);
        texture = NULL;
        width_frame_ = 0;
        height_frame_ = 0;
        x_pos = 0;
        y_pos = 0;
    }
}



