#define _POSIX_C_SOURCE 200809L

#include <unistd.h>
#include "core.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

#ifdef _WIN32
    #include <windows.h>
#elif __APPLE__
    #include <mach-o/dyld.h>
    #include <libgen.h>
#else
    #include <libgen.h>
#endif

// Variables globales
bool running = true;
bool show_fps = false;
EngineCommand pending_command = { CMD_NONE, 0, 0 };

// Ruta base de recursos
static char resource_base_path[PATH_MAX];
static char temp_path[PATH_MAX]; // para combinaciones temporales

void core_init(void) {
    char exe_path[PATH_MAX];
    memset(resource_base_path, 0, sizeof(resource_base_path));

#ifdef _WIN32
    // 📦 Windows
    GetModuleFileNameA(NULL, exe_path, sizeof(exe_path));
    char* last_slash = strrchr(exe_path, '\\');
    if (last_slash) *last_slash = '\0';
    snprintf(resource_base_path, sizeof(resource_base_path), "%s\\..\\engine\\", exe_path);

#elif __APPLE__
    // 🍏 macOS
    uint32_t size = sizeof(exe_path);
    if (_NSGetExecutablePath(exe_path, &size) == 0) {
        char* dir = dirname(exe_path);
        snprintf(resource_base_path, sizeof(resource_base_path), "%s/../engine/", dir);
    } else {
        getcwd(resource_base_path, sizeof(resource_base_path));
    }

#else
    // 🐧 Linux y otros UNIX
    ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
    if (len != -1) {
        exe_path[len] = '\0';
        char* dir = dirname(exe_path);
        snprintf(resource_base_path, sizeof(resource_base_path), "%s/../engine/", dir);
    } else {
        getcwd(resource_base_path, sizeof(resource_base_path));
    }
#endif

    printf("[CORE] Ruta base de recursos: %s\n", resource_base_path);
}

const char* get_resource_path(const char* relative) {
#ifdef _WIN32
    snprintf(temp_path, sizeof(temp_path), "%s%s", resource_base_path, relative);
#else
    snprintf(temp_path, sizeof(temp_path), "%s%s", resource_base_path, relative);
#endif
    return temp_path;
}

void core_shutdown(void) {
    // Futuras limpiezas globales
}
