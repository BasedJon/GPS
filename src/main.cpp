
// INCLUDE GPS
#include "GPS_SDL_INIT.h"
#include "STD3D.h"
#include "GPS.h"


void debug_controls(float speed) {
    if (GPS_SDL_KEYSTATE[SDL_SCANCODE_D] == true) {
        CAMERA.pos = STD3D_vec3_addition(CAMERA.pos, STD3D_vec3_scalar(CAMERA.right, -speed));
        CAMERA.target = STD3D_vec3_addition(CAMERA.target, STD3D_vec3_scalar(CAMERA.right, -speed));
    }
    if (GPS_SDL_KEYSTATE[SDL_SCANCODE_A] == true) {
        CAMERA.pos = STD3D_vec3_addition(CAMERA.pos, STD3D_vec3_scalar(CAMERA.right, speed));
        CAMERA.target = STD3D_vec3_addition(CAMERA.target, STD3D_vec3_scalar(CAMERA.right, speed));
    }
    if (GPS_SDL_KEYSTATE[SDL_SCANCODE_LSHIFT] == true) {
        CAMERA.pos = STD3D_vec3_addition(CAMERA.pos, STD3D_vec3_scalar(CAMERA.up, -speed));
        CAMERA.target = STD3D_vec3_addition(CAMERA.target, STD3D_vec3_scalar(CAMERA.up, -speed));
    }
    if (GPS_SDL_KEYSTATE[SDL_SCANCODE_SPACE] == true) {
        CAMERA.pos = STD3D_vec3_addition(CAMERA.pos, STD3D_vec3_scalar(CAMERA.up, speed));
        CAMERA.target = STD3D_vec3_addition(CAMERA.target, STD3D_vec3_scalar(CAMERA.up, speed));
    }
    if (GPS_SDL_KEYSTATE[SDL_SCANCODE_W] == true) {
        vec3 direction = STD3D_vec3_direction(CAMERA.pos, CAMERA.target);
        CAMERA.pos = STD3D_vec3_addition(CAMERA.pos, STD3D_vec3_scalar(direction, speed));
    }
    if (GPS_SDL_KEYSTATE[SDL_SCANCODE_S] == true) {
        vec3 direction = STD3D_vec3_direction(CAMERA.pos, CAMERA.target);
        CAMERA.pos = STD3D_vec3_addition(CAMERA.pos, STD3D_vec3_scalar(direction, -speed));
    }

    if (GPS_SDL_KEYSTATE[SDL_SCANCODE_LEFT] == true) {
        mat4 yaw_matrix = STD3D_mat4_rotate_yaw(speed * 0.5);
        MODEL_DATA[0] = STD3D_mat4_multiply(MODEL_DATA[0], yaw_matrix);
    }

    if (GPS_SDL_KEYSTATE[SDL_SCANCODE_RIGHT] == true) {
        mat4 yaw_matrix = STD3D_mat4_rotate_yaw(-speed * 0.5);
        MODEL_DATA[0] = STD3D_mat4_multiply(MODEL_DATA[0], yaw_matrix);
    }
    if (GPS_SDL_KEYSTATE[SDL_SCANCODE_UP] == true) {
        mat4 pitch_matrix = STD3D_mat4_rotate_pitch(speed * 0.5);
        MODEL_DATA[0] = STD3D_mat4_multiply(MODEL_DATA[0], pitch_matrix);
    }
    if (GPS_SDL_KEYSTATE[SDL_SCANCODE_DOWN] == true) {
        mat4 pitch_matrix = STD3D_mat4_rotate_pitch(-speed * 0.5);
        MODEL_DATA[0] = STD3D_mat4_multiply(MODEL_DATA[0], pitch_matrix);
    }
    if (GPS_SDL_KEYSTATE[SDL_SCANCODE_Q] == true) {

    }
}
// LOOP
void GPS_LOOP(SDL_Event &event) {
    bool GPS_running = true;
    uint32_t ticks_start = 0;
    uint32_t ticks_end = 0;
    uint32_t ticks_counter = 0;

    while (GPS_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                GPS_running = false;
            }  
        }
    SDL_SetRenderDrawColor(GPS_SDL_RENDERER, 0, 0, 0, 255);
    SDL_RenderClear(GPS_SDL_RENDERER);
    ticks_start = SDL_GetTicks();
    ticks_counter += ticks_start - ticks_end;
    VIEW_MATRIX = STD3D_mat4_view(CAMERA.pos, CAMERA.target, CAMERA.up);

    if (ticks_counter >= TICKRATE) {
        
        GPS_FUNC_camera_update();
        for (uint32_t i = 0, size = MESH_DATA.size(); i < size; i++) {
            GPS_FUNC_transform_mesh_to_world_space(MESH_DATA[i], MODEL_DATA[i], VIEW_MATRIX, PROJECTION_MATRIX);
        }
        debug_controls(0.1);
        ticks_counter = 0;
    }
    // RENDER MATH HERE
    GPS_FUNC_render();
    ticks_end = ticks_start;
    SDL_RenderPresent(GPS_SDL_RENDERER);
    }
}

