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

Vec3 rotate_x(Vec3 point, double angle);

Vec3 rotate_y(Vec3 point, double angle);

Vec3 rotate_z(Vec3 point, double angle);

Vec3 rotate(Vec3 point, double x, double y, double z);

#endif