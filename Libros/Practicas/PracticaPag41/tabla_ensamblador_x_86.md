### 📜 TABLA RESUMEN DE ENSAMBLADOR X86 (32 bits)

---

## 🔧 REGISTROS PRINCIPALES

| Registro | Significado                        | Uso principal                          | Ejemplo                      |
|----------|-------------------------------------|----------------------------------------|------------------------------|
| EAX      | Acumulador                         | Operaciones aritméticas, retorno        | `mov eax, 5`                 |
| EBX      | Base                               | Direcciones base, datos                | `mov ebx, [var]`             |
| ECX      | Contador                           | Bucles, repeticiones                   | `dec ecx / jnz loop`         |
| EDX      | Extensión del acumulador           | Multiplicación, E/S                    | `mul edx`                    |
| ESI      | Source Index                       | Copia de memoria (fuente)             | `mov al, [esi]`              |
| EDI      | Destination Index                  | Copia de memoria (destino)            | `mov [edi], al`              |
| ESP      | Stack Pointer                      | Apunta al tope del stack              | `push eax / pop ebx`         |
| EBP      | Base Pointer                       | Base del stack frame actual           | `mov ebp, esp`               |
| EIP      | Instruction Pointer                | Apunta a la siguiente instrucción     | Se modifica con `call`, `ret`|

---

## ⚙️ INSTRUCCIONES DE MOVIMIENTO

| Instrucción | Significado                  | Ejemplo             | Qué hace                          |
|--------------|-----------------------------|----------------------|----------------------------------|
| `mov`        | Mover valor                 | `mov eax, 10`        | Copia 10 en `eax`                |
| `push`       | Apilar valor                | `push eax`           | Decrementa ESP, guarda `eax`     |
| `pop`        | Desapilar valor             | `pop ebx`            | Carga valor del tope a `ebx`     |
| `lea`        | Cargar dirección efectiva   | `lea eax, [ebp-4]`   | Guarda la dirección en `eax`     |
| `xchg`       | Intercambiar                | `xchg eax, ebx`      | Intercambia contenidos           |

---

## ➕ INSTRUCCIONES ARITMÉTICAS / LÓGICAS

| Instrucción | Operación             | Ejemplo            | Resultado                     |
|--------------|------------------------|---------------------|-------------------------------|
| `add`        | Suma                  | `add eax, 5`        | eax = eax + 5                 |
| `sub`        | Resta                 | `sub ebx, 1`         | ebx = ebx - 1                 |
| `inc`        | Incremento            | `inc ecx`            | ecx = ecx + 1                 |
| `dec`        | Decremento            | `dec ecx`            | ecx = ecx - 1                 |
| `mul`        | Multiplicación        | `mul ecx`            | eax = eax * ecx               |
| `div`        | División             | `div ecx`            | eax = eax / ecx, resto en edx |
| `and`        | AND binario           | `and eax, 0xFF`      | eax &= 0xFF                   |
| `or`         | OR binario            | `or eax, 0x1`        | eax |= 0x1                    |
| `xor`        | XOR binario           | `xor eax, eax`       | eax = 0                        |
| `not`        | Negación binaria      | `not eax`            | eax = ~eax                    |

---

## 🔁 INSTRUCCIONES DE CONTROL DE FLUJO

| Instrucción | Tipo          | Ejemplo           | Descripción                             |
|--------------|---------------|--------------------|------------------------------------------|
| `jmp`        | Salto directo | `jmp etiqueta`     | Salta a una etiqueta sin condición       |
| `je`         | Igual         | `je etiqueta`      | Salta si ZF (zero flag) está activado     |
| `jne`        | Distinto      | `jne etiqueta`     | Salta si ZF está apagado                 |
| `jg`         | Mayor         | `jg etiqueta`      | Salta si mayor (signed)                  |
| `jl`         | Menor         | `jl etiqueta`      | Salta si menor (signed)                  |
| `cmp`        | Comparar      | `cmp eax, ebx`     | Compara y actualiza flags                |
| `call`       | Llamada       | `call funcion`     | Salta a func, guarda ret address en stack|
| `ret`        | Retorno       | `ret`              | Vuelve a la dirección guardada (pop EIP) |

---

## 🧠 FLAGS COMUNES

| Flag | Nombre       | Significado                       |
|------|--------------|------------------------------------|
| ZF   | Zero Flag    | Se activa si resultado fue cero   |
| SF   | Sign Flag    | Se activa si resultado fue negativo|
| CF   | Carry Flag   | Se activa en desbordamiento        |
| OF   | Overflow Flag| Se activa en overflow aritmético   |

---

## 🧪 EJEMPLO COMPLETO

```asm
func:
  push ebp
  mov ebp, esp
  sub esp, 0x20       ; reservar buffer de 32 bytes
  lea eax, [ebp-0x20] ; apuntar al buffer
  mov [eax], 0x41414141 ; escribir 'AAAA'
  leave
  ret
```

---

¡Listo! Esta tabla es tu referencia esencial para practicar exploit development en x86 32 bits. Si quieres la versión imprimible o extendida con instrucciones SSE/FPU o 64 bits, dime y la armamos.

