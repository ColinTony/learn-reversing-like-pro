# Entorno Hacking (Vagrant Edition)

Este repositorio contiene un laboratorio de **Reversing y Exploitation** basado en una **Máquina Virtual completa** (no Docker).

Diseñado específicamente para resolver los problemas de compatibilidad de kernels modernos con binarios de 32 bits (el famoso error `ptrace-traceme: Function not implemented`).  
Aquí corremos sobre un **Kernel nativo de 32 bits**.

---

## 📋 Requisitos Previos

Necesitas tener instalados **VirtualBox** y **Vagrant**.

### En Kali Linux / Debian recientes

Si `apt install vagrant` falla, usa estos comandos para agregar el repositorio oficial de HashiCorp:

```bash
# 1. Agregar llave y repositorio de HashiCorp (Versión compatible)
wget -O- https://apt.releases.hashicorp.com/gpg | sudo gpg --dearmor -o /usr/share/keyrings/hashicorp-archive-keyring.gpg
echo "deb [signed-by=/usr/share/keyrings/hashicorp-archive-keyring.gpg] https://apt.releases.hashicorp.com bookworm main" | sudo tee /etc/apt/sources.list.d/hashicorp.list

# 2. Instalar dependencias
sudo apt update
sudo apt install vagrant virtualbox virtualbox-dkms -y
```

---

## 🚀 Instalación y Uso

```bash
git clone https://github.com/ColinTony/learn-reversing-like-pro
cd learn-reversing-like-pro
vagrant up
```

---

## 📂 Flujo de Trabajo

Todo lo que pongas en el repo aparecerá en `/vagrant` dentro de la VM.

---

## 🛠 Herramientas Incluidas

- Kernel Linux 32-bit real
- Radare2
- GDB + pwndbg / GEF
- GCC multilib
- Python 2 y 3

---

## 💀 ASLR

```bash
echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
```

O solo para un binario:

```bash
setarch i386 -R ./binario
```

---

Happy Hacking  
**c0l1nr00t**
