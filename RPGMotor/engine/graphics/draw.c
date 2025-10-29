#include "draw.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include "../../test/test.h"

void draw_init(FrameTimer* timer)
{
    timer->last_time = SDL_GetPerformanceCounter();
    timer->delta_time = 0.0;
    timer->fps = 0.0;
}

void draw_update_timer(FrameTimer* timer)
{
    Uint64 current_time = SDL_GetPerformanceCounter();
    Uint64 freq = SDL_GetPerformanceFrequency();

    timer->delta_time = (double)(current_time - timer->last_time) / (double)freq;
    timer->last_time = current_time;
    timer->fps = (timer->delta_time > 0) ? (1.0 / timer->delta_time) : 0.0;
}

void draw_frame(GraphicsContext* ctx, FrameTimer* timer)
{
    // Limpieza del frame anterior
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctx->renderer);

    // Aquí puedes dibujar tus entidades, UI, sprites, etc.
    //Prueba de colores al inicializar, así como resolución
    // 🔹 Test de colores
    static int initialized = 0;
    static TEST test;
    if(!initialized) {
        test_rgb(&test, ctx->renderer);
        SDL_Delay(3000);
        initialized = 1;
    }
    // Por ahora, un ejemplo visual simple:
    SDL_SetRenderDrawColor(ctx->renderer, 255, 255, 0, 255);
    SDL_Rect rect = { 200, 200, 100, 100 };
    SDL_RenderFillRect(ctx->renderer, &rect);

    SDL_RenderPresent(ctx->renderer);

    // Mostrar FPS en consola (opcional para debug)
    //printf("\rFPS: %.1f", timer->fps);
    fflush(stdout);
}

void draw_sync(FrameTimer* timer, double target_fps)
{
    if (target_fps <= 0) return;
    double frame_time = 1.0 / target_fps;
    double delay = frame_time - timer->delta_time;

    if (delay > 0)
        SDL_Delay((Uint32)(delay * 1000.0));
}
