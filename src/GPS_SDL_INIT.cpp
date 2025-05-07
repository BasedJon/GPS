// INCLUDE STD
#include "GPS_SDL_INIT.h"

// SDL VARS
SDL_Event GPS_SDL_EVENT;
SDL_Window* GPS_SDL_WINDOW;
uint32_t GPS_SDL_WINDOW_HEIGHT = 900;
uint32_t GPS_SDL_WINDOW_WIDTH = 1200;
const char* GPS_SDL_WINDOW_TITLE = "Black Leaf Engine";
const bool* GPS_SDL_KEYSTATE = SDL_GetKeyboardState(NULL);
std::vector<SDL_Window*> GPS_SDL_WINDOW_ARRAY;
SDL_Renderer* GPS_SDL_RENDERER;

// SDL
void GPS_SDL_clean_up() {
    SDL_DestroyRenderer(GPS_SDL_RENDERER);
    for (SDL_Window* window : GPS_SDL_WINDOW_ARRAY) {
        SDL_DestroyWindow(window);
    }
SDL_Quit();
}

void GPS_SDL_init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == false) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        GPS_SDL_clean_up();
    }
}

void GPS_SDL_init_renderer() {
    GPS_SDL_RENDERER = SDL_CreateRenderer(GPS_SDL_WINDOW, NULL);
    if (GPS_SDL_RENDERER == NULL) {
        std::cerr << "GPS_SDL_init_renderer failed: " << SDL_GetError() << std::endl;
        GPS_SDL_clean_up();
    }
}

void GPS_SDL_create_window(SDL_Window* &window, const char* title, uint32_t width, uint32_t height) {
    window = SDL_CreateWindow(title, width, height, 0);

    if (window == NULL) {
        std::cerr << "GPS_SDL_create_window failed: " << SDL_GetError() << std::endl;
        GPS_SDL_clean_up();
    }

    GPS_SDL_WINDOW_ARRAY.push_back(window);
}
