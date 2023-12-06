//Guillermo Delgado Lopez C02585
//Cristian David Vega Romero C18418
//Andrés Bonilla Vega B81220
#include <stdio.h>
#include <stdlib.h>

// Función para obtener las direcciones de memoria de los números que inician cada FILA
int obtenerDireccionesFilas(int** matriz, int filas, int columnas, int** direcciones) {
    // Reserva de memoria para las direcciones
    *direcciones = (int*)malloc(filas * sizeof(int));

    if (*direcciones == NULL) {
        // Error al reservar memoria
        return -1;
    }

    // Copiar la dirección de memoria del primer elemento de cada fila
    for (int i = 0; i < filas; i++) {
        (*direcciones)[i] = (int)&matriz[i][0];
    }

    // No hubo errores
    return 0;
}
int prueba(){
    int filas, columnas;

    // Obtener dimensiones de la matriz
    columnas=3;
    filas=3;

    // Reserva de memoria para la matriz
    int** matriz = (int**)malloc(filas * sizeof(int*));

    if (matriz == NULL) {
        printf("Error al reservar memoria para la matriz.\n");
        return -1;
    }

    for (int i = 0; i < filas; i++) {
        matriz[i] = (int*)malloc(columnas * sizeof(int));

        if (matriz[i] == NULL) {
            printf("Error al reservar memoria para la fila %d.\n", i);
            return -1;
        }
    }

    // Obtener números enteros representando las posiciones en la matriz
    int numeroPosicion = 1;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = numeroPosicion;
            numeroPosicion++;
        }
    }

    // Obtener direcciones de memoria de los números que inician cada FILA
    int* direcciones;
    int resultado = obtenerDireccionesFilas(matriz, filas, columnas, &direcciones);

    if (resultado == -1) {
        printf("Error al obtener direcciones de memoria.\n");
        return -1;
    }

    // Imprimir las direcciones de memoria
    printf("Direcciones de memoria de los números que inician cada FILA:\n");
    for (int i = 0; i < filas; i++) {
        printf("%p\n", (void*)direcciones[i]);
    }

    // Liberar la memoria utilizada
    for (int i = 0; i < filas; i++) {
        free(matriz[i]);
    }
    free(matriz);
    free(direcciones);


    return 0;
}


int ejecutar(){
    int filas, columnas;

    // Obtener dimensiones de la matriz
    printf("Ingrese el número de filas: ");
    scanf("%d", &filas);

    printf("Ingrese el número de columnas: ");
    scanf("%d", &columnas);

    // Reserva de memoria para la matriz
    int** matriz = (int**)malloc(filas * sizeof(int*));

    if (matriz == NULL) {
        printf("Error al reservar memoria para la matriz.\n");
        return -1;
    }

    for (int i = 0; i < filas; i++) {
        matriz[i] = (int*)malloc(columnas * sizeof(int));

        if (matriz[i] == NULL) {
            printf("Error al reservar memoria para la fila %d.\n", i);
            return -1;
        }
    }

    // Obtener números enteros representando las posiciones en la matriz
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("Ingrese el número para la posición [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }

    // Obtener direcciones de memoria de los números que inician cada FILA
    int* direcciones;
    int resultado = obtenerDireccionesFilas(matriz, filas, columnas, &direcciones);

    if (resultado == -1) {
        printf("Error al obtener direcciones de memoria.\n");
        return -1;
    }

    // Imprimir las direcciones de memoria
    printf("Direcciones de memoria de los números que inician cada FILA:\n");
    for (int i = 0; i < filas; i++) {
        printf("%p\n", (void*)direcciones[i]);
    }

    // Liberar la memoria utilizada
    for (int i = 0; i < filas; i++) {
        free(matriz[i]);
    }
    free(matriz);
    free(direcciones);

    return 0;
}

int main() {
    int opcion;

    // elegir si hacer una prueba rapida o correr el programa solicitando datos
    printf("Digite 1 para correr el programa de forma regular o 2 para hacer la prueba rapida\n");
    scanf("%d", &opcion);

    if(opcion==1){
        return ejecutar();
    }else if(opcion==2){
        return prueba();
    }else {
        return -1;
    }
}
