#include "test.h"
#include <SDL2/SDL.h>
#include <stdio.h>

void test_rgb(TEST* test, SDL_Renderer* renderer) {
    // Por ejemplo, dibujamos 16 rectángulos con colores primarios
    SDL_Rect rect = { 50, 50, 50, 50 };
    Uint8 colors[16][3] = {
        {255,0,0}, {0,255,0}, {0,0,255}, {255,255,0},
        {0,255,255}, {255,0,255}, {192,192,192}, {128,128,128},
        {128,0,0}, {0,128,0}, {0,0,128}, {128,128,0},
        {0,128,128}, {128,0,128}, {255,128,0}, {0,255,128}
    };

    for(int i = 0; i < 16; ++i) {
        SDL_SetRenderDrawColor(renderer, colors[i][0], colors[i][1], colors[i][2], 255);
        rect.x = 50 + (i % 4) * 60;
        rect.y = 50 + (i / 4) * 60;
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer); // Mostrar inmediatamente
    printf("[INFO] Test RGB Complete");
}
