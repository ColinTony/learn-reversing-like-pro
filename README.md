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


## 🚨⚠️ **ADVERTENCIA DE SEGURIDAD — ASLR GLOBAL** ⚠️🚨

💣 **Este laboratorio modifica la configuración de seguridad del host**  
Durante la práctica se **DESACTIVA** el ASLR global para que las direcciones de memoria sean predecibles:

```bash
kernel.randomize_va_space = 0   # ❌ OFF (riesgoso)
```

Al salir, el script lo restaura a:

```bash
kernel.randomize_va_space = 2   # ✅ ON (por defecto)
```

---

### ⚠ **Riesgo crítico**:
Si la sesión/laboratorio se cierra **inesperadamente** (💥 crash, ❌ SIGKILL, 🔌 apagón, etc.),  
el host puede **quedar con ASLR desactivado** y vulnerable.

---

### 🔍 **Verificar estado actual**:
```bash
cat /proc/sys/kernel/randomize_va_space
# 0 = ❌ OFF
# 1 = ⚠️ Parcial
# 2 = ✅ ON
```

---

### 🛠 **Restaurar manualmente**:
```bash
echo 2 | sudo tee /proc/sys/kernel/randomize_va_space >/dev/null
```

---

### 💡 **Recomendaciones importantes**:
- 🚫 **Nunca** dejes el ASLR en `0` después de practicar.
- 🕵️ Verifica y restaura manualmente si interrumpes el script antes de tiempo.
- 🛡 Para mayor seguridad, usa **ASLR solo por proceso**:
  ```bash
  setarch "$(uname -m)" -R bash    # 🖥 shell sin ASLR
  setarch "$(uname -m)" -R gdb -q ./stack0
  ```
- 🔄 Añade un **check final** en tus scripts:
  ```bash
  echo -n "[*] ASLR final: "
  cat /proc/sys/kernel/randomize_va_space
  ```

---

⚡ **Recuerda**: dejar el ASLR en `0` expone tu sistema a ataques locales de *memory corruption*.  
Usa este laboratorio con **responsabilidad**.

