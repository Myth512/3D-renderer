#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "sdl_wrapper.h"
#include "render.h"
#include "camera.h"


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
            draw_pixel(ctx, x, y, c);
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
            draw_pixel(ctx, x, y, c);
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
            draw_pixel(ctx, x, y, c);
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
            draw_pixel(ctx, x, y, c);
            x += k;
        }
    }
}


double deg_to_rad(double angle) {
    return angle / 180.0 * 3.14;
}


Vec3 project(Context *ctx, Camera *camera, Vec3 point) {
    Vec3 rel = Vec3_sub(point, camera->position);
    rel = rotate_y(rel, -camera->rotation.x);
    rel = rotate_z(rel, camera->rotation.y);

    if (rel.x < 0)
        return (Vec3){-1, -1, rel.x};

    double fov_rad = deg_to_rad(camera->fov);

    double a = (double)ctx->width / ctx->height;

    double fx = 1.0f / tan(fov_rad / 2);
    double fy = a * fx;

    double x = rel.z / rel.x * fx;
    double y = rel.y / rel.x * fy;

    x = (x + 1) * 0.5 * ctx->width;
    y = (y + 1) * 0.5 * ctx->height;
    return (Vec3){x, y, rel.x};
}


void init_mesh(Mesh *mesh, Vertex *vertices, Face *faces, int face_count) {
    mesh->face_count = face_count;
    mesh->vertices = vertices; 
    mesh->faces = faces; 
}


void draw_polygon_outline(Context *ctx, Vec2 p0, Vec2 p1, Vec2 p2, Color c) {
    draw_line(ctx, p0, p1, c);
    draw_line(ctx, p0, p2, c);
    draw_line(ctx, p1, p2, c);
}


Vec3 compute_barycentric_weights(Vec2 p, Vec2 a, Vec2 b, Vec2 c) {
    double denominator = (b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y);
    double alpha = ((b.y - c.y) * (p.x - c.x) + (c.x - b.x) * (p.y - c.y)) / denominator;
    double beta = ((c.y - a.y) * (p.x - c.x) + (a.x - c.x) * (p.y - c.y)) / denominator;
    double gamma = 1 - alpha - beta;
    return (Vec3){alpha, beta, gamma};
}


static void draw_top_flat_triangle(Context *ctx, Vec2 p0, Vec2 p1, Vec2 p2, Color c) {
    double k0 = (p2.x - p0.x) / (p2.y - p0.y);
    double k1 = (p2.x - p1.x) / (p2.y - p1.y);

    if (k0 < k1) {
        double tmp = k0;
        k0 = k1;
        k1 = tmp;
    }

    double x_left = p2.x;
    double x_right = p2.x;

    for (int y = p2.y; y > p0.y; y--) {
        for (int x = x_left; x <= x_right; x++) {
            draw_pixel(ctx, x, y, c);
        }
        x_left -= k0;
        x_right -= k1;
    }
}


static void draw_botton_flat_triangle(Context *ctx, Vec2 p0, Vec2 p1, Vec2 p2, Color c) {
    double k0 = (p0.x - p1.x) / (p0.y - p1.y);
    double k1 = (p0.x - p2.x) / (p0.y - p2.y);

    if (k0 > k1) {
        double tmp = k0;
        k0 = k1;
        k1 = tmp;
    }

    double x_left = p0.x;
    double x_right = p0.x;

    for (int y = p0.y; y < p2.y; y++) {
        for (int x = x_left; x <= x_right; x++) {
            draw_pixel(ctx, x, y, c);
        }
        x_left += k0;
        x_right += k1;
    }
}


