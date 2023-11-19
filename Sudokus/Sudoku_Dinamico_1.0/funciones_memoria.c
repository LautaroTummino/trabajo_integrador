#include <stdio.h>
#include <stdlib.h>
#define MAX 9

/*
Este archivo contiene distintas funciones utilizadas en tps pasados como nuevas funciones
necesarias para poder hacer funcionar el sudoku.
'importamos' y utilizarlo como si fuese un 'header' 
*/


/*
Representa un tablero de Sudoku con matrices para el juego y la solución completa.
Estructura que contiene dos matrices dinamicas de enteros:
1er Miembro -> MATRIZ: Tablero de juego con celdas para números del 1 al 9 (0 para celdas vacías).
2do Miembro -> TABLERO_COMPLETO: Tablero completamente resuelto.
 */

typedef struct 
{
    int** MATRIZ;
    int** TABLERO_COMPLETO;
} tablero_t;


// Declaración de prototipos de todas las funciones del archivo
void jugar_sudoku(tablero_t* tablero, char* nombre_archivo);

int movimiento_valido(tablero_t* tablero, int fila, int columna, int numero);

int obtener_entrada_valida(char mensaje[]);

int preguntar_seguir_jugando();

void inicializar_tablero(tablero_t* tablero);

void liberar_tablero(tablero_t* tablero) ;

void inicio_tablero(tablero_t* tablero);

void mostrar_tablero(tablero_t *tablero);

int esta_completo(tablero_t* tablero);

void guardar_tablero(tablero_t* tablero, char* nombre_archivo);

void cargar_tablero(tablero_t* tablero, char* nombre_archivo);

void menu_bienvenida();

void salir_del_programa();

void corrobora_opcion(int opcion, tablero_t* tablero, char* nombre_archivo);

void logo_sudoku();



/**
 * Esta funcion se encarga de corroborar si el movimiento ingresado por el ususario
 * es un movimiento valido. utilizando el tablero_completo para corroborar el numero
 * y si las filas o columnas son mayores a 1 y menores a 9
 * como tambien corroborar si el lugar ingresado por el usuario ya cuenta con un numero
 *
 * @param tablero puntero a la matriz que representa donde transcurre el juego.
 * @param fila numero que representa la fila ingresada por el usuario
 * @param columna numero que representa la columna ingresada por el usuario
 * @param numero numero que representa el valor numerico ingresado por el usuario para la casilla del sudoku
 * @return numero entero que representa si el movimiento es valido (1) o si no lo es (0)
 * @pre Tablero debe ser una estructura valida 
 * @post Imprime la matriz completa, delimitando filas,columnas y matrices internas de 3x3
 */
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

/**
 * Esta funcion se encarga de solicitarle al usuario un numero válido entre 1 y 9
 *
 * @param mensaje Mensaje que indica al usuario que tipo de entrada se espera fila/columna/numero.
 * @return numero entero que representa la entrada valida del usuario en el rango de 1 a 9.
 * @pre
 * @post La función devuelve una entrada valida despues de solicitarla al usuario o le indica al mismo que su entrada no es valida
 * Si el usuario proporciona una entrada invalida, se muestra un mensaje de error y se vuelve a solicitar.
 */
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

/**
 * Esta funcion se encarga de preguntarle al usuario si desea seguir jugando.
 *
 * @param
 * @return valor numerico que representa la respuesta del usuario Si(1) o No(0)
 * @pre
 * @post Devolver el valor ingresado por el usuario
 */
int preguntar_seguir_jugando()
{
    int respuesta;
    printf("Seguir Jugando: Si-(1) | No-(0)");
    scanf("%d", &respuesta);
    return respuesta;
}

/**
 * Esta función se encarga de  inicializar dinamicamente la memoria necesaria para un nuevo tablero.
 *
 * @param tablero Puntero al tablero que se inicializara.
 * @return
 * @pre El puntero al tablero debe apuntar a una estructura valida
 * @post Se asigna memoria dinamicamente para las filas y columnas de los tableros sin completar(MATRIZ) y completo(TABLERO_COMPLETO).
 */
void inicializar_tablero(tablero_t* tablero) 
{
    //Se pide memoria para las filas de ambos tableros (Sin completar y completo)
    tablero->MATRIZ = (int**)malloc(MAX * sizeof(int*));
    tablero->TABLERO_COMPLETO = (int**)malloc(MAX * sizeof(int*));

    //Se pide memoria para las columnas de ambos tableros (Sin completar y completo)
    for (int i = 0; i < MAX; i++) 
    {
        tablero->MATRIZ[i] = (int*)malloc(MAX * sizeof(int));
        tablero->TABLERO_COMPLETO[i] = (int*)malloc(MAX * sizeof(int));
    }
}

/**
 * Esta funcion se encarga de liberar la memoria asignada dinámicamente para un tablero.
 *
 * @param tablero puntero al tablero cual liberaremos la memoria
 * @return
 * @pre El puntero al tablero debe apuntar a una estructura valida con memoria asignada dinamicamente. (inicializar_tablero)
 * @post La memoria asignada se liberara correctamente.
 */
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

