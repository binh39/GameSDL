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

void Sprite::init(/*SDL_Texture* _texture,*/int frames, const int _clips [][4]) {
    //texture = _texture;
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
}

void Sprite::move(){
    x = (x+4)%(1280+64);
}

const SDL_Rect* Sprite::getCurrentClip() const {
    return &(clips[currentFrame]);
}

void Sprite :: Render(int x, int y, SDL_Renderer* renderer) {
    const SDL_Rect* clip = getCurrentClip();
    SDL_Rect renderQuad = {x, y, clip->w, clip->h};
    SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

void Sprite :: RenderWithMap(Map& map_data, SDL_Renderer* renderer){
    x = x_pos - map_data.start_x_;
    y = y_pos - map_data.start_y_;
    const SDL_Rect* clip = getCurrentClip();
    SDL_Rect renderquad = {x, y, 64, 64};
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



