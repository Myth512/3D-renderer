#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL3/SDL.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    double *depth_buffer;
    int height;
    int width;
} Context;

#endif