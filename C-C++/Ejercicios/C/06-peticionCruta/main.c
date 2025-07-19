/*
 * Crear una petiucion HTTP usando sockets en crudo.
* */

#include <stdio.h>          // Para printf(), perror()
#include <stdlib.h>         // Para exit(), malloc() si fuera necesario
#include <string.h>         // Para strlen(), strstr(), strchr()
#include <unistd.h>         // Para close(), función POSIX para cerrar sockets
#include <sys/socket.h>     // Para socket(), connect(), send(), recv()
#include <netinet/in.h>     // Para struct sockaddr_in
#include <arpa/inet.h>      // Para inet_addr(), convierte IP de texto a binario
#include <netdb.h>          // Para gethostbyname() (no usado aquí pero útil si haces DNS)

#define BUFFER_SIZE 4096    // Tamaño del buffer para leer respuesta HTTP
#define PORT 80

int main ()
{
  const char *host = "127.0.0.1";
  // Creamos el socket AF_INET = IPV4 y SOCK_STREAM = TCP
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  // is hay error devolvera -1
  if(sock < 0)
  {
    perror("Error al crear el socket");
    return 1;
  }
  // Estructura para guardar los datos del servidor
  struct sockaddr_in server_addr;                 // se usa la Estructura
  server_addr.sin_family = AF_INET;               // Tipo de red: IPv4
  server_addr.sin_port = htons(PORT);             // Puerto (convertido a network byte order)
  server_addr.sin_addr.s_addr = inet_addr(host);  // IP como binario (ej: 127.0.0.1)


  // conectamos al servidor
  // Conectar al servidor usando connect()
  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) 
  {
      perror("Error al conectar");  // Error si no se pudo establecer conexión
      return 1;
  }
  printf("[+] Conectado a %s:%d\n", host, PORT);  // Confirmación visual
  // Construimos manualmente una petición HTTP válida
  char request[] = "GET / HTTP/1.1\r\n"
                  "Host: 127.0.0.1\r\n"
                  "Connection: close\r\n"
                  "\r\n";  // Doble salto de línea indica fin de headers

  // Enviar la petición al servidor
  send(sock, request, strlen(request), 0);


  // Preparar buffer para recibir la respuesta
  char buffer[BUFFER_SIZE];
  int bytes;
  
  // Leer los datos que llegan desde el socket
  while ((bytes = recv(sock, buffer, sizeof(buffer)-1, 0)) > 0) {
      buffer[bytes] = '\0';         // Aseguramos que el string esté bien terminado
      printf("%s", buffer);         // Imprimir respuesta completa (puede incluir flag)
  }
  // Cerrar la conexión después de terminar
  close(sock);
  return 0;
}
