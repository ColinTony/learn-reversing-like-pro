
# ✅ Ejercicio Práctico - Exploit con Shellcode + SUID Root

## Descripción

Este ejercicio forma parte de mi camino en exploit development.  
El objetivo fue explotar un binario con permisos SUID para ejecutar una shell con privilegios de root usando shellcode inyectado.

---

## 🧠 Lógica del exploit

1. **Se da un binario con SUID** (`/bin/practical1`), propiedad de root.
2. Me conecto como usuario `testing` con privilegios bajos.
3. Compilo y ejecuto el exploit desde este usuario, apuntando al binario SUID.
4. El exploit:
   - Inyecta un shellcode (`/bin/sh`) en el stack.
   - Usa un relleno (`padding`) de 8 bytes antes del shellcode.
   - Calcula un offset de 44 bytes para sobreescribir el EIP.
   - Inserta la dirección del shellcode (`0xffffdfc0`, en little endian) como retorno.
5. Al ejecutarse, el binario salta a mi shellcode y se ejecuta una shell **como root**.

---

## 🧪 Herramientas y técnicas usadas

- `cyclic` para calcular offset exacto.
- `radare2 -d` para identificar dirección del stack (`esp`) y verificar contenido.
- Payload generado manualmente en formato `\xNN`.
- SHELLCODE adaptado para encajar en 48 bytes totales.

---

## 🐚 Resultado

```bash
./exploit
PAYLOAD...
bash-5.1# whoami
root
