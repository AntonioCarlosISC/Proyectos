# --------------------------
# Makefile RPGMotor multiplataforma
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
SRC_DIR_APP = app
SRC_DIR_ENGINE = engine
SRC_DIR_TEST = test

# Carpeta de objetos y build
OBJ_DIR = obj
BUILD_DIR = build
BUILD_ASSETS = $(BUILD_DIR)/engine/fonts/static

# --------------------------
# Archivos fuente y objetos
# --------------------------
SRC = $(wildcard $(SRC_DIR_APP)/*.c) \
      $(wildcard $(SRC_DIR_ENGINE)/*.c) \
      $(wildcard $(SRC_DIR_ENGINE)/input/*.c) \
      $(wildcard $(SRC_DIR_ENGINE)/graphics/*.c) \
      $(wildcard $(SRC_DIR_ENGINE)/fonts/*.c) \
      $(wildcard $(SRC_DIR_TEST)/*.c)

OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

# Includes
INCLUDES = -Iengine -Iengine/input -Iengine/graphics -Iengine/fonts/fonts -Itest/test

# --------------------------
# Targets principales
# --------------------------
.PHONY: all clean dirs assets

all: dirs assets $(TARGET)

# --------------------------
# Linking
# --------------------------
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(SDLFLAGS) $(THREADFLAGS)

# --------------------------
# Compilación de objetos
# --------------------------
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Incluir dependencias de headers
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
	@rm -rf $(OBJ_DIR) $(BUILD_DIR)