void draw_filled_triangle(Context *ctx, Vec2 p0, Vec2 p1, Vec2 p2, Color c) {
    Vec2 tmp;
    if (p0.y > p1.y) {
        tmp = p0;
        p0 = p1;
        p1 = tmp;
    }
    if (p1.y > p2.y) {
        tmp = p1;
        p1 = p2;
        p2 = tmp;
    }
    if (p0.y > p1.y) {
        tmp = p0;
        p0 = p1;
        p1 = tmp;
    }

    if (p0.y == p1.y) {
        draw_top_flat_triangle(ctx, p0, p1, p2, c);
    } else if (p1.y == p2.y) {
        draw_botton_flat_triangle(ctx, p0, p1, p2, c);
    } else {
        double k = (p0.y - p2.y) / (p0.x - p2.x);
        double b = p0.y - k * p0.x;
        
        double x = isfinite(k) ? (p1.y - b) / k : p0.x;

        Vec2 p3 = {x, p1.y};

        draw_botton_flat_triangle(ctx, p0, p1, p3, c);
        draw_top_flat_triangle(ctx, p1, p3, p2, c);
    }
}


static void draw_top_flat_triangle_gradient(Context *ctx, Vec3 p0, Vec3 p1, Vec3 p2, Color c0, Color c1, Color c2) {
    double k0 = (p2.x - p0.x) / (p2.y - p0.y);
    double k1 = (p2.x - p1.x) / (p2.y - p1.y);

    if (k0 < k1) {
        double tmp = k0;
        k0 = k1;
        k1 = tmp;
    }

    double x_left = p2.x;
    double x_right = p2.x;

    for (int y = p2.y; y >= p0.y; y--) {
        for (int x = x_left; x <= x_right; x++) {
            if (x < 0 || x >= ctx->width || y < 0 || y >= ctx->height)
                continue;

            Vec3 w = compute_barycentric_weights((Vec2){x, y}, (Vec2){p0.x, p0.y}, (Vec2){p1.x, p1.y}, (Vec2){p2.x, p2.y});
            Color c = {
                c.r = c0.r * w.x + c1.r * w.y + c2.r * w.z,
                c.g = c0.g * w.x + c1.g * w.y + c2.g * w.z,
                c.b = c0.b * w.x + c1.b * w.y + c2.b * w.z,
            };
            double z = p0.z * w.x + p1.z * w.y + p2.z * w.z;

            if (z < ctx->depth_buffer[y * ctx->width + x]) {
                draw_pixel(ctx, x, y, c);
                ctx->depth_buffer[y * ctx->width + x] = z;
            }
        }
        x_left -= k0;
        x_right -= k1;
    }
}


static void draw_botton_flat_triangle_gradient(Context *ctx, Vec3 p0, Vec3 p1, Vec3 p2, Color c0, Color c1, Color c2) {
    double k0 = (p0.x - p1.x) / (p0.y - p1.y);
    double k1 = (p0.x - p2.x) / (p0.y - p2.y);

    if (k0 > k1) {
        double tmp = k0;
        k0 = k1;
        k1 = tmp;
    }

    double x_min = fmin(fmin(p0.x, p1.x), p2.x);
    double x_max = fmax(fmax(p0.x, p1.x), p2.x);

    double x_left = p0.x;
    double x_right = p0.x;

    for (int y = p0.y; y <= p2.y; y++) {
        for (int x = x_left; x <= x_right; x++) {
            if (x < 0 || x >= ctx->width || y < 0 || y >= ctx->height)
                continue;

            if (x < x_min || x > x_max)
                continue;

            Vec3 w = compute_barycentric_weights((Vec2){x, y}, (Vec2){p0.x, p0.y}, (Vec2){p1.x, p1.y}, (Vec2){p2.x, p2.y});
            Color c = {
                c.r = c0.r * w.x + c1.r * w.y + c2.r * w.z,
                c.g = c0.g * w.x + c1.g * w.y + c2.g * w.z,
                c.b = c0.b * w.x + c1.b * w.y + c2.b * w.z,
            };
            double z = p0.z * w.x + p1.z * w.y + p2.z * w.z;

            if (z < ctx->depth_buffer[y * ctx->width + x]) {
                draw_pixel(ctx, x, y, c);
                ctx->depth_buffer[y * ctx->width + x] = z;
            }
        }
        x_left += k0;
        x_right += k1;
    }
}


