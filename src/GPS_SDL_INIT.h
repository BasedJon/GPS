#pragma once

// INCLUDE STD
#include "STD3D.h"

// INCLUDE SDL3
#include <SDL3/SDL.h>

// SDL VARS
extern SDL_Event GPS_SDL_EVENT;
extern SDL_Window* GPS_SDL_WINDOW;
extern uint32_t GPS_SDL_WINDOW_HEIGHT;
extern uint32_t GPS_SDL_WINDOW_WIDTH;
extern const char* GPS_SDL_WINDOW_TITLE;
extern const bool* GPS_SDL_KEYSTATE;
extern std::vector<SDL_Window*> GPS_SDL_WINDOW_ARRAY;
extern SDL_Renderer* GPS_SDL_RENDERER;

// SDL
void GPS_SDL_clean_up();

void GPS_SDL_init();

void GPS_SDL_init_renderer();

void GPS_SDL_create_window(SDL_Window* &window, const char* title, uint32_t width, uint32_t height);

void GPS_SDL_get_vulkan_extensions(uint32_t* count, const char* const** extensions);