int main() {
    GPS_SDL_init();
    GPS_SDL_create_window(GPS_SDL_WINDOW, GPS_SDL_WINDOW_TITLE, GPS_SDL_WINDOW_WIDTH, GPS_SDL_WINDOW_HEIGHT);
    GPS_SDL_init_renderer();
    // CREATE MESH
    vertex cube_vertex_data[8] = {
        { { -1.0f, -1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
        { {  1.0f, -1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
        { {  1.0f,  1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
        { { -1.0f,  1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },

        { { -1.0f, -1.0f,  1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
        { {  1.0f, -1.0f,  1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
        { {  1.0f,  1.0f,  1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
        { { -1.0f,  1.0f,  1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
    };

    // CREATE CUBE FACES (12 triangles)
    face cube_face_data[12] = {
        { 0, 1, 2 }, { 0, 2, 3 },
        { 4, 5, 6 }, { 4, 6, 7 },
        { 0, 1, 5 }, { 0, 5, 4 },
        { 1, 2, 6 }, { 1, 6, 5 },
        { 2, 3, 7 }, { 2, 7, 6 },
        { 3, 0, 4 }, { 3, 4, 7 }
    };

    // Define cube mesh
    mesh cube_mesh = {};
    cube_mesh.vertices = cube_vertex_data;
    cube_mesh.vertex_count = 8;
    cube_mesh.faces = cube_face_data;
    cube_mesh.face_count = 12;

    // Add cube to mesh data
    MESH_DATA.push_back(cube_mesh);

    // Set up model matrix for the cube (identity matrix for now)
    mat4 cube_model_matrix = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    MODEL_DATA.push_back(cube_model_matrix);

    // Set up projection matrix
    TEMPLATE_PROJECTION_MATRIX.fov = 60.0f * (M_PI / 180.0f);
    TEMPLATE_PROJECTION_MATRIX.aspect_ratio = GPS_SDL_WINDOW_WIDTH / GPS_SDL_WINDOW_HEIGHT;
    TEMPLATE_PROJECTION_MATRIX.near_plane = 0.1f;
    TEMPLATE_PROJECTION_MATRIX.far_plane = 100.0f;
    PROJECTION_MATRIX = STD3D_mat4_perspective_projection(TEMPLATE_PROJECTION_MATRIX.fov,
                                                                  TEMPLATE_PROJECTION_MATRIX.aspect_ratio,
                                                                  TEMPLATE_PROJECTION_MATRIX.near_plane,
                                                                  TEMPLATE_PROJECTION_MATRIX.far_plane);

    // Main loop
    GPS_LOOP(GPS_SDL_EVENT);
}