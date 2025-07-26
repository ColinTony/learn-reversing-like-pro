#include <stdio.h>
#include <string.h>

void vulnerable() {
    char buffer[64];  // Buffer vulnerable

    puts("Bienvenido a Linux Exploiting 🧠");
    printf("Introduce tu input: ");
    
    // Leer desde stdin (entrada estándar)
    fgets(buffer, sizeof(buffer) + 256, stdin); // Intencional: permite overflow

    printf("Recibido: %s\n", buffer);
}

int main() {
    vulnerable();
    return 0;
}
