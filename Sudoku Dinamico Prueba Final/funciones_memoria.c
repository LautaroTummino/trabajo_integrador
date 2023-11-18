#include <stdio.h>
#include <stdlib.h>


/*
Este archivo contiene distintas funciones utilizadas en tps pasados
para poder 'importar' y utilizarlo como si fuese un 'header' 
*/
#define MAX 9



typedef struct 
{
    int** MATRIZ;
    int** TABLERO_COMPLETO;
} tablero_t;


// Declaración de funciones
void jugar_sudoku(tablero_t* tablero, char* nombre_archivo);
int movimiento_valido(tablero_t* tablero, int fila, int columna, int numero);
int obtener_entrada_valida(char mensaje[]);
int preguntar_seguir_jugando();
void inicio_tablero(tablero_t* tablero);
void mostrar_tablero(tablero_t *tablero);
int esta_completo(tablero_t* tablero);
void guardar_tablero(tablero_t* tablero, char* nombre_archivo);
void cargar_tablero(tablero_t* tablero, char* nombre_archivo);
void menu_bienvenida();
void salir_del_programa();
void logo_sudoku();





int movimiento_valido(tablero_t* tablero, int fila, int columna, int numero) 
{
    int es_movimiento_valido = 1;
    // Verificar límites de fila y columna
    if (fila < 1 || fila > MAX || columna < 1 || columna > MAX)
    {
        es_movimiento_valido = 0;  // Movimiento no válido, fila o columna fuera de rango
    }

    // Verificar si la celda está ocupada
    if (tablero->MATRIZ[fila - 1][columna - 1] != 0)
    {
        es_movimiento_valido = 0;  // Movimiento no válido, la celda ya está ocupada
    }

    // Verificar si el número es válido según el tablero completo
    if (tablero->TABLERO_COMPLETO[fila - 1][columna - 1] != numero)
    {
        es_movimiento_valido = 0;  // Movimiento no válido, el número no coincide con el tablero completo
    }
    return es_movimiento_valido;  // Movimiento válido
}


int obtener_entrada_valida(char mensaje[])
{
    int entrada;
    while (1)
    {
        printf("%s", mensaje);
        if (scanf("%d", &entrada) == 1 && entrada >= 1 && entrada <= 9)
        {
            // Entrada válida
            return entrada;
        }
        else
        {
            printf("Entrada no valida. Asegurate de ingresar un numero entre 1 y 9.\n");
            // Limpiar el búfer de entrada para evitar un bucle infinito
            while (getchar() != '\n');
        }
    }
}

int preguntar_seguir_jugando()
{
    int respuesta;
    printf("Seguir Jugando: Si-(1) | No-(0)");
    scanf("%d", &respuesta);
    return respuesta;
}

void inicializar_tablero(tablero_t* tablero) 
{
    tablero->MATRIZ = (int**)malloc(MAX * sizeof(int*));
    tablero->TABLERO_COMPLETO = (int**)malloc(MAX * sizeof(int*));

    for (int i = 0; i < MAX; i++) 
    {
        tablero->MATRIZ[i] = (int*)malloc(MAX * sizeof(int));
        tablero->TABLERO_COMPLETO[i] = (int*)malloc(MAX * sizeof(int));
    }
}

void liberar_tablero(tablero_t* tablero) 
{
    for (int i = 0; i < MAX; i++) 
    {
        free(tablero->MATRIZ[i]);
        free(tablero->TABLERO_COMPLETO[i]);
    }

    free(tablero->MATRIZ);
    free(tablero->TABLERO_COMPLETO);
}

void inicio_tablero(tablero_t* tablero) 
{
    int tablero_inicial[MAX][MAX] =
     {
        {0, 5, 0, 1, 0, 4, 6, 0, 2},
        {0, 6, 8, 0, 7, 0, 0, 0, 5},
        {0, 0, 2, 0, 0, 0, 9, 0, 0},
        {0, 0, 0, 0, 0, 5, 0, 0, 9},
        {0, 0, 0, 0, 8, 0, 0, 0, 0},
        {7, 0, 0, 9, 0, 0, 0, 0, 0},
        {0, 0, 3, 0, 0, 0, 2, 0, 0},
        {8, 0, 0, 0, 1, 0, 4, 9, 0},
        {6, 0, 1, 2, 0, 7, 0, 5, 0}
    };

    int tablero_completo[MAX][MAX] =
    {
        {3, 5, 7, 1, 9, 4, 6, 8, 2},
        {9, 6, 8, 3, 7, 2, 1, 4, 5},
        {1, 4, 2, 5, 6, 8, 9, 7, 3},
        {2, 1, 4, 7, 3, 5, 8, 6, 9},
        {5, 3, 9, 4, 8, 6, 7, 2, 1},
        {7, 8, 6, 9, 2, 1, 5, 3, 4},
        {4, 7, 3, 8, 5, 9, 2, 1, 6},
        {8, 2, 5, 6, 1, 3, 4, 9, 7},
        {6, 9, 1, 2, 4, 7, 3, 5, 8}
    };

    // Copiar las configuraciones al tablero
    for (int i = 0; i < MAX; i++) 
    {
        for (int j = 0; j < MAX; j++) 
        {
            tablero->MATRIZ[i][j] = tablero_inicial[i][j];
            tablero->TABLERO_COMPLETO[i][j] = tablero_completo[i][j];
        }
    }
}

