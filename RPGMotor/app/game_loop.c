#include "../engine/core.h"
#include "../engine/input/input.h"
#include "../engine/graphics/graphics.h"
#include "../engine/graphics/draw.h"
#include <pthread.h>
#include <SDL2/SDL.h>
#include <stdio.h>

int game_loop(char* display) {
    GraphicsContext* ctx = graphics_init(display);
    if (!ctx) return 1;

    FrameTimer timer;
    draw_init(&timer);

    pthread_t tid;
    pthread_create(&tid, NULL, input_thread, NULL);

    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        // 🔧 Procesar comando pendiente
        switch (pending_command.type) {
            case CMD_EXIT:
                running = false;
                break;
            case CMD_FULLSCREEN:
                graphics_set_fullscreen(ctx, true);
                graphics_set_bordered(ctx, false);
                printf("[INFO] Pantalla completa activada.\n");
                break;
            case CMD_WINDOWED:
                graphics_set_fullscreen(ctx, false);
                graphics_set_bordered(ctx, true);
                graphics_resize(ctx, 800, 600);
                printf("[INFO] Modo ventana.\n");
                break;
            case CMD_BORDERED:
                graphics_set_bordered(ctx, true);
                printf("[INFO] Bordes activados.\n");
                break;
            case CMD_RESIZE:
                graphics_resize(ctx, pending_command.w, pending_command.h);
                printf("[INFO] Resolución ajustada a %dx%d.\n", pending_command.w, pending_command.h);
                break;
            default:
                break;
        }

        // Resetear comando
        pending_command.type = CMD_NONE;

        // ✅ Renderizado correcto
        draw_update_timer(&timer);
        draw_frame(ctx, &timer);
        draw_sync(&timer, 60.0);
    }

    pthread_join(tid, NULL);
    graphics_shutdown(ctx);
    return 0;
}
