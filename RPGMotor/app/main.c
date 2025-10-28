//#region Encabezados
#include <stdio.h>
//#endregion

//#region Enlazados
    int game_loop(void);
//#endregion

// #region Función principal
int main(int argc, char* argv[])
{
    printf("Compilación correcta\n");
    if(argc > 1 && argv[1] != NULL)
    {
        printf("Argumento pasado: %s\n",argv[1]);
    }
    return game_loop();
}
//#endregion