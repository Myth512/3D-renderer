#include <stdlib.h>
#include <stdio.h>

#include "sdl_wrapper.h"
#include "render.h"
#include "math.h"


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


double deg_to_rad(double angle) {
    return angle / 180.0 * 3.14;
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


double interpolate(double x, double x0, double x1, double y0, double y1) {
    double t = y1 - y0;
    double p = (x - x0) / (x1 - x0);
    return y0 + t * p;
}


Vec2 project(Context *ctx, Camera *camera, Vec3 point) {
    Vec3 rel = Vec3_sub(camera->postition, point);
    rel = rotate_y(rel, -camera->rotation.x);
    rel = rotate_z(rel, camera->rotation.y);

    double fov_rad = deg_to_rad(camera->fov);

    double a = (double)ctx->width / ctx->height;

    double fx = 1.0f / tan(fov_rad / 2);
    double fy = a * fx;

    double x = rel.z / rel.x * fx;
    double y = rel.y / rel.x * fy;

    x = (x + 1) * 0.5 * ctx->width;
    y = (y + 1) * 0.5 * ctx->height;
    return (Vec2){x, y};
}


void init_mesh(Mesh *mesh, Vertex *vertices, Face *faces, int face_count) {
    mesh->face_count = face_count;
    mesh->vertices = vertices; 
    mesh->faces = faces; 
}


void render_background(Camera *camera, Context *ctx) {
    Color sky_color = (Color){117, 187, 254};
    Color floor_color = (Color){37, 37, 37};

    double angle = atan(camera->rotation.y);
    double pos = (angle + 1) * 480 / 2;

    for (int y = 0; y < pos; y++) {
        for (int x = 0; x <= 640; x++) {
            set_pixel(ctx, x, y, sky_color);
        }
    }

    for (int y = pos; y < 480; y++) {
        for (int x = 0; x < 640; x++) {
            set_pixel(ctx, x, y, floor_color);
        }
    }


}


void render_object(Camera *camera, Context *ctx, Object *object) {
    for (int i = 0; i < object->mesh.face_count; i++) {
        Vertex v1 = object->mesh.vertices[object->mesh.faces[i].v1];
        Vertex v2 = object->mesh.vertices[object->mesh.faces[i].v2];
        Vertex v3 = object->mesh.vertices[object->mesh.faces[i].v3];

        Vec3 t1 = Vec3_add(v1.position,  object->posistion);
        Vec3 t2 = Vec3_add(v2.position, object->posistion);
        Vec3 t3 = Vec3_add(v3.position, object->posistion);

        Vec2 p1 = project(ctx, camera, t1);
        Vec2 p2 = project(ctx, camera, t2);
        Vec2 p3 = project(ctx, camera, t3);

        draw_line_gradient(ctx, p1, p2, v1.color, v2.color);
        draw_line_gradient(ctx, p1, p3, v1.color, v3.color);
        draw_line_gradient(ctx, p2, p3, v2.color, v3.color);
    }

}