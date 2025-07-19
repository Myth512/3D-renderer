#ifndef RENDER_H
#define RENDER_H

typedef struct {
    double x;
    double y;
} Vec2;

typedef struct {
    double x;
    double y;
    double z;
} Vec3;

typedef struct {
    Vec3 postition;
    Vec2 rotation;
    double fov;
} Camera;

typedef struct {
    Vec3 position;
    Color color;
} Vertex;

typedef struct {
    int v1;
    int v2;
    int v3;
} Face;

typedef struct {
    Vertex *vertices;
    int vertex_count;
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

Vec2 project(Camera *camera, Vec3 point);

void init_mesh(Mesh *mesh, int vertex_count, int face_count);

void add_vertex(Mesh *mesh, Vertex vertex);

void add_face(Mesh *mesh, Face face);

void render_object(Camera *camera, Context *ctx, Object *object);

#endif