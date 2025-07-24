#include "input.h"

#include <stdio.h>
#include <math.h>
#include <string.h>


#define PI 3.1415926


static double normalize_angle(double angle) {
    while (angle < -PI)
        angle += 2*PI;
    while (angle > PI)
        angle -= 2*PI;
    return angle;
}


static double cap_angle(double angle, double low, double high) {
    if (angle > high)
        return high;
    if (angle < low)
        return low;
    return angle;
}


void process_input(InputState *input, Camera *camera) {
    if (input->mouse_left) {
        camera->position = rotate_y(camera->position, input->mouse_x_rel / 50);

        double x = atan2(camera->position.z, camera->position.x) + 3.14;
        x = normalize_angle(x);
        x = cap_angle(x, -PI, PI);
        camera->rotation.x = x; 

        double a1 = sin(camera->rotation.x) * input->mouse_y_rel / 50;
        double a2 = cos(camera->rotation.x) * input->mouse_y_rel / 50;

        Vec3 tmp = camera->position;
        tmp = rotate_x(tmp, a1);
        tmp = rotate_z(tmp, a2);
        camera->position = tmp;

        tmp = rotate_y(camera->position, -camera->rotation.x);
        camera->rotation.y = cap_angle(normalize_angle(PI - atan2(tmp.y, tmp.x)), -PI/2, PI/2);
    }

    if (input->mouse_scroll) {
        camera->position.x += cos(camera->rotation.x) * input->mouse_scroll;
        camera->position.z += sin(camera->rotation.x) * input->mouse_scroll;
        camera->position.y -= sin(camera->rotation.y) * input->mouse_scroll;
        input->mouse_scroll = 0;
    }
    if (input->mouse_middle) {
        camera->position.x += sin(camera->rotation.x) * input->mouse_x_rel / 10;
        camera->position.z -= cos(camera->rotation.x) * input->mouse_x_rel / 10;
        camera->position.y -= input->mouse_y_rel / 10;
    }
    if (input->mouse_right) {
        double x = camera->rotation.x + input->mouse_x_rel / 100;
        x = normalize_angle(x);
        camera->rotation.x = x; 
        double y = camera->rotation.y + input->mouse_y_rel / 100;
        y = normalize_angle(y);
        y = cap_angle(y, -PI/2, PI/2);
        camera->rotation.y = y; 
    }
    input->mouse_x_rel = 0;
    input->mouse_y_rel = 0;
}