/**
 * Esta funcion se encarga de inicializar un tablero inicial (el tablero a completar por el usuario)
 * Como tambien el mismo tablero pero ya completado(Esto para validar las entradas)
 * 
 * Ambos tableros se igualaran con nuesta estructura de matriz y tablero completo
 * 
 * El primer tablero era con numeros randoms, con validacion en fila columna y sub matris de 3x3 
 * pero teniamos errores de logica donde el jugador en un cierto punto de la partida no podia avanzar mas.
 *
 * @param tablero Puntero al tablero que se inicializara.
 * @return
 * @pre El puntero al tablero debe apuntar a una estructura valida.
 * @post El tablero se inicializa con una configuración inicial y completa.
 *       La configuracion inicial tiene celdas con valores y celdas vacias marcadas con 0.
 *       La configuracion inicial se asociara con nuestro miembro MATRIZ de la estructura
 *       La configuracion completa es una versión resuelta del tablero inicial.
 *       La configuracion completa se asociara con nuestro TABLERO_COMPLETo
 */
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

/**
 * Esta funcion se encarga de imprimir el tablero en pantalla
 *
 * @param tablero puntero a la matriz que representa donde transcurre el juego.
 * @return
 * @pre Tablero debe ser una estructura valida 
 * @post Imprime la matriz completa, delimitando filas,columnas y matrices internas de 3x3
 */
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


/**
 * Esta funcion se encarga de comprobar si el tablero esta o no completo.
 *
 * @param tablero puntero a la matriz que representa donde transcurre el juego.
 * @return numero entero que representa si el tablero esta completo (1) o si no lo esta (0)
 * @pre Programar un sudoku para utilizarlo de mensaje bienvenida
 * @post Imprimir un sudoku gigante en pantalla. 
 */
int esta_completo(tablero_t* tablero)
{
    int completo = 1;
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (tablero->MATRIZ[i][j] == 0)
            {
                completo = 0;  // Hay al menos una celda vacía
            }
        }
    }

    return completo;  // El tablero está completo
}


/**
 * Esta función se encarga de guardar un tablero desde un archivo.
 *
 * @param tablero Puntero al tablero donde se guardara la partida.
 * @param nombre_archivo Nombre del archivo en el cual guardamos el tablero.
 * @return 
 * @pre El puntero al tablero debe apuntar a una estructura valida.
 * @post El tablero se guarda en el archivo especificado.
 * Si el archivo no puede abrirse, se imprime un mensaje de error y se sale del programa.
 */
void guardar_tablero(tablero_t* tablero, char* nombre_archivo)
{
    FILE* archivo = fopen(nombre_archivo, "w");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo para guardar.\n");
        salir_del_programa();
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

/**
 * Esta función se encarga de cargar un tablero desde un archivo.
 * 
 * Como tambien de guardar el tablero completo, ya que estabamos teniendo un problema a la hora
 * de cargar partidas. Creemos es por trabajar sin retorno en la funcion de crear tableros. el tiempo corre!!! HELP
 *
 * @param tablero Puntero al tablero donde se cargará la partida.
 * @param nombre_archivo Nombre del archivo desde el cual cargar el tablero.
 * @return 
 * @pre El puntero al tablero debe apuntar a una estructura valida.
 * @post El tablero se carga desde el archivo especificado.
 * Si el archivo no puede abrirse, se imprime un mensaje y se sale del programa.
 */
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

/**
 * Esta funcion se encarga de imprimir un menu de bienvenida en pantalla
 *
 * @param
 * @return
 * @pre
 * @post Imprimir un menu de bienvenida
 */
void menu_bienvenida()
{
    printf("|Bienvenido al Sudoku de Commit & Conquer|\n");
    printf("|Por favor, elige una opcion|\n");
    printf("|1) Comenzar Juego|\n");
    printf("|2) Cargar partida|\n");
    printf("|3) Salir|\n");
}

/**
 * Esta funcion se encarga de terminar con la ejecución del programa.
 *
 * @param
 * @return
 * @pre
 * @post Imprimir un mensaje en pantalla, y salir de la ejecucion del programa.
 */
void salir_del_programa()
{
    printf("Gracias por jugar. Hasta luego.\n");
    exit(0);
}

/**
 * Esta funcion se encarga de corroborar que desea hacer el usuario
 * con respecto al menu_bievenida() impreso al comienzo del juego.
 *
 * @param opcion numero entero que representa que opcion elige el usuario
 * @param tablero puntero a la matriz que representa el tablero donde va a transcurrir el juego
 * @param nombre_archivo el nombre del archivo donde se carga la matriz, cuando se salve una partida
 * @return
 * @pre La estructura debe ser valida y representa el tablero inicial y completo.
 * El nombre del archivo debe ser valido como tambien debe existir en caso de querer cargar la partida
 * 
 * @post Inicializar el juego con el tablero predeterminado si la opcion es igual  a 1
 *          Cargar el tablero si la opcion es 2 -> Siempre y cuando se halla jugado una partida previa(el archivo existira en ese caso)
 *              o Si en la partida anterior el tablero quedo completo, un mensaje de error informandole al usuario
 */
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
        if(esta_completo(tablero))
        {
            printf("La ultima partida guardada fue completada\n");
        }
        else
        {
            jugar_sudoku(tablero, nombre_archivo);
        }
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

/**
 * Esta funcion se encarga de imprimir un muy lindo mensaje realizado en ASCII ART.
 *
 * @param
 * @return
 * @pre Programar un sudoku para utilizarlo de mensaje bienvenida
 * @post Imprimir un sudoku gigante en pantalla. 
 */
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
