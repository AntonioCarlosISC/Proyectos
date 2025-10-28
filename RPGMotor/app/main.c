//#region Encabezados
#include <stdio.h>
#include <string.h>
//#endregion

//#region Prototipos
int game_loop(void);
//#endregion

//#region Función principal
int main(int argc, char* argv[])
{
    // Soporte para --version
    if (argc > 1 && argv[1] != NULL)
    {
        if (strcmp(argv[1], "--version") == 0)
        {
            printf("RPG Engine v0.1 - Build OK\n");
            return 0;
        }
        else
        {
            printf("Argumento pasado: %s\n", argv[1]);
        }
    }

    printf("Compilación correcta\n");

    // Ejecutar el bucle principal del motor
    return game_loop();
}
//#endregion
