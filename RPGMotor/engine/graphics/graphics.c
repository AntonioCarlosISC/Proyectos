#include "graphics.h"
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include "../core.h"

GraphicsContext* graphics_init(const char* display) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        fprintf(stderr, "[ERROR] SDL_Init failed: %s\n", SDL_GetError());
        return NULL;
    }

    if (TTF_Init() != 0) {
        fprintf(stderr, "[ERROR] TTF_Init failed: %s\n", TTF_GetError());
        SDL_Quit();
        return NULL;
    }

    Uint32 window_flags = SDL_WINDOW_SHOWN;
    bool remove_borders = false;

    if (display) {
        if (strcmp(display, "full") == 0) {
            window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
            remove_borders = true;
        }
    }

    SDL_Window* window = SDL_CreateWindow(
        "RPG Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        window_flags
    );

    if (!window) {
        fprintf(stderr, "[ERROR] SDL_CreateWindow failed: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return NULL;
    }

    if (remove_borders) SDL_SetWindowBordered(window, SDL_FALSE);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "[ERROR] SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return NULL;
    }

    GraphicsContext* ctx = malloc(sizeof(GraphicsContext));
    ctx->window = window;
    ctx->renderer = renderer;

    // Inicializar la fuente principal del motor
const char* font_path = get_resource_path("fonts/static/OpenSans_Condensed-Bold.ttf");
ctx->main_font = font_load(font_path, 16);
if (!ctx->main_font) {
    fprintf(stderr, "[ERROR] No se pudo cargar la fuente principal\n");
    graphics_shutdown(ctx);
    return NULL;
} else {
        printf("[INFO] Fuente cargada correctamente desde: %s\n", font_path);
    }

    return ctx;
}

void graphics_shutdown(GraphicsContext* ctx) {
    if (!ctx) return;
    if (ctx->main_font) font_free(ctx->main_font);
    SDL_DestroyRenderer(ctx->renderer);
    SDL_DestroyWindow(ctx->window);
    TTF_Quit();
    SDL_Quit();
    free(ctx);
}

void graphics_render(GraphicsContext* ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctx->renderer);
    SDL_RenderPresent(ctx->renderer);
}

void graphics_set_fullscreen(GraphicsContext* ctx, bool fullscreen) {
    SDL_SetWindowFullscreen(ctx->window, fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

void graphics_set_bordered(GraphicsContext* ctx, bool bordered) {
    SDL_SetWindowBordered(ctx->window, bordered ? SDL_TRUE : SDL_FALSE);
}

void graphics_resize(GraphicsContext* ctx, int w, int h) {
    SDL_SetWindowSize(ctx->window, w, h);
}
