#include "STD3D.h"

// RANDOM INIT
std::random_device GPS_STD3D_random_number_device;
std::mt19937 GPS_STD3D_random_number_generator(GPS_STD3D_random_number_device());

int STD3D_random_int_in_range(int min, int max) {
    std::uniform_int_distribution<int> range(min, max);
    int random_number = range(GPS_STD3D_random_number_generator);
    return random_number;
}
float STD3D_random_float_in_range(float min, float max) {
    std::uniform_real_distribution<float> range(min, max);
    float random_number = range(GPS_STD3D_random_number_generator);
    return random_number;
}

std::vector<char> STD3D_file_get_binary_data(const std::string &filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "STD3D_file_get_binary_data failed to open a file:  " << filename << std::endl;
    }

    size_t file_size = (size_t)file.tellg();
    std::vector<char> buffer(file_size);

    file.seekg(0);
    file.read(buffer.data(), file_size);
    file.close();

    return buffer;
}

// VEC ADD SUB SCALE
vec2 STD3D_vec2_addition(const vec2 &a, const vec2 &b) {
    return {a.x + b.x, a.y + b.y};
}
vec2 STD3D_vec2_subtraction(const vec2 &a, const vec2 &b) {
    return {a.x - b.x, a.y - b.y };
}
vec2 STD3D_vec2_scalar(const vec2 &v, float scalar) {
    return {v.x * scalar, v.y * scalar};
}

vec3 STD3D_vec3_addition(const vec3 &a, const vec3 &b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}
vec3 STD3D_vec3_subtraction(const vec3 &a, const vec3 &b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}
vec3 STD3D_vec3_scalar(const vec3 &v, float scalar) {
    return {v.x * scalar, v.y * scalar, v.z * scalar};
}

vec4 STD3D_vec4_addition(const vec4 &a, const vec4 &b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}
vec4 STD3D_vec4_subtraction(const vec4 &a, const vec4 &b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}
vec4 STD3D_vec4_scalar(const vec4 &v, float scalar) {
    return {v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar};
}

