# --------------------------
# Makefile RPGMotor multiplataforma (dinámico)
# --------------------------

# --------------------------
# Variables generales
# --------------------------
CC = gcc
CFLAGS = -std=c99 -Wall -O2 -MMD -MP
THREADFLAGS = -pthread

# Detectar sistema operativo
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	SDLFLAGS = `sdl2-config --cflags --libs` -lSDL2_ttf
	TARGET = build/rpg
else ifeq ($(OS),Windows_NT)
	SDLFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
	TARGET = build/rpg.exe
else ifeq ($(UNAME_S),Darwin)
	SDLFLAGS = `sdl2-config --cflags --libs` -lSDL2_ttf
	TARGET = build/rpg
else
	$(error Sistema operativo no soportado)
endif

# Carpetas fuente
SRC_DIRS = app engine test

# Carpeta de objetos y build
OBJ_DIR = obj
BUILD_DIR = build
BUILD_ASSETS = $(BUILD_DIR)/engine/fonts/static

# Includes
INCLUDES = -Iengine -Iengine/input -Iengine/graphics -Iengine/fonts/fonts -Itest/test

# --------------------------
# Encontrar todos los .c automáticamente
# --------------------------
SRC = $(shell find $(SRC_DIRS) -name "*.c")
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

# --------------------------
# Targets principales
# --------------------------
.PHONY: all clean dirs assets linux windows

all: dirs assets $(TARGET)

# --------------------------
# Linking
# --------------------------
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(SDLFLAGS) $(THREADFLAGS)

# --------------------------
# Compilación de objetos (manteniendo estructura de carpetas)
# --------------------------
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# --------------------------
# Incluir dependencias de headers
# --------------------------
-include $(DEP)

# --------------------------
# Crear carpetas necesarias
# --------------------------
dirs:
	@mkdir -p $(OBJ_DIR) $(BUILD_DIR) $(BUILD_ASSETS)

# --------------------------
# Copiar assets al build
# --------------------------
assets:
	@echo "[INFO] Copiando assets al build..."
	@mkdir -p $(BUILD_ASSETS)
	@cp -r engine/fonts/static/* $(BUILD_ASSETS)/

# --------------------------
# Limpiar compilados
# --------------------------
clean:
	@echo "[INFO] Limpiando build y objetos..."
	@rm -rf $(OBJ_DIR) $(BUILD_DIR)

# --------------------------
# Linux/Windows targets explícitos
# --------------------------
linux: all
windows: all
