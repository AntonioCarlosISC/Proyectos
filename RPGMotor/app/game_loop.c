//#region Encabezados
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <pthread.h>
//#endregion

//#region Prototipos
int game_loop(void);
//#endregion

//#region Variables globales para control de bucle
static bool running = true;
//#endregion

//#region Función de hilo para leer comandos
void* input_thread(void* arg)
{
    SDL_Window* window = ((SDL_Window**)arg)[0]; // recibir ventana por argumento
    char command[64];

    while (running)
    {
        printf("> ");
        if (fgets(command, sizeof(command), stdin))
        {
            command[strcspn(command, "\n")] = 0; // eliminar salto de línea

            if (strcmp(command, "exit") == 0)
            {
                printf("[INFO] Saliendo del bucle...\n");
                running = false;
            }
            else if (strcmp(command, "full") == 0)
            {
                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                SDL_SetWindowBordered(window, SDL_FALSE);
                printf("[INFO] Modo fullscreen activado.\n");
            }
            else if (strcmp(command, "window") == 0)
            {
                SDL_SetWindowFullscreen(window, 0); // modo ventana
                SDL_SetWindowBordered(window, SDL_TRUE);
                SDL_SetWindowSize(window, 800, 600);
                printf("[INFO] Modo ventana activado.\n");
            }
            else if (strcmp(command, "bordered") == 0)
            {
                SDL_SetWindowBordered(window, SDL_TRUE);
                printf("[INFO] Ventana con borde activada.\n");
            }
            else if (strncmp(command, "resize ", 7) == 0)
            {
                int w, h;
                if (sscanf(command + 7, "%d %d", &w, &h) == 2)
                {
                    SDL_SetWindowSize(window, w, h);
                    printf("[INFO] Ventana redimensionada a %dx%d.\n", w, h);
                }
                else
                {
                    printf("[ERROR] Formato incorrecto. Uso: resize WIDTH HEIGHT\n");
                }
            }
            else if (strlen(command) > 0)
            {
                printf("[CMD] Comando no reconocido: '%s'\n", command);
            }
        }
    }
    return NULL;
}

//#endregion

//#region Función game_loop
int game_loop(void)
{
    printf("[INFO] Iniciando bucle de juego...\n");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        fprintf(stderr, "[ERROR] No se pudo inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "RPG Engine Loop",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    if (!window)
    {
        fprintf(stderr, "[ERROR] No se pudo crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        fprintf(stderr, "[ERROR] No se pudo crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Crear hilo para comandos de terminal
    pthread_t tid;
    SDL_Window* args[] = {window};
    pthread_create(&tid, NULL, input_thread, args);

    SDL_Event event;

    // Bucle principal SDL
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        // Render básico
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        // Pequeña pausa para no saturar CPU
        SDL_Delay(10);
    }

    // Esperar que el hilo termine
    pthread_join(tid, NULL);

    // Limpieza
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("[INFO] Bucle de juego finalizado.\n");
    return 0;
}
//#endregion
