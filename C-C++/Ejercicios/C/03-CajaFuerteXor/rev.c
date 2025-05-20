#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    const int LONGITUD = 11;       // Longitud total de la cadena
    const char MAX_CHAR = 126;     // '~' (máximo imprimible)
    const int ASCII_START = 32;
    const int ASCII_END = 126;
    char cadena[LONGITUD + 1];     // +1 para el '\0'
    size_t acumulado = 0;

    // Paso 1: Llenar los primeros 10 caracteres con '~' (126)
    for (int i = 0; i < LONGITUD - 1; i++) {
        cadena[i] = MAX_CHAR;
        acumulado += (cadena[i] ^ i);  // XOR con su posición
    }

    // Paso 2: Calcular el carácter final (posición 10)
    int resto = 1337 - acumulado;
    int pos_final = LONGITUD - 1;      // Índice 10
    cadena[pos_final] = '\0';          // Marcador temporal

    // Buscar carácter válido para la posición 10
    bool encontrado = false;
    for (int c = ASCII_START; c <= ASCII_END; c++) {
        if ((c ^ pos_final) == resto) {
            cadena[pos_final] = c;
            encontrado = true;
            break;
        }
    }

    // Paso 3: Resultado y verificación
    if (encontrado) {
        printf("Cadena válida: %s\n", cadena);
        // Verificación del acumulado
        size_t total = 0;
        for (int i = 0; i < LONGITUD; i++) {
            total += (cadena[i] ^ i);
        }
        printf("Valor total: %zu (target: 1337)\n", total);
    } else {
        printf("No se encontró solución.\n");
    }

    return 0;
}
