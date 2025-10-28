#include "input.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

extern bool running; // variable global compartida

void* input_thread(void* arg) {
    GraphicsContext* ctx = (GraphicsContext*)arg;
    char command[64];

    while (running) {
        printf("> ");
        if (fgets(command, sizeof(command), stdin)) {
            command[strcspn(command, "\n")] = 0;

            if (strcmp(command, "exit") == 0) {
                running = false;
            } else if (strcmp(command, "full") == 0) {
                printf("[INFO] Modo Pantalla Completa\n");
                graphics_set_fullscreen(ctx, true);
                graphics_set_bordered(ctx, false);
            } else if (strcmp(command, "window") == 0) {
                printf("[INFO] Modo Ventana\n");
                graphics_set_fullscreen(ctx, false);
                graphics_set_bordered(ctx, true);
                graphics_resize(ctx, 800, 600);
            } else if (strcmp(command, "bordered") == 0) {
                printf("[INFO] Modo Ventana sin Bordes\n");
                graphics_set_bordered(ctx, true);
            } else if (strncmp(command, "resize ", 7) == 0) {
                int w, h;
                if (sscanf(command + 7, "%d %d", &w, &h) == 2)
                {
                    printf("[INFO] Tamaño de Pantalla Establecido %d %d\n",w,h);
                    graphics_resize(ctx, w, h);
                }
            }
        }
    }

    return NULL;
}
