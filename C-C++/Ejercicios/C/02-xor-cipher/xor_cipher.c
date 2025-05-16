/*
* 
* author: c0l1nr00t
* version : 1.0.0
*
* */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void printBanner()
{
  printf("\n-------------------------------------\n");
  printf("\t\tXOR_cipher\n");
  printf("by: c0l1nr00t\n");
  printf("-------------------------------------\n");
}

void xor_string(char *cadena)
{
  size_t len = strlen(cadena);

}

void read_string(char *cadena)
{
  fgets(cadena , strlen(cadena),)
}

// funcion operacion XOR
int main()
{
  bool is_finish = false; // flag para terminal la ejecucion.
  int opc=0;
  char clave[50];
  
  fgets(clave, strlen(clave), stdin);
  char[srtcspn(clave,"\n")] = '\0';

  do {
    printBanner();
    printf("Teclea la opcion que deseas realizar \n");
    printf("\n1.-Descifrar.\n2.-Cifrar\n3.-Ambas\n4.-Salir");

    scanf("%d",&opc); // leemos la opcion

    switch(opc)
    {
      case 1:
        printf("Generando Cipher ...\n");
      break;

      case 2:
      break;

      case 3:
      break;

      case 4:
        is_finish = true;
      break;

    }

  } while (!is_finish);

  printf("\n BYE !!\n");
  return 0;
}
