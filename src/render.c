#include "sdl_wrapper.h"
#include <stdlib.h>
#include "render.h"
#include "math.h"


Vec3 Vec3_add(Vec3 a, Vec3 b) {
    return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}


void draw_line(Context *ctx, Vec2 p0, Vec2 p1, Color c) {
    double dx = p1.x - p0.x;
    double dy = p1.y - p0.y;

    if (fabs(dx) > fabs(dy)) {
        double k = dy / dx;
        double y = p0.y;

        if (p0.x > p1.x) {
            int tmp = p0.x;
            p0.x = p1.x;
            p1.x = tmp;
            y = p1.y;
        }

        for (double x = p0.x; x <= p1.x; x++) {
            set_pixel(ctx, x, y, c);
            y += k;
        }
    } else {
        double k = dx / dy;
        double x = p0.x;

        if (p0.y > p1.y) {
            int tmp = p0.y;
            p0.y = p1.y;
            p1.y = tmp;
            x = p1.x;
        }

        for (double y = p0.y; y <= p1.y; y++) {
            set_pixel(ctx, x, y, c);
            x += k;
        }
    }
}


void draw_line_gradient(Context *ctx, Vec2 p0, Vec2 p1, Color c0, Color c1) {
    double dx = p1.x - p0.x;
    double dy = p1.y - p0.y;

    if (fabs(dx) > fabs(dy)) {
        double k = dy / dx;
        double y = p0.y;

        if (p0.x > p1.x) {
            int tmp = p0.x;
            p0.x = p1.x;
            p1.x = tmp;
            y = p1.y;
        }


        for (double x = p0.x; x <= p1.x; x++) {
            double p = (x - p0.x) / (p1.x - p0.x);
            Color c = Color_add(Color_mul(c0, p), Color_mul(c1, (1 - p)));
            set_pixel(ctx, x, y, c);
            y += k;
        }
    } else {
        double k = dx / dy;
        double x = p0.x;

        if (p0.y > p1.y) {
            int tmp = p0.y;
            p0.y = p1.y;
            p1.y = tmp;
            x = p1.x;
        }

        for (double y = p0.y; y <= p1.y; y++) {
            double p = (y - p0.y) / (p1.y - p0.y);
            Color c = Color_add(Color_mul(c0, p), Color_mul(c1, (1 - p)));
            set_pixel(ctx, x, y, c);
            x += k;
        }
    }
}


Vec2 project(Camera *camera, Vec3 point) {
    double angle = atan((camera->postition.z - point.z) / (camera->postition.x - point.x));
    double angle2 = atan((camera->postition.y - point.y) / (camera->postition.x - point.x));
    Vec2 res;
    res.x = camera->rotation.x - angle;
    res.y = camera->rotation.y - angle2;
    res.x = (res.x + 1) * 640 / 2;
    res.y = (res.y + 1) * 480 / 2;
    return res;
}


void init_mesh(Mesh *mesh, int vertex_count, int face_count) {
    mesh->vertex_count = 0;
    mesh->face_count = 0;
    mesh->vertices = malloc(vertex_count * sizeof(Vertex));
    mesh->faces = malloc(face_count * sizeof(Face));
}


void add_vertex(Mesh *mesh, Vertex vertex) {
    mesh->vertices[mesh->vertex_count++] = vertex;
}


void add_face(Mesh *mesh, Face face) {
    mesh->faces[mesh->face_count++] = face;
}


void render_object(Camera *camera, Context *ctx, Object *object) {
    for (int i = 0; i < object->mesh.face_count; i++) {
        Vertex v1 = object->mesh.vertices[object->mesh.faces[i].v1];
        Vertex v2 = object->mesh.vertices[object->mesh.faces[i].v2];
        Vertex v3 = object->mesh.vertices[object->mesh.faces[i].v3];

        Vec3 t1 = Vec3_add(v1.position,  object->posistion);
        Vec3 t2 = Vec3_add(v2.position, object->posistion);
        Vec3 t3 = Vec3_add(v3.position, object->posistion);

        Vec2 p1 = project(camera, t1);
        Vec2 p2 = project(camera, t2);
        Vec2 p3 = project(camera, t3);

        draw_line_gradient(ctx, p1, p2, v1.color, v2.color);
        draw_line_gradient(ctx, p1, p3, v1.color, v3.color);
        draw_line_gradient(ctx, p2, p3, v2.color, v3.color);
    }

}