# 🧠 CTF Mini Challenge: HashMeIfYouCan

## 🔐 Descripción

Este reto simula un validador de contraseñas antiguo que utiliza un algoritmo de hashing **casero**, donde la clave correcta produce un hash específico.

El sistema aplica el siguiente algoritmo a una cadena ingresada por el usuario:

```
hash = carácter_ASCII * posición_en_la_cadena (comenzando desde 1)
```

Por ejemplo, para la cadena `"abc"`:

```
'a' * 1 = 97 * 1 = 97
'b' * 2 = 98 * 2 = 196
'c' * 3 = 99 * 3 = 297
------------------------
hash total = 590
```

---

## 🎯 Objetivo

Encuentra **una cadena exacta** que, al aplicar el algoritmo, produzca un **hash total de 1265**.

---

## 🧩 Tu misión

1. Escribe un programa en **C** que:
   - Pida al usuario una cadena.
   - Calcule el hash de la cadena según la fórmula dada.
   - Compare el resultado con el número **1265**.

2. Si el resultado coincide con 1265:
   - Muestra el siguiente mensaje:

     ```
     ¡Acceso concedido! FLAG: CTF{hash_pwned}
     ```

3. Si no coincide:
   - Muestra este mensaje:

     ```
     Hash incorrecto. Intenta de nuevo.
     ```

---

## ✅ Requisitos

- Lenguaje: **C**
- Conocimientos: cadenas, ASCII, bucles, condicionales

---

## 🏁 Entrega

Cuando encuentres la cadena correcta, comparte el input que te dio acceso para recibir el **siguiente reto**.

---

## 🔓 Ejemplo de ejecución

```
Ingrese la cadena: abc
Hash incorrecto. Intenta de nuevo.

Ingrese la cadena: ????
¡Acceso concedido! FLAG: CTF{hash_pwned}
```

---

## 👨‍💻 Autor

Ejercicio creado por ChatGPT y modificado por c0l1nr00t, adaptado para aprender **algoritmia orientada a hacking** desde lo básico.

## NOTA:
Solo considerar que los caracteres que se usan son caracteres Letras y Numeros. NO CARACTERES ESPECIALES.
