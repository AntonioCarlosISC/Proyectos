#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include "../fonts/fonts.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Font* main_font;
    bool show_fps;
} GraphicsContext;

GraphicsContext* graphics_init(const char* display);
void graphics_shutdown(GraphicsContext* ctx);
void graphics_render(GraphicsContext* ctx);
void graphics_set_fullscreen(GraphicsContext* ctx, bool fullscreen);
void graphics_set_bordered(GraphicsContext* ctx, bool bordered);
void graphics_resize(GraphicsContext* ctx, int width, int height);
