#ifndef CONTEXT_H
#define CONTEXT_H


#include <SDL3/SDL.h>


typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    void *pixels;
    int pitch;
    int height;
    int width;
} Context;


#endif