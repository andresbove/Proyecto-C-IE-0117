#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definición de la estructura Punto para representar coordenadas (x, y)
typedef struct {
    double x, y;
} Punto;

// Función que ordena los puntos por coordenada x
int comparar_puntos(const void *p1, const void *p2) {
    return ((Punto *)p1)->x - ((Punto *)p2)->x;
}

// Función que calcula el producto vectorial entre tres puntos
double producto_vectorial(Punto a, Punto b, Punto c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

// Función que determina si los puntos forman un polígono convexo
int es_convexo(Punto puntos[], int num_puntos) {
    if (num_puntos < 3) {
        return 0;
    }

    int i;
    int direccion = 0;

    for (i = 0; i < num_puntos - 2; i++) {
        double producto = producto_vectorial(puntos[i], puntos[i + 1], puntos[i + 2]);

        // Determinar la dirección de giro (positivo, negativo o colineales)
        if (producto < 0) {
            direccion |= 1; // Bit 1: giro a la derecha
        } else if (producto > 0) {
            direccion |= 2; // Bit 2: giro a la izquierda
        }

        // Si la dirección es mixta, entonces el polígono no es convexo
        if (direccion == 3) {
            return 0;
        }
    }

    return 1;
}
// función principal del programa
int main() {
    int num_puntos;
    printf("Ingrese el número de puntos: ");
    scanf("%d", &num_puntos);

    if (num_puntos < 3) {
        printf("Se necesitan al menos 3 puntos para formar un polígono.\n");
        return 1;
    }

    // Reserva de memoria para el arreglo de puntos
    Punto *puntos = (Punto *)malloc(num_puntos * sizeof(Punto));

    // pide los puntos al usuario 
    printf("Ingrese los puntos en el formato x y:\n");
    for (int i = 0; i < num_puntos; i++) {
        printf("Punto %d: ", i + 1);
        scanf("%lf %lf", &(puntos[i].x), &(puntos[i].y));
    }

    // Ordenar los puntos por coordenada x
    qsort(puntos, num_puntos, sizeof(Punto), comparar_puntos);

    // Verificar si los puntos forman un polígono convexo
    if (es_convexo(puntos, num_puntos)) {
        printf("Los ángulos del polígono son:");

        // Calcular e imprimir los ángulos entre las pendientes formadas por los puntos
        for (int i = 0; i < num_puntos; i++) {
            double angulo_rad = atan2(puntos[(i + 2) % num_puntos].y - puntos[i].y, puntos[(i + 2) % num_puntos].x - puntos[i].x) -
                                atan2(puntos[(i + 1) % num_puntos].y - puntos[i].y, puntos[(i + 1) % num_puntos].x - puntos[i].x);
            double angulo_grados = angulo_rad * (180.0 / M_PI);

            // Imprimir el ángulo
            printf("%.2f grados, ", angulo_grados);
        }
    } else {
        exit(0);
    }

    // Liberar la memoria reservada para el arreglo de puntos
    free(puntos);

    return 0;
}


