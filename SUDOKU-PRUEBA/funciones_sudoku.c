#include <stdio.h>


/*
Este archivo contiene distintas funciones utilizadas en tps pasados
para poder 'importar' y utilizarlo como si fuese un 'header' 
*/
#define MAX 9

typedef struct 
{
    int MATRIZ[MAX][MAX];
} tablero_t;

// Declaración de funciones
void inicio_tablero(tablero_t* tablero);
void mostrar_tablero(tablero_t *tablero);
int movimiento_valido(int num, tablero_t* tablero, int fila, int columna);
int esta_completo(tablero_t* tablero);
void guardar_tablero(tablero_t* tablero, char* nombre_archivo);
void cargar_tablero(tablero_t* tablero, char* nombre_archivo);
void menu_bienvenida();
void salir_del_programa();
int preguntar_seguir_jugando();
void jugar_sudoku(tablero_t* tablero, char* nombre_archivo);

int preguntar_seguir_jugando()
{
    int respuesta;
    printf("Quiere seguir jugando -> 1 para si, 0 para no: ");
    scanf("%d", &respuesta);
    return respuesta;
}


int es_random_valido(int numero, tablero_t* tablero, int fila, int columna) 
{
    int es_valido = 1;  // Se asume que el número es válido

    // Verificar si el número NO está en la fila
    for (int i = 0; i < MAX; i++) 
    {
        if (tablero->MATRIZ[fila][i] == numero) 
        {
            es_valido = 0;  // Número repetido en la fila
        }
    }

    // Verificar si el número NO está en la columna
    for (int i = 0; i < MAX; i++) 
    {
        if (tablero->MATRIZ[i][columna] == numero) 
        {
            es_valido = 0;  // Número repetido en la columna
        }
    }

    // Verificar si el número NO está en el cuadrante 3x3
    int inicio_fila = 3 * (fila / 3);
    int inicio_columna = 3 * (columna / 3);

    for (int i = inicio_fila; i < inicio_fila + 3; i++) 
    {
        for (int j = inicio_columna; j < inicio_columna + 3; j++) 
        {
            if (tablero->MATRIZ[i][j] == numero) 
            {
                es_valido = 0;  // Número repetido en el cuadrante 3x3
            }
        }
    }

    return es_valido;  // Devolver el resultado al final
}


//Se modifico INICIO TABLERO
void inicio_tablero(tablero_t* tablero) 
{
    srand(time(NULL));
    int numeros_restantes = 58;  // Cambia este valor al número deseado

    for (int i = 0; i < MAX; i++) 
    {
        for (int j = 0; j < MAX; j++) 
        {
            tablero->MATRIZ[i][j] = 0;
        }
    }

    while (numeros_restantes > 0) 
    {
        int fila = rand() % MAX;
        int columna = rand() % MAX;
        int numero = rand() % 9 + 1;  // Generar un número aleatorio del 1 al 9

        if (tablero->MATRIZ[fila][columna] == 0 && es_random_valido(numero, tablero, fila, columna)) 
        {
            tablero->MATRIZ[fila][columna] = numero;
            numeros_restantes--;
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

int movimiento_valido(int numero, tablero_t* tablero, int fila, int columna)
{
    int retorno = -1;
    // Verificar si la posición ya tiene un número diferente de cero
    if (tablero->MATRIZ[fila][columna] != 0)
    {
        retorno = 0;  // La posición ya está ocupada
    }
    else if (numero < 1 || numero > 9)
    {
        retorno = 0;
    }

    // Verificar si el número NO está en la fila
    for (int i = 0; i < MAX; i++)
    {
        if (i != columna && tablero->MATRIZ[fila][i] == numero)
        {
            retorno = 0;  // Número repetido en la fila
        }
    }

    // Verificar si el número NO está en la columna
    for (int i = 0; i < MAX; i++)
    {
        if (i != fila && tablero->MATRIZ[i][columna] == numero)
        {
            retorno = 0;  // Número repetido en la columna
        }
    }

    // Verificar si el número NO está en el cuadrante 3x3
    int inicio_fila = 3 * (fila / 3);
    int inicio_columna = 3 * (columna / 3);

    for (int i = inicio_fila; i < inicio_fila + 3; i++)
    {
        for (int j = inicio_columna; j < inicio_columna + 3; j++)
        {
            if (i != fila && j != columna && tablero->MATRIZ[i][j] == numero)
            {
                retorno = 0;  // Número repetido en el cuadrante 3x3
            }
        }
    }
    retorno = 1;

    return retorno;  // El número es válido
}

int esta_completo(tablero_t* tablero)
{
    int retorno = 2;
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (tablero->MATRIZ[i][j] == 0)
            {
                retorno = 0;  // Hay al menos una celda vacía
            }
        }
    }
    retorno = 1;
    return retorno;  // El tablero está completo
}


void guardar_tablero(tablero_t* tablero, char* nombre_archivo)
{
    FILE* archivo = fopen(nombre_archivo, "w");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo para guardar.\n");
    }

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
        salir_del_programa();
    }

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            fscanf(archivo, "%d", &tablero->MATRIZ[i][j]);
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
        salir_del_programa();
    }
    else
    {
        printf("Error con la opcion ingresada\n");
        salir_del_programa();
    }
}