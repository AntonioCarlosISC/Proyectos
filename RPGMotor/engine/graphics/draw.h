#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <stdbool.h>
#include "graphics.h"

//Aqui controlamos en renderizado y el framerate
typedef struct
{
    Uint64 last_time;
    double delta_time;
    double fps;
} FrameTimer;

//Inicializa el sistema de dibujado
void draw_init(FrameTimer* timer);

//Actualizamos el tiempo entre frames
void draw_update_timer(FrameTimer* timer);

//Renderizado de un frame completo
void draw_frame(GraphicsContext* ctx, FrameTimer* timer);

//Sincroniza el framerate de ser necesario
void draw_sync(FrameTimer* timer, double target_fps);
