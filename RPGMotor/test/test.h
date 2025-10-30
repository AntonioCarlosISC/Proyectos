#pragma once
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>


typedef struct {
    Uint16 TEST_RGB;
} TEST;

void test_rgb(TEST* test_rgb, SDL_Renderer* renderer); // Pasamos renderer para dibujar
