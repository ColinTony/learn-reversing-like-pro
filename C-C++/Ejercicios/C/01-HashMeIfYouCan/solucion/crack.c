#include <stdio.h>
#include <string.h>

#define TARGET 1265
#define MAX_LEN 6
#define MAX_RESULTS 3

int results_found = 0;

// Función para calcular el hash de una cadena según el criterio
int calcular_hash(const char *cadena) {
    int hash = 0;
    size_t len = strlen(cadena);
    for (size_t i = 0; i < len; i++) {
        hash += ((int)cadena[i] * (i + 1));
    }
    return hash;
}

void search(char *buffer, int pos, int current_hash) {
    if (results_found >= MAX_RESULTS || current_hash > TARGET || pos >= MAX_LEN)
        return;

    // Para la primera posición, empieza en ASCII 33 para evitar espacios al inicio
    int start_char = (pos == 0) ? 33 : 32;

    for (int c = start_char; c <= 126; c++) {
        buffer[pos] = (char)c;
        int new_hash = current_hash + c * (pos + 1);

        if (new_hash == TARGET) {
            buffer[pos + 1] = '\0';
            // Validar hash por seguridad
            if (calcular_hash(buffer) == TARGET) {
                printf("Cadena encontrada: \"%s\"\n", buffer);
                results_found++;
                if (results_found >= MAX_RESULTS)
                    return;
            }
        } else {
            search(buffer, pos + 1, new_hash);
        }
    }
}

int main() {
    char buffer[MAX_LEN + 1] = {0};
    search(buffer, 0, 0);
    return 0;
}

