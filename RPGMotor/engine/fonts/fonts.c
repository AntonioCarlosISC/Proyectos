#include "fonts.h"
#include <stdio.h>
#include <stdlib.h>

Font* font_load(const char* path, int size) {
    if (TTF_WasInit() == 0) {
        if (TTF_Init() == -1) {
            fprintf(stderr, "[ERROR] TTF_Init failed: %s\n", TTF_GetError());
            return NULL;
        }
    }

    TTF_Font* ttf = TTF_OpenFont(path, size);
    if (!ttf) {
        fprintf(stderr, "[ERROR] TTF_OpenFont failed (%s): %s\n", path, TTF_GetError());
        return NULL;
    }

    Font* f = malloc(sizeof(Font));
    if (!f) {
        TTF_CloseFont(ttf);
        fprintf(stderr, "[ERROR] No se pudo asignar memoria para la fuente\n");
        return NULL;
    }

    f->font = ttf;
    return f;
}

void font_free(Font* f) {
    if (!f) return;
    if (f->font) TTF_CloseFont(f->font);
    free(f);
}

SDL_Texture* font_render_text(SDL_Renderer* renderer, Font* f, const char* text, SDL_Color color) {
    if (!f || !f->font || !renderer || !text) return NULL;

    SDL_Surface* surface = TTF_RenderText_Solid(f->font, text, color);
    if (!surface) {
        fprintf(stderr, "[ERROR] TTF_RenderText_Solid failed: %s\n", TTF_GetError());
        return NULL;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!tex) {
        fprintf(stderr, "[ERROR] SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
        return NULL;
    }

    return tex;
}
