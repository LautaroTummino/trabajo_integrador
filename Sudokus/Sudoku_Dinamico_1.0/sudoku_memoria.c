#include<stdio.h>
#include <stdlib.h>
#include "funciones_memoria.c"
#define MAX 9


/**
 * En esta funcion es donde transcurre todo el codigo para poder jugar al Sudoku.
 *
 * @param tablero Puntero al tablero de Sudoku.
 * @param nombre_archivo Nombre del archivo para guardar la partida.
 * @return
 *
 * La función permite al usuario jugar al Sudoku, ingresando filas, columnas y numeros.
 * Verifica la validez de los movimientos con la función `movimiento_valido`, para luego proceder a guardar la partida/tablero en un archivo txt,
 * pregunta al usuario si desea seguir jugando despues de cada movimiento.
 * El juego continúa hasta que se completa el tablero o el usuario decide salir.
 */
void jugar_sudoku(tablero_t* tablero, char* nombre_archivo)
{
    int cuenta_movimientos = 1;
    int fila;
    int columna;
    int numero;
    int juego_completo = 0;
    int seguir_jugando;

    char mensaje_fila[] = "Ingrese la fila (1-9): ";
    char mensaje_columna[] = "Ingrese la columna (1-9): ";
    char mensaje_numero[] = "Ingrese el numero (1-9): ";

    do
    {
        mostrar_tablero(tablero);
        fila = obtener_entrada_valida(mensaje_fila);
        columna = obtener_entrada_valida(mensaje_columna);
        numero = obtener_entrada_valida(mensaje_numero);

        // Validar movimiento utilizando la nueva función
        if (movimiento_valido(tablero, fila, columna, numero))
        {
            // Actualizar el tablero
            tablero->MATRIZ[fila - 1][columna - 1] = numero;
            guardar_tablero(tablero, nombre_archivo);
            cuenta_movimientos++;

            // Verificar si el juego está completo utilizando la nueva función
            juego_completo = esta_completo(tablero);

            // Preguntar si quiere seguir jugando
            seguir_jugando = preguntar_seguir_jugando();
            if (!seguir_jugando)
            {
                salir_del_programa();
            }
        }
        else
        {
            printf("Movimiento no valido. Por favor, ingresa valores validos.\n");

            // Preguntar si quiere seguir jugando después de un movimiento incorrecto
            seguir_jugando = preguntar_seguir_jugando();
            if (!seguir_jugando)
            {
                salir_del_programa();
            }

        }

    } while (!juego_completo);

    //Mensaje Final
    printf("Felicitaciones completaste el Sudoku de Commit & Conquer en %d movimientos.\n", cuenta_movimientos);
    liberar_tablero(tablero);
    
}


int main() 
{
    int opcion;
    char nombre_archivo[] = "sudoku_guardado.txt";
    tablero_t sudoku;
    inicializar_tablero(&sudoku);
    logo_sudoku();
    menu_bienvenida();
    printf("Ingrese su opcion: ");
    scanf("%d", &opcion);
    corrobora_opcion(opcion, &sudoku, nombre_archivo);
    liberar_tablero(&sudoku);
    return 0;
}

