#ifndef RENDER_H
#define RENDER_H

#include "vec.h"

typedef struct { Vec3 position;
    Color color;
} Vertex;

typedef struct {
    int v1;
    int v2;
    int v3;
} Face;

typedef struct {
    Vertex *vertices;
    Face *faces;
    int face_count;
} Mesh;

typedef struct {
    Vec3 posistion;
    Vec3 rotation;
    Vec3 scale;
    Mesh mesh;
} Object;

void draw_line(Context *ctx, Vec2 p0, Vec2 p1, Color c);

Vec2 project(Context *ctx, Camera *camera, Vec3 point);

void init_mesh(Mesh *mesh, Vertex *vertices, Face *faces, int face_count);

double interpolate(double x, double x0, double x1, double y0, double y1);

void render_polygon_outline(Context *ctx, Vec2 p0, Vec2 p1, Vec2 p2, Color c);

void render_filled_polygon(Context *ctx, Vec2 p0, Vec2 p1, Vec2 p2, Color c);

void render_background(Camera *camera, Context *ctx);

void render_object(Camera *camera, Context *ctx, Object *object);

#endif