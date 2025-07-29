# Entorno Hacking

Este simplemente es un docker para practicar reversing de binarios en 64 bits y 32 bits.


## Instalacion de laboratorios con Docker

```bash
git clone https://github.com/ColinTony/learn-reversing-like-pro
cd learn-reversing-like-pro/Dockers
./startlab64.sh -h
```
### Instalar imagenes antes de usar:
Simplemente para instalar las imagenes.
```bash
./startlab64.sh -i # Crea una imagen vulnerable en docker 64 bits
./startlab64.sh -k # Crea una imagen vulnerable en docker 32 bits
```

### Uso de contenedores
```bash
./startlab64.sh -s # Inicia el contenedor 64 bits para reversing
./startlab64.sh -k # Inicia el contenedor 32 bits para reversing.
```

# Ejercicios

Todos los ejercicios o binarios que quieras probar ingresalos en la carpeta ctf.
Esta carpeta esta compartida con los contenedores para que puedas subir tus binarios vulnerables al conetenedor.