// VEC DOT PRODUCT
float STD3D_vec2_dot_product(const vec2 &a, const vec2 &b) {
    return a.x * b.x + a.y * b.y;
}
float STD3D_vec3_dot_product(const vec3 &a, const vec3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
float STD3D_vec4_dot_product(const vec4 &a, const vec4 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

// VEC LENGTH
float STD3D_vec2_length(const vec2 &v) {
    return sqrtf(STD3D_vec2_dot_product(v, v));
}
float STD3D_vec3_length(const vec3 &v) {
    return sqrtf(STD3D_vec3_dot_product(v, v));
}
float STD3D_vec4_length(const vec4 &v) {
    return sqrtf(STD3D_vec4_dot_product(v, v));
}

// VEC NORMALIZE
vec2 STD3D_vec2_normalize(const vec2 &v) {
    float length = STD3D_vec2_length(v);
    return { v.x / length, v.y / length };
}
vec3 STD3D_vec3_normalize(const vec3 &v) {
    float length = STD3D_vec3_length(v);
    return { v.x / length, v.y / length, v.z / length };
}
vec4 STD3D_vec4_normalize(const vec4 &v) {
    float length = STD3D_vec4_length(v);
    return { v.x / length, v.y / length, v.z / length, v.w / length };
}

// VEC4 TO NDC
vec3 STD3D_vec4_to_ndc(const vec4 &v) {
    return {v.x / v.w, v.y / v.w, v.z / v.w};
}

// VEC3 NDC TO VIEWPORT COORDS
vec3 STD3D_ndc_to_viewport(const vec3 &ndc, uint32_t viewport_width, uint32_t viewport_height) {
    vec3 viewport_coords;
    viewport_coords.x = (ndc.x + 1.0f) * 0.5f * viewport_width;
    viewport_coords.y = (1.0f - ndc.y) * 0.5f * viewport_height;
    viewport_coords.z = ndc.z;
    return viewport_coords;
}

// VEC DISTANCE
float STD3D_vec2_distance(const vec2 &a, const vec2 &b) {
    return STD3D_vec2_length(STD3D_vec2_subtraction(a, b));
}

float STD3D_vec3_distance(const vec3 &a, const vec3 &b) {
    return STD3D_vec3_length(STD3D_vec3_subtraction(a, b));
}

float STD3D_vec4_distance(const vec4 &a, const vec4 &b) {
    return STD3D_vec4_length(STD3D_vec4_subtraction(a, b));
}


// VEC3 CROSS PRODUCT
vec3 STD3D_vec3_cross_product(const vec3& a, const vec3& b) {
    vec3 vec3_cross_product;
    vec3_cross_product.x = a.y * b.z - a.z * b.y;
    vec3_cross_product.y = a.z * b.x - a.x * b.z;
    vec3_cross_product.z = a.x * b.y - a.y * b.x;
    return vec3_cross_product;
}

// VEC4 INTERPOLATE
vec4 STD3D_vec4_interpolate(vec4 a, vec4 b, float interpolation_factor) {
    vec4 vec4_interpolated;
    vec4_interpolated.x = a.x + interpolation_factor * (b.x - a.x);
    vec4_interpolated.y = a.y + interpolation_factor * (b.y - a.y);
    vec4_interpolated.z = a.z + interpolation_factor * (b.z - a.z);
    vec4_interpolated.w = a.w + interpolation_factor * (b.w - a.w);
    return vec4_interpolated;
}

// MAT4 IDENTITY
mat4 STD3D_mat4_identity() {
    mat4 mat4_idenity{};
    mat4_idenity.m[0]  = 1.0f;
    mat4_idenity.m[5]  = 1.0f;
    mat4_idenity.m[10] = 1.0f;
    mat4_idenity.m[15] = 1.0f;
    return mat4_idenity;
}

mat4 STD3D_mat4_transpose(const mat4& m) {
    mat4 mat4_transposed;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            mat4_transposed.m[row * 4 + col] = m.m[col * 4 + row];
        }
    }
    return mat4_transposed;
}

// MAT VEC MULTIPLICATION
vec3 STD3D_mat4_vec3_multiply(const mat4 &m, const vec3 &v) {
    vec3 vec3_multiplied_by_mat4;
    vec3_multiplied_by_mat4.x = m.m[0] * v.x + m.m[4] * v.y + m.m[8] * v.z + m.m[12];
    vec3_multiplied_by_mat4.y = m.m[1] * v.x + m.m[5] * v.y + m.m[9] * v.z + m.m[13];
    vec3_multiplied_by_mat4.z = m.m[2] * v.x + m.m[6] * v.y + m.m[10] * v.z + m.m[14];
    return vec3_multiplied_by_mat4;
}
vec4 STD3D_mat4_vec4_multiply(const mat4 &m, const vec4 &v) {
    vec4 vec4_multiplied_by_mat4;
    vec4_multiplied_by_mat4.x = m.m[0] * v.x + m.m[4] * v.y + m.m[8] * v.z + m.m[12] * v.w;
    vec4_multiplied_by_mat4.y = m.m[1] * v.x + m.m[5] * v.y + m.m[9] * v.z + m.m[13] * v.w;
    vec4_multiplied_by_mat4.z = m.m[2] * v.x + m.m[6] * v.y + m.m[10] * v.z + m.m[14] * v.w;
    vec4_multiplied_by_mat4.w = m.m[3] * v.x + m.m[7] * v.y + m.m[11] * v.z + m.m[15] * v.w;
    return vec4_multiplied_by_mat4;
}

// MAT4 MULTIPLICATION
mat4 STD3D_mat4_multiply(const mat4 &a, const mat4 &b) {
    mat4 mat4_multiplied;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            mat4_multiplied.m[i + j * 4] = a.m[i] * b.m[j * 4] + a.m[i + 4] * b.m[j * 4 + 1] + a.m[i + 8] * b.m[j * 4 + 2] + a.m[i + 12] * b.m[j * 4 + 3];
        }
    }
    return mat4_multiplied;
}

