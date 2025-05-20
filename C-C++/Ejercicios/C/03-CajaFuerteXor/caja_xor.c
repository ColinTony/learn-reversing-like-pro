#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// funcion para realizar la operacion XOR de las cadenas.
// solo seran cadenas imprimibles.
size_t xor_hash(char *cadena)
{
  const size_t ASCII_START = 32;
  const size_t ASCII_END = 126;

  const size_t len = strlen(cadena); // caracteres
  bool is_ok = true;
  size_t contador = 0;

  // Recorremos solo caracteres imprimibles.
  for(size_t i = 0; i<len; i++)
  {
    if((cadena[i]>= ASCII_START) && (cadena[i]<=ASCII_END))
      contador += (cadena[i] ^ i);
    else
      is_ok = false;
  }

  if(!is_ok)
  {
    printf("\n No habia caracteres imprimibles en la cadena. \n");
    contador = 0;
    return contador;
  }
  return contador;
}

int main()
{
  char cadena[12];
  printf("\n Teclea la cadena solo se leeran 11 caracteres: \n");
  fgets(cadena , sizeof(cadena) , stdin);
  cadena[strcspn(cadena,"\n")] = '\0';
  size_t contador = xor_hash(cadena);

  if(contador == 0)
  {
    printf("\n Ocurrio un error al leer la cadena.\n");
    return 1;
  }
  
  if(contador == 1337)
  {
    printf("\n La cadena es VALIDA !!\n");
    printf("\n La cadena es %s con valor %zu \n",cadena,contador);
    return 0;
  }

    printf("\n La cadena es INVALIDA !!\n");
    printf("\n La cadena es %s con valor %zu \n",cadena,contador);

  return 0;
}
