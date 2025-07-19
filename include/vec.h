#ifndef VEC_H
#define VEC_H

typedef struct {
    double x;
    double y;
} Vec2;

typedef struct {
    double x;
    double y;
    double z;
} Vec3;

Vec3 Vec3_add(Vec3 a, Vec3 b);

Vec3 Vec3_sub(Vec3 a, Vec3 b);

#endif