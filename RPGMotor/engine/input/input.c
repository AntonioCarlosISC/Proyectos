#include "../core.h"
#include "input.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void* input_thread(void* arg) {
    (void)arg; // no usamos directamente el contexto gráfico
    char command[64];

    printf("[INFO] Hilo de entrada iniciado correctamente.\n");

    while (running) {
        printf("> ");
        if (fgets(command, sizeof(command), stdin)) {
            command[strcspn(command, "\n")] = 0;

            if (strcmp(command, "exit") == 0) {
                pending_command.type = CMD_EXIT;
            } else if (strcmp(command, "full") == 0) {
                pending_command.type = CMD_FULLSCREEN;
            } else if (strcmp(command, "window") == 0) {
                pending_command.type = CMD_WINDOWED;
            } else if (strcmp(command, "bordered") == 0) {
                pending_command.type = CMD_BORDERED;
            } else if (strncmp(command, "resize ", 7) == 0) {
                int w, h;
                if (sscanf(command + 7, "%d %d", &w, &h) == 2) {
                    pending_command.type = CMD_RESIZE;
                    pending_command.w = w;
                    pending_command.h = h;
                }
            } else if (strcmp(command, "clear") == 0) {
                system("clear"); // Linux/macOS
            } else if (strlen(command) > 0) {
                printf("[WARN] Comando no reconocido: %s\n", command);
            }
        }
    }

    return NULL;
}
