#include <pthread.h>
#include "../engine/input/input.h"

bool running = true;

int game_loop(char* display) {
    GraphicsContext* ctx = graphics_init(display);
    if (!ctx) return 1;

    pthread_t tid;
    pthread_create(&tid, NULL, input_thread, ctx);

    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }
        graphics_render(ctx);
        SDL_Delay(10);
    }

    pthread_join(tid, NULL);
    graphics_shutdown(ctx);
    return 0;
}
