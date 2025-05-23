#include <stdio.h>
#include <stdlib.h>

int main() {
    int clave = 0;
    char pass[10];
    printf("Password: ");
    scanf("%9s", pass);
    
    for(int i = 0; pass[i]; i++) {
        clave += pass[i] ^ (0x55 + i);
        printf("%d - %c \n", clave,pass[i]);
    }

    if(clave == 1337) {
        puts("Acceso permitido");
    } else {
        puts("Acceso denegado");
    }

    return 0;
}

