#include "sdl_wrapper.h"
#include <stdio.h>


int Init(Context *ctx) {
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        SDL_Log("SDL_Init() Error: %s", SDL_GetError());
        return 0;
    }

    ctx->width = 640;
    ctx->height = 480;
    
    ctx->window = SDL_CreateWindow("HelloWorld SDL3", ctx->width, ctx->height, 0);
    if (!ctx->window) {
        SDL_Log("SDL_CreateWindow() Error: ", SDL_GetError());
        return 0;
    }

    ctx->renderer = SDL_CreateRenderer(ctx->window, NULL);
    if (!ctx->renderer) {
        SDL_Log("SDL_CreateRenderer() Error: ", SDL_GetError());
        return 0;
    }
    return 1;
}


void Term(Context *ctx) {
    SDL_DestroyRenderer(ctx->renderer);
    SDL_DestroyWindow(ctx->window);
    SDL_Quit();
}


void process_events(InputState *input) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch(event.type) {
            case SDL_EVENT_QUIT:
                input->quit_requested=true;
                break;
            case SDL_EVENT_MOUSE_MOTION:
                input->mouse_x_rel = event.motion.xrel;
                input->mouse_y_rel = event.motion.yrel;
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    input->mouse_left = true;
                else if (event.button.button == SDL_BUTTON_MIDDLE)
                    input->mouse_middle = true;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    input->mouse_right = true;
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    input->mouse_left = false;
                else if (event.button.button == SDL_BUTTON_MIDDLE)
                    input->mouse_middle = false;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    input->mouse_right = false;
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                input->mouse_scroll = event.wheel.y;
                break;
        }
    }
}


void clear(Context *ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctx->renderer);
}


void set_pixel(Context *ctx, double x, double y, Color c) {
    SDL_SetRenderDrawColor(ctx->renderer, c.r, c.g, c.b, 255);
    SDL_RenderPoint(ctx->renderer, x, y);
}


void render(Context *ctx) {
    SDL_RenderPresent(ctx->renderer);
}

