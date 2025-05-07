#pragma once

// INCLUDE STD & SDL
#include "STD3D.h"
#include "GPS_SDL_INIT.h"

// GPS STRUCTS

struct face {
    uint32_t v1, v2, v3;
};
struct vertex {
    vec4 pos_original;
    vec4 pos_transformed;
    vec4 col;
    vec2 uv;
    vec3 normal;
};
struct mesh {
    vertex* vertices;
    uint32_t vertex_count;
    face* faces;
    uint32_t face_count;
};
struct camera {
    vec3 pos;
    vec3 target;
    vec3 up;
    vec3 right;
    mat4 view_matrix;
    mat4 projection_matrix;
};
struct projection_matrix_template {
    float fov;
    float aspect_ratio;
    float near_plane;
    float far_plane;
};

// GPS FUNCS

vec4 GPS_FUNC_transform_vertex_with_model_view_projection(const vertex &vertex, const mat4 &model, const mat4 &view, const mat4 &projection);
void GPS_FUNC_transform_mesh_to_world_space(mesh &mesh, const mat4 &model, const mat4 &view, const mat4 &projection);
void GPS_FUNC_camera_update();
void GPS_FUNC_render();


// GPS VARS
extern uint32_t TICKRATE;
extern camera CAMERA;
extern mat4 VIEW_MATRIX;
extern mat4 PROJECTION_MATRIX;
extern projection_matrix_template TEMPLATE_PROJECTION_MATRIX;
extern std::vector<mesh> MESH_DATA;
extern std::vector<mat4> MODEL_DATA;

