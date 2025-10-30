# --------------------------
# Makefile definitivo RPGMotor
# --------------------------

# --------------------------
# Variables generales
# --------------------------
CC = gcc
CFLAGS = -std=c99 -Wall -O2
THREADFLAGS = -pthread

# SDL2
SDLFLAGS_LINUX = `sdl2-config --cflags --libs` -lSDL2_ttf
SDLFLAGS_WINDOWS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

# Carpetas fuente
SRC_DIR_APP = app
SRC_DIR_ENGINE = engine
SRC_DIR_TEST = test

# Carpetas objeto
OBJ_DIR = obj
OBJ_DIR_APP = $(OBJ_DIR)/app
OBJ_DIR_ENGINE = $(OBJ_DIR)/engine
OBJ_DIR_TEST = $(OBJ_DIR)/test

# Carpeta de build final
BUILD_DIR = build
BUILD_ASSETS = $(BUILD_DIR)/engine/fonts/static

# Archivos fuente
SRC_APP = $(SRC_DIR_APP)/main.c $(SRC_DIR_APP)/game_loop.c
SRC_ENGINE = $(SRC_DIR_ENGINE)/core.c $(SRC_DIR_ENGINE)/input/input.c $(SRC_DIR_ENGINE)/graphics/graphics.c $(SRC_DIR_ENGINE)/graphics/draw.c $(SRC_DIR_ENGINE)/fonts/fonts.c
SRC_TEST = $(SRC_DIR_TEST)/test.c
SRC = $(SRC_APP) $(SRC_ENGINE) $(SRC_TEST)

# Archivos objeto
OBJ_APP = $(patsubst $(SRC_DIR_APP)/%.c, $(OBJ_DIR_APP)/%.o, $(SRC_APP))
OBJ_ENGINE = $(patsubst $(SRC_DIR_ENGINE)/%.c, $(OBJ_DIR_ENGINE)/%.o, $(SRC_ENGINE))
OBJ_TEST = $(patsubst $(SRC_DIR_TEST)/%.c, $(OBJ_DIR_TEST)/%.o, $(SRC_TEST))
OBJ = $(OBJ_APP) $(OBJ_ENGINE) $(OBJ_TEST)

# Ejecutables
TARGET_LINUX = $(BUILD_DIR)/rpg
TARGET_WINDOWS = $(BUILD_DIR)/rpg.exe

# Includes
INCLUDES = -Iengine -Iengine/input -Iengine/graphics -Iengine/fonts/fonts -Itest/test

# --------------------------
# Targets principales
# --------------------------
.PHONY: all clean linux windows dirs assets

all: linux

# --------------------------
# Linux
# --------------------------
linux: dirs assets $(TARGET_LINUX)

$(TARGET_LINUX): $(OBJ)
	$(CC) $(OBJ) -o $@ $(SDLFLAGS_LINUX) $(THREADFLAGS)

# --------------------------
# Windows (MinGW)
# --------------------------
windows: dirs assets $(TARGET_WINDOWS)

$(TARGET_WINDOWS): $(OBJ)
	$(CC) $(OBJ) -o $@ $(SDLFLAGS_WINDOWS)

# --------------------------
# Crear carpetas necesarias
# --------------------------
dirs:
	mkdir -p $(OBJ_DIR_APP) $(OBJ_DIR_ENGINE) $(OBJ_DIR_TEST)
	mkdir -p $(BUILD_DIR) $(BUILD_ASSETS)

# --------------------------
# Copiar assets al build
# --------------------------
assets:
	@echo "[INFO] Copiando assets al build..."
	@mkdir -p $(BUILD_ASSETS)
	@cp -r engine/fonts/static/* $(BUILD_ASSETS)/

# --------------------------
# Compilación de objetos
# --------------------------
$(OBJ_DIR_APP)/%.o: $(SRC_DIR_APP)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR_ENGINE)/%.o: $(SRC_DIR_ENGINE)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR_ENGINE)/input/%.o: $(SRC_DIR_ENGINE)/input/%.c
	mkdir -p $(OBJ_DIR_ENGINE)/input
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR_ENGINE)/graphics/%.o: $(SRC_DIR_ENGINE)/graphics/%.c
	mkdir -p $(OBJ_DIR_ENGINE)/graphics
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR_ENGINE)/fonts/%.o: $(SRC_DIR_ENGINE)/fonts/%.c
	mkdir -p $(OBJ_DIR_ENGINE)/fonts
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR_TEST)/%.o: $(SRC_DIR_TEST)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# --------------------------
# Limpiar compilados
# --------------------------
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)
