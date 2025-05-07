// INCLUDE GPS
#include "GPS.h"
#include "STD3D.h"

// GPS VARS
uint32_t TICKRATE = 1000 / 60;
camera CAMERA = {
    { 0.0f, 0.0f, 5.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    {},
    {},
    {}
};
mat4 VIEW_MATRIX;
mat4 PROJECTION_MATRIX;
std::vector<mesh> MESH_DATA;
std::vector<mat4> MODEL_DATA;
projection_matrix_template TEMPLATE_PROJECTION_MATRIX;

vec4 GPS_FUNC_transform_vertex_with_model_view_projection(const vertex &vertex, const mat4 &model, const mat4 &view, const mat4 &projection) {
    vec4 vector_transformed = vertex.pos_original;

    vector_transformed = STD3D_mat4_vec4_multiply(model, vertex.pos_original);

    vector_transformed = STD3D_mat4_vec4_multiply(view, vector_transformed);

    vector_transformed = STD3D_mat4_vec4_multiply(projection, vector_transformed);

    return vector_transformed;
}

void GPS_FUNC_transform_mesh_to_world_space(mesh& mesh, const mat4 &model, const mat4 &view, const mat4 &projection) {
    for (uint32_t i = 0, size = mesh.vertex_count; i < size; i++) {
        mesh.vertices[i].pos_transformed = GPS_FUNC_transform_vertex_with_model_view_projection(mesh.vertices[i], model, view, projection);
    }
}

void GPS_FUNC_camera_update() {
    vec3 forward = STD3D_vec3_direction(CAMERA.pos, CAMERA.target);
    CAMERA.right = STD3D_vec3_normalize(STD3D_vec3_cross_product(forward, CAMERA.up));
}


void GPS_FUNC_render() {
    vec3 v1, v2, v3;
    SDL_SetRenderDrawColor(GPS_SDL_RENDERER, 255, 255, 255, 255);
    for (uint32_t i = 0, size = MESH_DATA.size(); i < size; i++) {
        mesh mesh = MESH_DATA[i];
        for (uint32_t j = 0, size = mesh.face_count; j < size; j++) {
            face face = mesh.faces[j];
            fmt::print("v1 x = {}, y = {}, z = {}, w = {} \n", mesh.vertices[face.v1].pos_transformed.x, mesh.vertices[face.v1].pos_transformed.y, mesh.vertices[face.v1].pos_transformed.z, mesh.vertices[face.v1].pos_transformed.w);
            fmt::print("v2 x = {}, y = {}, z = {}, w = {} \n", mesh.vertices[face.v2].pos_transformed.x, mesh.vertices[face.v2].pos_transformed.y, mesh.vertices[face.v2].pos_transformed.z, mesh.vertices[face.v2].pos_transformed.w);
            fmt::print("v3 x = {}, y = {}, z = {}, w = {} \n", mesh.vertices[face.v3].pos_transformed.x, mesh.vertices[face.v3].pos_transformed.y, mesh.vertices[face.v3].pos_transformed.z, mesh.vertices[face.v3].pos_transformed.w);
            v1 = STD3D_ndc_to_viewport(STD3D_vec4_to_ndc(mesh.vertices[face.v1].pos_transformed), GPS_SDL_WINDOW_WIDTH, GPS_SDL_WINDOW_HEIGHT);
            v2 = STD3D_ndc_to_viewport(STD3D_vec4_to_ndc(mesh.vertices[face.v2].pos_transformed), GPS_SDL_WINDOW_WIDTH, GPS_SDL_WINDOW_HEIGHT);
            v3 = STD3D_ndc_to_viewport(STD3D_vec4_to_ndc(mesh.vertices[face.v3].pos_transformed), GPS_SDL_WINDOW_WIDTH, GPS_SDL_WINDOW_HEIGHT);

            SDL_RenderLine(GPS_SDL_RENDERER, v1.x, v1.y, v2.x, v2.y);   
            SDL_RenderLine(GPS_SDL_RENDERER, v2.x, v2.y, v3.x, v3.y);
            SDL_RenderLine(GPS_SDL_RENDERER, v3.x, v3.y, v1.x, v1.y);
        }
    }
}

