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

void xor_string(char *cadena , char *clave , bool is_cipher)
{
  size_t len = strlen(cadena);
  size_t len_clave = strlen(clave);
  size_t j = 0;

  for (size_t i= 0; i<len; i++) 
  {
    if(j >= len_clave)
      j = 0;
    
    cadena[i] ^= clave[j];
    printf("\n HEX: %02X \n", (unsigned char)cadena[i]);
    j++;
  }
  if(is_cipher)
    printf("CADENA CIFRADA : %s \n", cadena);
  else 
    printf("CADENA DESCIFRADA : %s\n", cadena);
}

void read_string(char *cadena, size_t size)
{
  fgets(cadena , size, stdin);
  cadena[strcspn(cadena , "\n")] = '\0';
}

// funcion operacion XOR
int main()
{
  bool is_finish = false; // flag para terminal la ejecucion.
  int opc=0;
  char clave[50];
  char cadena[100];
  printf("Ingresa la CLAVE con cual cifrar\n");
  read_string(clave, sizeof(clave));
  printf("Ingresa la cadena descifrar o cifrar \n");
  read_string(cadena, sizeof(cadena));

  do {
    printBanner();
    printf("Teclea la opcion que deseas realizar \n");
    printf("\n1.-Descifrar.\n2.-Cifrar\n3.-Ambas\n4.-Salir\n");

    scanf("%d",&opc); // leemos la opcion

    switch(opc)
    {
      case 1:
        printf("Descifrando Cipher ...\n");
        xor_string(cadena,clave,false);
      break;
      case 2:
        printf("Generando Cipher ...\n");
        xor_string(cadena,clave,true);
      break;

      case 3:
        printf("Cifrando y Descifrando\n");
        xor_string(cadena,clave,true);
        xor_string(cadena,clave,false);
      break;

      case 4:
        is_finish = true;
      break;
      
      default:
        printf("\nValor ingresado invalido.\n");
      break;
    }

  } while (!is_finish);

  printf("\n BYE !!\n");
  return 0;
}