void draw_triangle_gradient(Context *ctx, Vec3 p0, Vec3 p1, Vec3 p2, Color c0, Color c1, Color c2) {
    Vec3 tmp;
    Color t;
    if (p0.y > p1.y) {
        tmp = p0;
        p0 = p1;
        p1 = tmp;

        t = c0;
        c0 = c1;
        c1 = t;

    }
    if (p1.y > p2.y) {
        tmp = p1;
        p1 = p2;
        p2 = tmp;

        t = c1;
        c1 = c2;
        c2 = t;
    }
    if (p0.y > p1.y) {
        tmp = p0;
        p0 = p1;
        p1 = tmp;

        t = c0;
        c0 = c1;
        c1 = t;
    }

    if (p0.y == p1.y) {
        draw_top_flat_triangle_gradient(ctx, p0, p1, p2, c0, c1, c2);
    } else if (p1.y == p2.y) {
        draw_botton_flat_triangle_gradient(ctx, p0, p2, p1, c0, c1, c2);
    } else {
        double p = (p1.y - p2.y) / (p0.y - p2.y);
        
        double x = p0.x * p + p2.x * (1 - p);
        double z = p0.z * p + p2.z * (1 - p);

        Vec3 p3 = {x, p1.y, z};

        Color c3 = {
            c0.r * p + c2.r * (1 - p),
            c0.g * p + c2.g * (1 - p),
            c0.b * p + c2.b * (1 - p),
        };

        draw_botton_flat_triangle_gradient(ctx, p0, p3, p1, c0, c3, c1);
        draw_top_flat_triangle_gradient(ctx, p3, p1, p2, c3, c1, c2);
    }
}


void draw_object(Camera *camera, Context *ctx, Object *object) {
    for (int i = 0; i < object->mesh.face_count; i++) {
        Vertex v1 = object->mesh.vertices[object->mesh.faces[i].v1];
        Vertex v2 = object->mesh.vertices[object->mesh.faces[i].v2];
        Vertex v3 = object->mesh.vertices[object->mesh.faces[i].v3];

        Vec3 t1 = v1.position;
        Vec3 t2 = v2.position;
        Vec3 t3 = v3.position;

        t1.x *= object->scale.x;
        t1.y *= object->scale.y;
        t1.z *= object->scale.z;

        t2.x *= object->scale.x;
        t2.y *= object->scale.y;
        t3.z *= object->scale.z;

        t3.x *= object->scale.x;
        t3.y *= object->scale.y;
        t3.z *= object->scale.z;

        t1 = rotate_x(t1, object->rotation.x);
        t1 = rotate_y(t1, object->rotation.y);
        t1 = rotate_z(t1, object->rotation.z);

        t2 = rotate_x(t2, object->rotation.x);
        t2 = rotate_y(t2, object->rotation.y);
        t2 = rotate_z(t2, object->rotation.z);

        t3 = rotate_x(t3, object->rotation.x);
        t3 = rotate_y(t3, object->rotation.y);
        t3 = rotate_z(t3, object->rotation.z);

        t1 = Vec3_add(t1, object->posistion);
        t2 = Vec3_add(t2, object->posistion);
        t3 = Vec3_add(t3, object->posistion);

        Vec3 p1 = project(ctx, camera, t1);
        Vec3 p2 = project(ctx, camera, t2);
        Vec3 p3 = project(ctx, camera, t3);
        // printf("%f %f %f %d\n", p2.x, p2.y, p2.z, v2.color.r);

        draw_triangle_gradient(ctx, p1, p2, p3, v1.color, v2.color, v3.color);
        // draw_polygon_outline(ctx, p1, p2, p3, COLOR_CYAN);
    }
}