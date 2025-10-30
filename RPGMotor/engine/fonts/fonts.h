#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct {
    TTF_Font* font;
} Font;

/**
 * @brief Carga una fuente desde un archivo .ttf
 * 
 * @param path Ruta al archivo .ttf
 * @param size Tamaño de la fuente
 * @return Font* puntero a la fuente cargada, NULL en error
 */
Font* font_load(const char* path, int size);

/**
 * @brief Libera la memoria asociada a la fuente
 * 
 * @param f puntero a la fuente
 */
void font_free(Font* f);

/**
 * @brief Renderiza texto a una textura SDL
 * 
 * @param renderer SDL_Renderer donde se dibujará
 * @param f Fuente a usar
 * @param text Texto a renderizar
 * @param color Color del texto
 * @return SDL_Texture* textura creada, NULL en error
 */
SDL_Texture* font_render_text(SDL_Renderer* renderer, Font* f, const char* text, SDL_Color color);
