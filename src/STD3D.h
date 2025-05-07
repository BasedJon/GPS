#pragma once

// STD
#include <random>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>

// INCLUDE FMT
#define FMT_HEADER_ONLY
#include <fmt/core.h>

// GLM
#include <glm/glm.hpp>

// PRIMITIVE TYPES
struct vec2 {
    float x, y;
};
struct vec3 {
    float x, y, z;
};
struct vec4 {
    float x, y, z, w;
};
struct mat4 {
    float m[16];
};

// RANDOM INIT
extern std::random_device GPS_STD3D_random_number_device;
extern std::mt19937 GPS_STD3D_random_number_generator;

int STD3D_random_int_in_range(int min, int max);
float STD3D_random_float_in_range(float min, float max);
std::vector<char> STD3D_file_get_binary_data(const std::string &filename);

// VEC ADD SUB SCALE
vec2 STD3D_vec2_addition(const vec2 &a, const vec2 &b);
vec2 STD3D_vec2_subtraction(const vec2 &a, const vec2 &b);
vec2 STD3D_vec2_scalar(const vec2 &v, float scalar);

vec3 STD3D_vec3_addition(const vec3 &a, const vec3 &b);
vec3 STD3D_vec3_subtraction(const vec3 &a, const vec3 &b);
vec3 STD3D_vec3_scalar(const vec3 &v, float scalar);

vec4 STD3D_vec4_addition(const vec4 &a, const vec4 &b);
vec4 STD3D_vec4_subtraction(const vec4 &a, const vec4 &b);
vec4 STD3D_vec4_scalar(const vec3 &v, float scalar);

// VEC DOT PRODUCT
float STD3D_vec2_dot_product(const vec2 &a, const vec2 &b);
float STD3D_vec3_dot_product(const vec3 &a, const vec3 &b);
float STD3D_vec4_dot_product(const vec4 &a, const vec4 &b);

// VEC LENGTH
float STD3D_vec2_length(const vec2 &v);
float STD3D_vec3_length(const vec3 &v);
float STD3D_vec4_length(const vec4 &v);

// VEC NORMALIZE
vec2 STD3D_vec2_normalize(const vec2 &v);
vec3 STD3D_vec3_normalize(const vec3 &v);
vec4 STD3D_vec4_normalize(const vec4 &v);

// VEC4 TO NDC
vec3 STD3D_vec4_to_ndc(const vec4 &v); 

// VEC3 NDC TO VIEWPORT COORDS
vec3 STD3D_ndc_to_viewport(const vec3 &ndc, uint32_t viewport_width, uint32_t viewport_height);

// VEC DISTANCE
float STD3D_vec2_distance(const vec2 &a, const vec2 &b);
float STD3D_vec3_distance(const vec3 &a, const vec3 &b);
float STD3D_vec4_distance(const vec4 &a, const vec4 &b);

// VEC3 CROSS PRODUCT
vec3 STD3D_vec3_cross_product(const vec3& a, const vec3& b);

// MAT4 IDENTITY
mat4 STD3D_mat4_identity();

// MAT4 TRANSPONE
mat4 STD3D_mat4_transpose(const mat4& m);

// MAT VEC MULTIPLICATION
vec3 STD3D_mat4_vec3_multiply(const mat4 &m, const vec3 &v);
vec4 STD3D_mat4_vec4_multiply(const mat4 &m, const vec4 &v);

// MAT4 MULTIPLICATION
mat4 STD3D_mat4_multiply(const mat4 &a, const mat4 &b);

// MAT4 INVERSION
mat4 STD3D_mat4_inverse(const mat4 &m);

// PERSPECTIVE PROJECTION MATRIX CREATE
mat4 STD3D_mat4_perspective_projection(float fov, float aspect, float near, float far);

// VIEW MATRIX CREATE
mat4 STD3D_mat4_view(const vec3& pos, const vec3& target, const vec3& up);

// VIEW DIRECTION MATRIX CREATE
mat4 STD3D_mat4_view_direction(const vec3& pos, const vec3& direction, const vec3& up);

// ORTHOGRAPHIC MATRIX CREATE
mat4 STD3D_mat4_orthographic_projection(float left, float right, float bottom, float top, float near, float far);

// VEC3 GET DIRECTION 
vec3 STD3D_vec3_direction(const vec3& from, const vec3& to);

// TRANSLATION MATRIX CREATE
mat4 STD3D_mat4_translation(const vec3& translation);

// SCAILING MATRIX CREATE
mat4 STD3D_mat4_scale(const vec3& scale);

// ROTATE MATRIX YAW
mat4 STD3D_mat4_rotate_yaw(float angle_radians);

// ROTATE MATRIX PITCH
mat4 STD3D_mat4_rotate_pitch(float angle_radians);

// ROTATE MATRIX ROLL
mat4 STD3D_mat4_rotate_roll(float angle_radians);

// CLIP VERTEX
vec4 STD3D_vertex_clip(const vec4 &v1, const vec4 &v2);