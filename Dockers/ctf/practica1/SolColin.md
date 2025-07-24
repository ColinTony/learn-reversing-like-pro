# Mi solucion que hice para lograrlo


## Radare2 
Usando radare2 use el comando

```bash
radare2 -d practica.c
```
Dentro de radare2 , empece con comandos básicos para lograr encontrar la direccion de la funcion func.

```bash
aaa # Carga y analiza automaticamente el binario
afl # Revisamos todas las funciones detectadas.
```

Con eso localice que existia la funcion de func en con la direccion de memoria:

```bash
0x004005ad sys.func
```

En radare meti mi argumento de ejecucion el programa, ya que si bien recordamos el programa se corre asi:
```bash
./practica1 c0l1nr00t

./practica1 cadena
```

Para nosotros meter argumentos dentro de radare y su ejecucion , vamos a usar el siguiente comando
(recordar que se reinicia el binario con ood)
```bash
e dbg.args = c0l1nr00t
```