// MAT4 INVERSION
mat4 STD3D_mat4_inverse(const mat4 &m) {
    mat4 result;

    float det = m.m[0] * (m.m[5] * m.m[10] * m.m[15] - m.m[6] * m.m[9] * m.m[15] - m.m[7] * m.m[10] * m.m[14] + m.m[7] * m.m[9] * m.m[13])
                - m.m[1] * (m.m[4] * m.m[10] * m.m[15] - m.m[6] * m.m[8] * m.m[15] - m.m[7] * m.m[10] * m.m[12] + m.m[7] * m.m[8] * m.m[13])
                + m.m[2] * (m.m[4] * m.m[9] * m.m[15] - m.m[5] * m.m[8] * m.m[15] - m.m[7] * m.m[9] * m.m[12] + m.m[7] * m.m[8] * m.m[13])
                - m.m[3] * (m.m[4] * m.m[9] * m.m[14] - m.m[5] * m.m[8] * m.m[14] - m.m[6] * m.m[9] * m.m[12] + m.m[6] * m.m[8] * m.m[13]);

    if (det == 0) {
        return result;
    }

    float invDet = 1.0f / det;

    result.m[0] = invDet * (m.m[5] * m.m[10] * m.m[15] - m.m[6] * m.m[9] * m.m[15] - m.m[7] * m.m[10] * m.m[14] + m.m[7] * m.m[9] * m.m[13]);

    return result;
}

// PERSPECTIVE PROJECTION MATRIX CREATE
mat4 STD3D_mat4_perspective_projection(float fov, float aspect, float near, float far) {
    mat4 mat4_perspective_projection;
    float tangent_half_fov = tan(fov / 2.0f);

    mat4_perspective_projection.m[0] = 1.0f / (aspect * tangent_half_fov);
    mat4_perspective_projection.m[1] = 0.0f;
    mat4_perspective_projection.m[2] = 0.0f;
    mat4_perspective_projection.m[3] = 0.0f;

    mat4_perspective_projection.m[4] = 0.0f;
    mat4_perspective_projection.m[5] = 1.0f / tangent_half_fov;
    mat4_perspective_projection.m[6] = 0.0f;
    mat4_perspective_projection.m[7] = 0.0f;

    mat4_perspective_projection.m[8] = 0.0f;
    mat4_perspective_projection.m[9] = 0.0f;
    mat4_perspective_projection.m[10] = -(far + near) / (far - near);
    mat4_perspective_projection.m[11] = -1.0f;

    mat4_perspective_projection.m[12] = 0.0f;
    mat4_perspective_projection.m[13] = 0.0f;
    mat4_perspective_projection.m[14] = -(2.0f * far * near) / (far - near);
    mat4_perspective_projection.m[15] = 0.0f;

    return mat4_perspective_projection;
}

// VIEW MATRIX CREATE
mat4 STD3D_mat4_view(const vec3& pos, const vec3& target, const vec3& up) {
    vec3 f = STD3D_vec3_normalize(STD3D_vec3_subtraction(target, pos));
    vec3 r = STD3D_vec3_normalize(STD3D_vec3_cross_product(up, f));
    vec3 u = STD3D_vec3_cross_product(f, r);

    mat4 mat4_view = {};
    mat4_view.m[0] = r.x;
    mat4_view.m[1] = u.x;
    mat4_view.m[2] = -f.x;
    mat4_view.m[3] = 0.0f;

    mat4_view.m[4] = r.y;
    mat4_view.m[5] = u.y;
    mat4_view.m[6] = -f.y;
    mat4_view.m[7] = 0.0f;

    mat4_view.m[8] = r.z;
    mat4_view.m[9] = u.z;
    mat4_view.m[10] = -f.z;
    mat4_view.m[11] = 0.0f;

    mat4_view.m[12] = -STD3D_vec3_dot_product(r, pos);
    mat4_view.m[13] = -STD3D_vec3_dot_product(u, pos);
    mat4_view.m[14] = STD3D_vec3_dot_product(f, pos);
    mat4_view.m[15] = 1.0f;

    return mat4_view;
}

