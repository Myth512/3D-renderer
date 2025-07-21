#ifndef CAMERA_H
#define CAMERA_H

#include "vec.h"

typedef struct {
    Vec3 postition;
    Vec2 rotation;
    double fov;
} Camera;

#endif