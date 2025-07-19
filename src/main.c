#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>

#include "sdl_wrapper.h"
#include "render.h"

int main(int argc, char* argv[]) {
    Context ctx;
    Init(&ctx);


    Camera camera = {0};
    camera.rotation = (Vec2){0.2, 0};
    Object object;
    object.posistion = (Vec3){5, 0, 0};
    init_mesh(&object.mesh, 8, 12);
    Vertex v1, v2, v3, v4, v5, v6, v7, v8;

    v1.position = (Vec3){.x = -1, .y = -1, .z = -1,};
    v1.color = (Color){.r = 0, .g = 0, .b = 0};
    v2.position = (Vec3){.x = -1, .y = -1, .z = 1};
    v2.color = (Color){.r = 0, .g = 0, .b = 255};
    v3.position = (Vec3){.x = -1, .y = 1, .z = 1};
    v3.color = (Color){.r = 0, .g = 255, .b = 0};
    v4.position = (Vec3){.x = -1, .y = 1, .z = -1};
    v4.color = (Color){.r = 0, .g = 255, .b = 255};
    v5.position = (Vec3){.x = 1, .y = -1, .z = -1};
    v5.color = (Color){.r = 255, .g = 0, .b = 0};
    v6.position = (Vec3){.x = 1, .y = -1, .z = 1};
    v6.color = (Color){.r = 255, .g = 0, .b = 255};
    v7.position = (Vec3){.x = 1, .y = 1, .z = 1};
    v7.color = (Color){.r = 255, .g = 255, .b = 0};
    v8.position = (Vec3){.x = 1, .y = 1, .z = -1};
    v8.color = (Color){.r = 255, .g = 255, .b = 255};

    add_vertex(&object.mesh, v1);
    add_vertex(&object.mesh, v2);
    add_vertex(&object.mesh, v3);
    add_vertex(&object.mesh, v4);
    add_vertex(&object.mesh, v5);
    add_vertex(&object.mesh, v6);
    add_vertex(&object.mesh, v7);
    add_vertex(&object.mesh, v8);

    Face f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12;
    f1 = (Face){.v1 = 0, .v2 = 1, .v3 = 2};
    f2 = (Face){.v1 = 0, .v2 = 2, .v3 = 3};
    f3 = (Face){.v1 = 0, .v2 = 1, .v3 = 5};
    f4 = (Face){.v1 = 0, .v2 = 4, .v3 = 5};
    f5 = (Face){.v1 = 1, .v2 = 5, .v3 = 6};
    f6 = (Face){.v1 = 1, .v2 = 2, .v3 = 6};
    f7 = (Face){.v1 = 0, .v2 = 4, .v3 = 7};
    f8 = (Face){.v1 = 0, .v2 = 3, .v3 = 7};
    f9 = (Face){.v1 = 2, .v2 = 3, .v3 = 7};
    f10 = (Face){.v1 = 2, .v2 = 6, .v3 = 7};
    f11 = (Face){.v1 = 4, .v2 = 5, .v3 = 6};
    f12 = (Face){.v1 = 4, .v2 = 6, .v3 = 7};


    add_face(&object.mesh, f1);
    add_face(&object.mesh, f2);
    add_face(&object.mesh, f3);
    add_face(&object.mesh, f4);
    add_face(&object.mesh, f5);
    add_face(&object.mesh, f6);
    add_face(&object.mesh, f7);
    add_face(&object.mesh, f8);
    add_face(&object.mesh, f9);
    add_face(&object.mesh, f10);
    add_face(&object.mesh, f11);
    add_face(&object.mesh, f12);


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
            camera.rotation.x += 0.1;
        }
        if (keyboard_state[SDL_SCANCODE_DOWN]) {
            camera.rotation.x -= 0.1;
        }
        if (keyboard_state[SDL_SCANCODE_LEFT]) {
            camera.rotation.y += 0.1;
        }
        if (keyboard_state[SDL_SCANCODE_RIGHT]) {
            camera.rotation.y -= 0.1;
        }

        clear(&ctx);

        render_object(&camera, &ctx, &object);

        render(&ctx);

        SDL_Delay(33);
    }

    return 0;
}