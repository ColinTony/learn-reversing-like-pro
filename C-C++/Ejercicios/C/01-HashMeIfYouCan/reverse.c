#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main()
{
  int hash_digit = 0;
  int hash_digit_temp = 0;
  char list_posible[126-32]; // cadena para saber las poisbles caracters
  char hash_decypt[126-32];
  int hash[126-32]; // cadena para saber los caracteres que llevamos
  int rest=0; // valor restante del numero a regresar
  size_t pos = 0; // posicion del hash
  size_t j = 0;
  size_t k = 0;
  bool is_pass = false;


  scanf("%d",&hash_digit);
  hash_digit_temp = hash_digit;

  while (hash_digit_temp > 0)
  {
    pos++;
    printf("RESTO HASH : %d\n\n",hash_digit_temp);

    for(size_t i = 32; i<=126; i++)
    {
      int real_value = i * pos;
      int res = hash_digit_temp % real_value;

      if(res == 0)
      {
        list_posible[j] = (char)i;
        j++;
      }
    }

    list_posible[j+1]='\0';
    j = 0;
    k = 0;
    while(!is_pass && k<strlen(list_posible))
    {
        if((hash_digit_temp - ((int)list_posible[k] * pos)) > 0)
        {
          hash_decypt[j] = list_posible[k];
          j++;
          is_pass = true;
          hash_digit_temp -= ((int)list_posible[k] * pos);
        }
      k++;
    }
    // comprobar que no se pase.
    printf("Decrypt hash progres... %d\n",hash_digit_temp);
    printf("\n ------- \n hash digit : %d \n hash_decypt : %s \n hash digit temp : %d\n list: %s \n", hash_digit,hash_decypt,hash_digit_temp,list_posible);
  }
    printf("\nResiduo de hash : %d\n\n\n",hash_digit);
    printf("HASH DECRYPTED: %s \n",hash_decypt);
  return 0;
}
