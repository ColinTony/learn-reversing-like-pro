#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void func(char *arg)
{
  char nombre[32];
  strcpy(nombre,arg);
  printf("\n Bienvenido a Linux Exploiting %s \n\n", nombre);
}

void main(int argc , char argv[])
{
  if(argc != 2){
    printf("USO : %s NOMBRE\n",argv[0]);
    exit(0);
  }
  func(argv[1]);
  printf("FIN del programa\n");
  return 0;
}
