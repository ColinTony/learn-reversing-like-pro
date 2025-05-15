/*
*
* author: c0l1nr00t
* version: 1.0.0
* */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT 256 // definimos el maximo de caracteres

int main()
{
  // cadena usuario
  char cadena[MAX_INPUT];
  int hash = 0;
  /*
  *
  * fgets evita desbordamiento de buffer.
  * imnecesita fgets(char *str, int n , FILE * stream);
  * basicamente:
  *    char *str -> direccion de memoria donde se comienza a escribir
  *    int n -> numero maximo de caracteres al leer incluyendo el caracter '\0'
  *    FILE *stream -> indica de donde leer los datos en este caso del teclado stdin
  */

  // Usa fgets para leer una línea de forma segura desde stdin.
  // Limita la lectura a (size - 1) y siempre termina con '\0'.
  // Incluye '\n' si cabe; hay que eliminarlo manualmente si no se desea.
  printf("Ingresa la cadena : ");
  fgets(cadena , sizeof(cadena) , stdin);
  
  if(cadena == NULL){
    printf("Error al leer la cadena");
    return 0;
  }
  
  size_t len = strlen(cadena);
  
  if(len > 0 && cadena[len - 1 ] == '\n')
  {
    cadena[len - 1] = '\0';
    len--;
  }
  
  // convertir a ASCII caracteres (int)char
  for(size_t i = 0; i<len; i++)
    hash += ((int)cadena[i] * (i+1));

  printf("Hash : %i\n",hash);

  if(hash == 1265)
    printf("¡Acceso consedido! FLAG : CTF{flag_c0l1nr00t_LO_LOGRASTE}\n");
  else {
    printf("!Acceso Denegado!\n");
  }

}
