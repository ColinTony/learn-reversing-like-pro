# Mi solucion que hice para lograrlo

# Compilacion

Recuerda compilar de esta forma el binario para que puedas sobreescribir el EIP

```bash
gcc -fno-stack-protector -D_FORTIFY_SOURCE=0 -z norelro -z execstack -o practica <file>.c
```

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
 sys.func
```
En este caso la direccion de memoria era 

```markdown
0x565561c9    1     64 sym.func
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

si nosotros podemos ejecutar el programa con :

```bash
dc
```
y con dr , revisar los registros que nos interesan.

## Sobreescribiendo el registro

Ahi podemos ver que direccion de memoria tiene el registro EIP al momento de terminar el programa.
La idea es que nosotros llenemos pasandole argumentos al programa demasiado largos hasta llegar a sobrescribir
el registro EIP. Para nosotros luego encontrar el offset y poder saber en que momento se empieza a sobreescribir
el registro. Para ello haremos uso de la herramienta cyclic.

Con esta herramienta nosotros generamos una cadena de 100 caracteres y haciendo uso de radare2 ver como termina
la ejecucion y si sobreescribe el registro EIP.

```bash
#1 
cyclic 100
#2
radare2 -d practica1
#3
aaa
#4
e dbg.args=<CadenaGeneradaConCyclic>
#5
ood
#6
dc
#7
dr
```

Podemos notar que al ejecutar el programa lograremos un segmentation fault.
El cual nos dice que efectivamente existe una vulnerabilidad de buffer.

Ahora lo que nos queda es ver que direccion tiene el registro EIP en nuestro caso quedo:

```markdown
0x6161616c
```
Ahora con cyclic podemos calcular rapidamente cuantos caracteres antes de llegar al registro EIP son:

```bash
cyclic -l 0x6161616c
```
En mi caso son 44 , entonces , podemos empezar a construir el exploit. Que estara el codigo fuente en el archivo `exploit.c`.



Al compilarlo y ejecutarlo , podemos ver como llamamos nuevamente a la funcion `func` que es justo lo que queriamos del ejercicio del libro.