// VIEW DIRECTION MATRIX CREATE
mat4 STD3D_mat4_view_direction(const vec3& pos, const vec3& direction, const vec3& up) {
    vec3 z = STD3D_vec3_normalize(STD3D_vec3_scalar(direction, -1.0f));
    vec3 x = STD3D_vec3_normalize(STD3D_vec3_cross_product(up, z));
    vec3 y = STD3D_vec3_cross_product(z, x);

    mat4 mat4_view_direction = STD3D_mat4_identity();

    mat4_view_direction.m[0] = x.x;
    mat4_view_direction.m[1] = y.x;
    mat4_view_direction.m[2] = z.x;
    mat4_view_direction.m[3] = 0.0f;

    mat4_view_direction.m[4] = x.y;
    mat4_view_direction.m[5] = y.y;
    mat4_view_direction.m[6] = z.y;
    mat4_view_direction.m[7] = 0.0f;

    mat4_view_direction.m[8]  = x.z;
    mat4_view_direction.m[9]  = y.z;
    mat4_view_direction.m[10] = z.z;
    mat4_view_direction.m[11] = 0.0f;

    mat4_view_direction.m[12] = -STD3D_vec3_dot_product(x, pos);
    mat4_view_direction.m[13] = -STD3D_vec3_dot_product(y, pos);
    mat4_view_direction.m[14] = -STD3D_vec3_dot_product(z, pos);
    mat4_view_direction.m[15] = 1.0f;

    return mat4_view_direction;
}

// ORTHOGRAPHIC MATRIX CREATE
mat4 STD3D_mat4_orthographic_projection(float left, float right, float bottom, float top, float near, float far) {
    mat4 mat4_orthnograpic_projection = {};

    mat4_orthnograpic_projection.m[0] = 2.0f / (right - left);
    mat4_orthnograpic_projection.m[5] = 2.0f / (top - bottom);
    mat4_orthnograpic_projection.m[10] = -2.0f / (far - near);

    mat4_orthnograpic_projection.m[12] = -(right + left) / (right - left);
    mat4_orthnograpic_projection.m[13] = -(top + bottom) / (top - bottom);
    mat4_orthnograpic_projection.m[14] = -(far + near) / (far - near);

    mat4_orthnograpic_projection.m[15] = 1.0f;

    return mat4_orthnograpic_projection;
}

// VEC3 GET DIRECTION 
vec3 STD3D_vec3_direction(const vec3& from, const vec3& to) {
    return STD3D_vec3_normalize(STD3D_vec3_subtraction(to, from));
}

// TRANSLATION MATRIX CREATE
mat4 STD3D_mat4_translation(const vec3& translation) {
    mat4 mat4_translation = STD3D_mat4_identity();

    mat4_translation.m[12] = translation.x;
    mat4_translation.m[13] = translation.y;
    mat4_translation.m[14] = translation.z;

    return mat4_translation;
}

// SCAILING MATRIX CREATE
mat4 STD3D_mat4_scale(const vec3& scale) {
    mat4 mat4_scale = {};

    mat4_scale.m[0] = scale.x;
    mat4_scale.m[5] = scale.y;
    mat4_scale.m[10] = scale.z;
    mat4_scale.m[15] = 1.0f;

    return mat4_scale;
}

// ROTATE MATRIX YAW
mat4 STD3D_mat4_rotate_yaw(float angle_radians) {
    mat4 mat4_rotation_yaw = STD3D_mat4_identity();
    float cos_angle = cosf(angle_radians);
    float sin_angle = sinf(angle_radians);

    mat4_rotation_yaw.m[0] = cos_angle;
    mat4_rotation_yaw.m[2] = sin_angle;
    mat4_rotation_yaw.m[8] = -sin_angle;
    mat4_rotation_yaw.m[10] = cos_angle;

    return mat4_rotation_yaw;
}

