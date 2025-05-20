# RETO DE HOY (Exploit Dev / C / Reversing)
## Nombre: La caja fuerte de XOR.
## Nivel: Medio
### Objetivo: Encontrar la contraseña correcta que desbloquea una caja fuerte, usando análisis estático (descompilación o lectura de código C) y lógica reversa.

## Descripcion:
Un programa en C recibe una contraseña de 9 caracteres, le aplica un algoritmo XOR + suma, y si el resultado acumulado es 0x539 (1337), te da acceso.
Este reto es idéntico en estructura al reto que resolviste con radare2, pero esta vez debes crear tú mismo el programa, simular el proceso y luego encontrar una contraseña válida sin fuerza bruta.

# Objetivos específicos:
Escribe un programa en C que:
Reciba una cadena de 9 caracteres.
Haga por cada carácter:

```C
acumulador += (caracter ^ i);  // donde i es la posición del caracter (0 a 8)
```
Compare el acumulador con 1337.

Luego escribe un programa o script (en C o Python) que invierta el proceso y genere una contraseña válida (caracteres imprimibles, si puedes).

Opcional: Haz un binario con -fno-stack-protector -no-pie y prácticalo con radare2, gdb o ghidra.
