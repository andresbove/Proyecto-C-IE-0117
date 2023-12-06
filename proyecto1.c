#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_CIUDADES 20 // Definir el máximo de ciudades

// Función para calcular la ruta más corta usando fuerza bruta
long long int calcularRutaMasCorta(int n, int Distancias[MAX_CIUDADES][MAX_CIUDADES], int ciudadActual, int destino, int visitadas, long long int distanciaActual) {
    if (ciudadActual == destino) {
        return distanciaActual;
    }

    long long int distanciaMinima = LLONG_MAX;

    for (int i = 0; i < n; i++) {
        if (!(visitadas & (1 << i)) && Distancias[ciudadActual][i] != 0) {
            long long int nuevaDistancia = calcularRutaMasCorta(n, Distancias, i, destino, visitadas | (1 << i), distanciaActual + Distancias[ciudadActual][i]);
            distanciaMinima = (nuevaDistancia < distanciaMinima) ? nuevaDistancia : distanciaMinima;
        }
    }

    return distanciaMinima;
}

int obtenerIndiceCiudad(char ciudad, char Ciudades[MAX_CIUDADES][2], int CantCiudades) {
    for (int i = 0; i < CantCiudades; i++) {
        if (Ciudades[i][0] == ciudad) {
            return i;
        }
    }
    return -1;
}

int main() {
    int CantCiudades;
    
    printf("Ingrese la cantidad de ciudades: ");
    scanf("%d", &CantCiudades);

    // Verificación para asegurar que la cantidad de ciudades sea válida
    if (CantCiudades <= 0 || CantCiudades > MAX_CIUDADES) {
        printf("La cantidad de ciudades debe ser mayor que cero y menor o igual a %d.\n", MAX_CIUDADES);
        return 1;
    }

    char Ciudades[CantCiudades][2]; // Array bidimensional para almacenar los nombres de las ciudades (de longitud 2 para una letra)
    int Distancias[CantCiudades][CantCiudades]; // Array bidimensional para almacenar las distancias entre las ciudades

    for (int n = 0; n < CantCiudades; n++) {
        printf("Ingrese el nombre de la ciudad %d (con una letra): ", n + 1);
        scanf("%s", Ciudades[n]); // Lee una cadena de caracteres de longitud 1 (una letra)
    }

    // Capturar las distancias entre las ciudades
    for (int i = 0; i < CantCiudades; i++) {
        for (int j = 0; j < CantCiudades; j++) {
            printf("Ingrese la distancia entre la ciudad %s y %s (-1 si no están conectadas): ", Ciudades[i], Ciudades[j]);
            scanf("%d", &Distancias[i][j]); // Leer la distancia entre las ciudades i y j
            if (Distancias[i][j] == -1 && i != j) {
                Distancias[i][j] = 0; // Si es -1 y no es la misma ciudad, se asume que no están conectadas (se establece distancia cero)
            }
        }
    }

    // Mostrar las ciudades ingresadas y las distancias entre ellas
    printf("Ciudades y distancias:\n");
    for (int i = 0; i < CantCiudades; i++) {
        for (int j = 0; j < CantCiudades; j++) {
            printf("ruta %s - %s: Distancia %d\n", Ciudades[i], Ciudades[j], Distancias[i][j]);
        }
    }

    // Seleccionar ruta más corta entre origen y destino
    char origen, destino;

    printf("\nIngrese la ciudad de origen (una letra): ");
    scanf(" %c", &origen);

    printf("Ingrese la ciudad de destino (una letra): ");
    scanf(" %c", &destino);

    int index_origen = obtenerIndiceCiudad(origen, Ciudades, CantCiudades);
    int index_destino = obtenerIndiceCiudad(destino, Ciudades, CantCiudades);

    if (index_origen != -1 && index_destino != -1) {
        long long int distancia_minima = calcularRutaMasCorta(CantCiudades, Distancias, index_origen, index_destino, 1 << index_origen, 0);

        if (distancia_minima != LLONG_MAX) {
            printf("La distancia de ruta más corta entre %c y %c es: %lld\n", origen, destino, distancia_minima);
        } else {
            printf("No hay ruta disponible entre %c y %c.\n", origen, destino);
        }
    } else {
        printf("Ciudades inválidas.\n");
    }

    return 0;
}
