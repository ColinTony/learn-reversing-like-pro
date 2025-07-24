// ghost_inject.c
// Simulación de Ghost Stack Injection vía fake sigreturn frame

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <ucontext.h>
#include <stdlib.h>

// Esta cadena se incluye en el binario para que pwntools la encuentre
char *binsh = "/bin/sh";

void vulnerable_function() {
    char buffer[128];
    puts("🔓 Escribe tus datos:");
    read(0, buffer, 512);  // Desbordamiento intencional
}

void setup() {
    setvbuf(stdout, NULL, _IONBF, 0);
}

int main() {
    setup();
    vulnerable_function();
    return 0;
}
