# 🧠 Ejercicio 4 – Cifrado y Descifrado XOR en C

## 📋 Descripción

Este ejercicio consiste en implementar un programa en C que:
- Cifre una cadena de texto usando el operador XOR y una clave.
- Permita descifrar la misma cadena utilizando el mismo proceso.

El propósito es comprender cómo se puede **ocultar información simple** mediante operaciones a bajo nivel, como XOR, que son comunes en el malware y en ingeniería inversa (*reversing*).

---

## 🎯 Objetivos

- Entender cómo funciona el cifrado XOR.
- Implementar funciones de cifrado y descifrado.
- Usar punteros y manipulación de arrays de caracteres.
- Generar una salida cifrada y mostrar cómo revertirla.

---

## 🛠️ Requisitos

- Conocimientos básicos de C.
- Compilador como `gcc`.

---

## 📦 Archivos

- `main.c`: Código fuente del programa.
- `README.md`: Este archivo.

---

## 🧪 Instrucciones

1. Compila el programa:
   ```bash
   gcc main.c -o xor_cipher
   ```

2. Ejecuta el binario:
   ```bash
   ./xor_cipher
   ```

3. Introduce una cadena y observa cómo se cifra y luego se descifra.

---

## 🔎 Conceptos útiles para reversing

- El XOR es reversible: `A ^ B = C` implica que `C ^ B = A`.
- Comúnmente usado para ocultar *strings* en binarios maliciosos.
- Aprenderás a identificar patrones repetitivos que permiten deducir claves en análisis de binarios.
