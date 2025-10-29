#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} GraphicsContext;

GraphicsContext* graphics_init(const char* display);
void graphics_shutdown(GraphicsContext* ctx);
void graphics_render(GraphicsContext* ctx);
void graphics_set_fullscreen(GraphicsContext* ctx, bool fullscreen);
void graphics_set_bordered(GraphicsContext* ctx, bool bordered);
void graphics_resize(GraphicsContext* ctx, int width, int height);
