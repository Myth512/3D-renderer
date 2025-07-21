#include "input.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

void process_input(InputState *input, Camera *camera) {
    if (input->mouse_left) {
        camera->postition = rotate_y(camera->postition, input->mouse_x_rel / 50);
        camera->rotation.x = atan2(camera->postition.z, camera->postition.x) + 3.14;
        input->mouse_x_rel = 0;
    }
    if (input->mouse_scroll) {
        camera->postition.x += cos(camera->rotation.x) * input->mouse_scroll;
        camera->postition.z += sin(camera->rotation.x) * input->mouse_scroll;
        printf("here %f %f\n", camera->rotation.y, sin(camera->rotation.y));
        camera->postition.y -= sin(camera->rotation.y) * input->mouse_scroll;
        input->mouse_scroll = 0;
    }
    if (input->mouse_middle) {
        printf("rel %f %f %f\n", camera->rotation.x * 180 / 3.14, sin(camera->rotation.x), cos(camera->rotation.x));
        camera->postition.x += sin(camera->rotation.x) * input->mouse_x_rel / 10;
        camera->postition.z -= cos(camera->rotation.x) * input->mouse_x_rel / 10;
        camera->postition.y -= input->mouse_y_rel / 10;
    }
    if (input->mouse_right) {
        camera->rotation.x += input->mouse_x_rel / 100;
        camera->rotation.y -= input->mouse_y_rel / 100;
    }
    input->mouse_x_rel = 0;
    input->mouse_y_rel = 0;
}