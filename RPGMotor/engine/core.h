#pragma once
#include <stdbool.h>

// Ruta base relativa de tus recursos (para referencia)
#define ASSETS_PATH "engine/fonts/static/"

// Estado global del motor
extern bool running;
extern bool show_fps;

// Tipos de comandos posibles
typedef enum {
    CMD_NONE,
    CMD_EXIT,
    CMD_FULLSCREEN,
    CMD_WINDOWED,
    CMD_BORDERED,
    CMD_RESIZE,
    CMD_SHOW_FPS
} EngineCommandType;

// Estructura para comandos pendientes
typedef struct {
    EngineCommandType type;
    int w, h;
} EngineCommand;

// Comando actual compartido entre hilos
extern EngineCommand pending_command;

// Inicializa el núcleo (establece rutas, etc.)
void core_init(void);

// Devuelve una ruta absoluta hacia un recurso del motor
const char* get_resource_path(const char* relative);

// Finaliza el núcleo y libera recursos si es necesario
void core_shutdown(void);
