#include <stdio.h>
#include <string.h>

void mensaje() {
    char clave[8] = "gh@6D*!";
    char user_input[50];

    printf("Introduce la clave secreta: ");
    scanf("%49s", user_input);

    if (strcmp(clave, user_input) == 0) {
        printf("¡Acceso concedido!\n");
        printf("Flag: YOU_HAVE_BYPASSED_THE_CHECK\n");
    } else {
        printf("Acceso denegado.\n");
    }
}

int main() {
    mensaje();
    return 0;
}

