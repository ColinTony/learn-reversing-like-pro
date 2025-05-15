#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TARGET 1265
#define MAX_LEN 6
#define MAX_RESULTS 3

int results_found = 0;

bool esAlfanumerico(char c) {
    return (c >= '0' && c <= '9') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z');
}

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

    // Rango ASCII completo, pero saltamos no alfanuméricos
    for (int c = 32; c <= 126; c++) {
        if (!esAlfanumerico((char)c))
            continue;

        buffer[pos] = (char)c;
        int new_hash = current_hash + c * (pos + 1);

        if (new_hash == TARGET) {
            buffer[pos + 1] = '\0';
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

