#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>

#include "sdl_wrapper.h"
#include "render.h"
#include "vec.h"

Vertex vertices[] = {
    {.position = (Vec3){-1, -1, -1}, .color = COLOR_BLACK},
    {.position = (Vec3){-1, -1,  1}, .color = COLOR_BLUE},
    {.position = (Vec3){-1,  1,  1}, .color = COLOR_CYAN},
    {.position = (Vec3){-1,  1, -1}, .color = COLOR_GREEN},
    {.position = (Vec3){ 1, -1, -1}, .color = COLOR_MAGENTA},
    {.position = (Vec3){ 1, -1,  1}, .color = COLOR_RED},
    {.position = (Vec3){ 1,  1,  1}, .color = COLOR_YELLOW},
    {.position = (Vec3){ 1,  1, -1}, .color = COLOR_WHITE}
};

Face faces[] = {
    {0, 1, 2},
    {0, 2, 3},
    {0, 1, 5},
    {0, 4, 5},
    {1, 5, 6},
    {1, 2, 6},
    {0, 4, 7},
    {0, 3, 7},
    {2, 3, 7},
    {2, 6, 7},
    {4, 5, 6},
    {4, 6, 7}
};

int main(int argc, char* argv[]) {
    Context ctx;
    Init(&ctx);


    Camera camera = {0};
    camera.rotation = (Vec2){0.2, 0};
    Object object = {.posistion = (Vec3){5, 0, 0}};
    init_mesh(&object.mesh, vertices, faces, sizeof(faces) / sizeof(Face));

    bool running = true;
    SDL_Event ev;

    while (running) {
        while (SDL_PollEvent(&ev) != 0) {
            switch(ev.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
            }
        }

        const bool *keyboard_state = SDL_GetKeyboardState(NULL);
        if (keyboard_state[SDL_SCANCODE_W]) {
            camera.postition.x += 1;
        }
        if (keyboard_state[SDL_SCANCODE_S]) {
            camera.postition.x -= 1;
        }
        if (keyboard_state[SDL_SCANCODE_A]) {
            camera.postition.z += 1;
        }
        if (keyboard_state[SDL_SCANCODE_D]) {
            camera.postition.z -= 1;
        }

        if (keyboard_state[SDL_SCANCODE_UP]) {
            camera.rotation.y += 0.1;
        }
        if (keyboard_state[SDL_SCANCODE_DOWN]) {
            camera.rotation.y -= 0.1;
        }
        if (keyboard_state[SDL_SCANCODE_LEFT]) {
            camera.rotation.x += 0.1;
        }
        if (keyboard_state[SDL_SCANCODE_RIGHT]) {
            camera.rotation.x -= 0.1;
        }

        clear(&ctx);

        render_background(&camera, &ctx);

        render_object(&camera, &ctx, &object);

        render(&ctx);

        SDL_Delay(33);
    }

    return 0;
}