// ROTATE MATRIX PITCH
mat4 STD3D_mat4_rotate_pitch(float angle_radians) {
    mat4 mat4_rotation_pitch = STD3D_mat4_identity();
    float cos_angle = cosf(angle_radians);
    float sin_angle = sinf(angle_radians);

    mat4_rotation_pitch.m[5] = cos_angle;
    mat4_rotation_pitch.m[6] = sin_angle;
    mat4_rotation_pitch.m[9] = -sin_angle;
    mat4_rotation_pitch.m[10] = cos_angle;

    return mat4_rotation_pitch;
}

// ROTATE MATRIX ROLL
mat4 STD3D_mat4_rotate_roll(float angle_radians) {
    mat4 mat4_rotation_roll = STD3D_mat4_identity();
    float cos_angle = cosf(angle_radians);
    float sin_angle = sinf(angle_radians);

    mat4_rotation_roll.m[0] = cos_angle;
    mat4_rotation_roll.m[1] = sin_angle;
    mat4_rotation_roll.m[4] = -sin_angle;
    mat4_rotation_roll.m[5] = cos_angle;

    return mat4_rotation_roll;
}

// FINDS DISTANCE FROM THE CLIP PLANE, IF NEGATIVE IT IS OUTSIDE
float STD3D_vec4_clip_plane_distance(const vec4 &v, uint8_t plane_index) {
    switch (plane_index) {
        case 0: return v.x + v.w;  // x >= -w
        case 1: return v.w - v.x;  // x <= w
        case 2: return v.y + v.w;  // y >= -w
        case 3: return v.w - v.y;  // y <= w
        case 4: return v.z + v.w;  // z >= -w
        case 5: return v.w - v.z;  // z <= w
        default: return 0.0f;
    }
}

// CLIP TRAIANGLE
std::vector<vec4> STD3D_test(const vec4 &v1, const vec4 &v2, const vec4 &v3, uint8_t plane_index) {
    std::vector<vec4> polygon_to_clip = {v1, v2, v3};
    std::vector<vec4> polygon_output(3);

    polygon_to_clip.push_back(v1);
    vec4 v1_temp, v2_temp;
    float v1_in_or_out_f_value, v2_in_or_out_f_value, interpolation_factor;
    bool v1_in_or_out_bool_value, v2_in_or_out_bool_value;


    for (uint32_t i = 0; i < 3; i++) {
        v1_temp = polygon_to_clip[i];
        v2_temp = polygon_to_clip[(i + 1) % 3];
        v1_in_or_out_f_value = STD3D_vec4_clip_plane_distance(v1_temp, plane_index);
        v2_in_or_out_f_value = STD3D_vec4_clip_plane_distance(v2_temp, plane_index);
        interpolation_factor = v1_in_or_out_f_value / (v1_in_or_out_f_value - v2_in_or_out_f_value);
        v1_in_or_out_bool_value = v1_in_or_out_f_value >= 0.0f;
        v2_in_or_out_bool_value = v2_in_or_out_f_value >= 0.0f;


        if (v1_in_or_out_bool_value && v2_in_or_out_bool_value) {
            polygon_output.push_back(v2_temp);
        }
        
        else if (!v1_in_or_out_bool_value && !v2_in_or_out_bool_value) {
            continue;
        }

        else if (v1_in_or_out_bool_value && !v2_in_or_out_bool_value) {
            polygon_output.push_back(STD3D_vec4_interpolate(v1_temp, v2_temp, interpolation_factor));
        }

        else if (!v1_in_or_out_bool_value && v2_in_or_out_bool_value) {
            polygon_output.push_back(STD3D_vec4_interpolate(v1_temp, v2_temp, interpolation_factor));
            polygon_output.push_back(v2_temp);
        }
    }

    return polygon_output;
}