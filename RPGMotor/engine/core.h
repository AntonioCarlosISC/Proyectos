#pragma once
#include <stdbool.h>

// Estado global del motor
extern bool running;

// Tipos de comandos posibles
typedef enum {
    CMD_NONE,
    CMD_EXIT,
    CMD_FULLSCREEN,
    CMD_WINDOWED,
    CMD_BORDERED,
    CMD_RESIZE
} EngineCommandType;

// Estructura para comandos pendientes
typedef struct {
    EngineCommandType type;
    int w, h;
} EngineCommand;

// Comando actual compartido entre hilos
extern EngineCommand pending_command;
