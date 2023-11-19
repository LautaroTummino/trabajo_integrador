#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#include "funciones_sudoku.c"

#define MAX 9

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

void jugar_sudoku(tablero_t* tablero, char* nombre_archivo)
{
    int cuenta_movimientos = 1;
    int fila;
    int columna;
    int numero;
    int juego_completo = 0;
    char mensaje_fila[] = "Ingrese la fila (1-9): ";
    char mensaje_columna[] = "Ingrese la columna (1-9): ";
    char mensaje_numero[] = "Ingrese el numero (1-9): ";

    while (!juego_completo)
    {
        mostrar_tablero(tablero);
        fila = obtener_entrada_valida(mensaje_fila);
        columna = obtener_entrada_valida(mensaje_columna);
        numero = obtener_entrada_valida(mensaje_numero);
        // Verificar si el movimiento es válido
        if (fila >= 1 && fila <= 9 && columna >= 1 && columna <= 9 && numero >= 1 && numero <= 9)
        {
            if (movimiento_valido(numero, tablero, fila - 1, columna - 1))
            {
                // Actualizar el tablero
                tablero->MATRIZ[fila - 1][columna - 1] = numero;
                guardar_tablero(tablero, nombre_archivo);
                cuenta_movimientos ++;
                // Verificar si el juego está completo
                juego_completo = esta_completo(tablero);

                if (juego_completo)
                {
                    mostrar_tablero(tablero);
                    printf("Felicidades Has completado el Sudoku.\n");
                    printf("La cantidad de movimientos fueron: %d \n", cuenta_movimientos);

                    // Preguntar si desea seguir jugando
                    int seguir_jugando = preguntar_seguir_jugando();

                    if (!seguir_jugando)
                    {
                        guardar_tablero(tablero, nombre_archivo);
                        return;
                    }
                    else
                    {
                        // Seguir jugando, reiniciar el tablero
                        inicio_tablero(tablero);
                        juego_completo = 0;  // Reiniciar el estado del juego           
                    }
                }
                else
                {
                    // Preguntar si desea seguir jugando después de ingresar un número
                    mostrar_tablero(tablero);
                    int seguir_ingresando = preguntar_seguir_jugando();

                    if (!seguir_ingresando)
                    {
                        // No seguir ingresando, salir del bucle
                        return;
                    }
                }
            } 
            else
            {
                printf("Numero no valido en esa posicion. Intentalo de nuevo.\n");
            }
        }
        else
        {
            printf("Entrada no valida. Asegurate de ingresar numeros entre 1 y 9.\n");
        }
    }
}


int main() 
{
    int opcion;
    char nombre_archivo[] = "sudoku_guardado.txt";
    tablero_t sudoku;

    logo_sudoku();
    menu_bienvenida();

    
    printf("Ingrese su opcion: ");
    scanf("%d", &opcion);

    corrobora_opcion(opcion, &sudoku, nombre_archivo);

    return 0;
}
