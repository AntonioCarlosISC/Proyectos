#include "draw.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include "../../test/test.h"
#include <SDL2/SDL_ttf.h>

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

    // 🔹 Test de colores inicial
    static int initialized = 0;
    static TEST test;
    if (!initialized) {
        test_rgb(&test, ctx->renderer);
        SDL_Delay(3000);
        initialized = 1;
    }

    // Cuadro amarillo de ejemplo
    SDL_SetRenderDrawColor(ctx->renderer, 255, 255, 0, 255);
    SDL_Rect rect = { 200, 200, 100, 100 };
    SDL_RenderFillRect(ctx->renderer, &rect);

    // 🔹 Mostrar FPS en pantalla
if (ctx->show_fps) {
    char buf[32];
    snprintf(buf, sizeof(buf), "FPS: %.1f", timer->fps);
    SDL_Color color = {255, 255, 255, 255};
    SDL_Texture* tex = font_render_text(ctx->renderer, ctx->main_font, buf, color);
    if (tex) {
        int w, h;
        SDL_QueryTexture(tex, NULL, NULL, &w, &h);
        SDL_Rect dst = {10, 10, w, h};
        SDL_RenderCopy(ctx->renderer, tex, NULL, &dst);
        SDL_DestroyTexture(tex);
    }
}


    SDL_RenderPresent(ctx->renderer);
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
