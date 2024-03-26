#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include "CommonFunction.h"

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






#endif // _GRAPHICS_H
