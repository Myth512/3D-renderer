#include <math.h>
#include <stdio.h>

#include "vec.h"

Vec3 Vec3_add(Vec3 a, Vec3 b) {
    return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 Vec3_sub(Vec3 a, Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

Vec3 rotate_x(Vec3 point, double angle) {
    double s = sin(angle);
    double c = cos(angle);
    
    double z = point.z * c - point.y * s;
    double y = point.z * s + point.y * c;

    return (Vec3){point.x, y, z};
}


Vec3 rotate_y(Vec3 point, double angle) {
    double s = sin(angle);
    double c = cos(angle);
    
    double x = point.x * c - point.z * s;
    double z = point.x * s + point.z * c;

    return (Vec3){x, point.y, z};
}


Vec3 rotate_z(Vec3 point, double angle) {
    double s = sin(angle);
    double c = cos(angle);
    
    double x = point.x * c - point.y * s;
    double y = point.x * s + point.y * c;

    return (Vec3){x, y, point.z};
}