void mostrar_tablero(tablero_t *tablero)
{
    printf(" ------------------------------\n");
    for (int i = 0; i < MAX; ++i)
    {
        if (i % 3 == 0 && i != 0)
        {
            printf(" ------------------------------\n");
        }
        for (int j = 0; j < MAX; ++j)
        {
            if (j % 3 == 0)
            {
                printf("|");
            }
            printf("%2d ", tablero->MATRIZ[i][j]);
        }
        printf("|\n");
    }
    printf(" ------------------------------\n");
}



int esta_completo(tablero_t* tablero)
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (tablero->MATRIZ[i][j] == 0)
            {
                return 0;  // Hay al menos una celda vacía
            }
        }
    }

    return 1;  // El tablero está completo
}



void guardar_tablero(tablero_t* tablero, char* nombre_archivo)
{
    FILE* archivo = fopen(nombre_archivo, "w");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo para guardar.\n");
        return;
    }

    // Guardar el tablero en juego
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            fprintf(archivo, "%d ", tablero->MATRIZ[i][j]);
        }
        fprintf(archivo, "\n");
    }


    fclose(archivo);
}

void cargar_tablero(tablero_t* tablero, char* nombre_archivo)
{
    FILE* archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo para cargar.\n");
        printf("Ya que no existe una partida previa.\n");
        salir_del_programa(tablero);
        return;
    }

    // Primero, cargar el tablero en juego
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            fscanf(archivo, "%d", &tablero->MATRIZ[i][j]);
        }
    }

    //Guardo el tablero ya que si cargo la partida algo deja de funcionar
    int tablero_completo[MAX][MAX] =
    {
        {3, 5, 7, 1, 9, 4, 6, 8, 2},
        {9, 6, 8, 3, 7, 2, 1, 4, 5},
        {1, 4, 2, 5, 6, 8, 9, 7, 3},
        {2, 1, 4, 7, 3, 5, 8, 6, 9},
        {5, 3, 9, 4, 8, 6, 7, 2, 1},
        {7, 8, 6, 9, 2, 1, 5, 3, 4},
        {4, 7, 3, 8, 5, 9, 2, 1, 6},
        {8, 2, 5, 6, 1, 3, 4, 9, 7},
        {6, 9, 1, 2, 4, 7, 3, 5, 8}
    };

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            tablero->TABLERO_COMPLETO[i][j] = tablero_completo[i][j];
        }
    }

    fclose(archivo);
}


void menu_bienvenida()
{
    printf("|Bienvenido al Sudoku de Commit & Conquer|\n");
    printf("|Por favor, elige una opcion|\n");
    printf("|1) Comenzar Juego|\n");
    printf("|2) Cargar partida|\n");
    printf("|3) Salir|\n");
}

void salir_del_programa()
{
    printf("Gracias por jugar. Hasta luego.\n");
    exit(0);
}


void corrobora_opcion(int opcion, tablero_t* tablero, char* nombre_archivo)
{
    if (opcion == 1)
    {
        inicio_tablero(tablero);
        jugar_sudoku(tablero, nombre_archivo);
    }
    else if(opcion == 2)
    {
        cargar_tablero(tablero, nombre_archivo);
        jugar_sudoku(tablero, nombre_archivo);
    }
    else if (opcion == 3)
    {
        salir_del_programa(tablero);
    }
    else
    {
        printf("Error con la opcion ingresada\n");
        salir_del_programa(tablero);
    }      
}

void logo_sudoku()
{
    
    printf("                                           ,----..          ,--.               \n");
    printf("  .--.--.                     ,---,       /   /   \\     ,--/  /|               \n");
    printf(" /  /    '.          ,--,   .'  .' `\\    /   .     : ,---,': / '         ,--,  \n");
    printf("|  :  /`. /        ,'_ /| ,---.'     \\  .   /   ;.  \\:   : '/ /        ,'_ /|  \n");
    printf(";  |  |--`    .--. |  | : |   |  .`\\  |.   ;   /  ` ;|   '   ,    .--. |  | :  \n");
    printf("|  :  ;_    ,'_ /| :  . | :   : |  '  |;   |  ; \\ ; |'   |  /   ,'_ /| :  . |  \n");
    printf(" \\  \\    `. |  ' | |  . . |   ' '  ;  :|   :  | ; | '|   ;  ;   |  ' | |  . .  \n");
    printf("  `----.   \\|  | ' |  | | '   | ;  .  |.   |  ' ' ' ::   '   \\  |  | ' |  | |  \n");
    printf("  __ \\  \\  |:  | | :  ' ; |   | :  |  ''   ;  \\; /  ||   |    ' :  | | :  ' ;  \n");
    printf(" /  /`--'  /|  ; ' |  | ' '   : | /  ;  \\   \\  ',  / '   : |.  \\|  ; ' |  | '  \n");
    printf("'--'.     / :  | : ;  ; | |   | '` ,/    ;   :    /  |   | '_\\.':  | : ;  ; |  \n");
    printf("  `--'---'  '  :  `--'   \\;   :  .'       \\   \\ .'   '   : |    '  :  `--'   \\ \n");
    printf("            :  ,      .-./|   ,.'          `---`     ;   |,'    :  ,      .-./ \n");
    printf("             `--`----'    '---'                      '---'       `--`----'     \n");
    printf("\t \t                                           by Commit_&_Conquer");
    printf("\n\n");
}
