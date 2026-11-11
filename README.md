# Learn Reversing Like Pro — laboratorio Vagrant i386

Laboratorio local de reversing y explotación de binarios. Mantiene los ejercicios originales de `Contenedores/WarGames` y reemplaza el aprovisionamiento antiguo basado en `ubuntu/xenial32` por **Debian 12 i386 con kernel de 32 bits**, dentro de **VirtualBox + Vagrant**. **No usa Docker.**

> **Estado de validación:** los scripts y la sintaxis se han revisado estáticamente. No se ha arrancado la VM en este entorno de edición. La compatibilidad de `stack0`, `ptrace`, Radare2 y VirtualBox con tu Kali se comprueba al ejecutar `verify-lab.sh`; no está confirmada de antemano.

## Requisitos en Kali Linux

- CPU x86_64 con virtualización habilitada; Vagrant 2.4 o posterior, VirtualBox compatible, `rsync` y `ssh`.
- Comprueba primero `vagrant --version`, `VBoxManage --version` y `lsmod | grep vbox`.
- Al menos 2 GiB de RAM para la VM, 2 CPU y espacio para compilar Radare2.
- **No ejecutar** `starlabs.sh`, `dockerclean.sh` ni desactivar ASLR en Kali.

## Arrancar

```bash
cd Contenedores
vagrant up --provider=virtualbox
vagrant ssh
```

La box usada por defecto es `generic/debian12` **v4.3.12, arquitectura i386** (no amd64). Vagrant sincroniza el repositorio desde el host a `/workspace` mediante **rsync unidireccional**, excluyendo `.git`, `.vagrant` e imágenes de VM. Los binarios originales no se modifican; se copian a `/opt/protostar/bin` con dueño root y SUID, en el disco interno de la VM.

**Dentro de la VM:**

```bash
uname -m
getconf LONG_BIT
file /opt/protostar/bin/stack0
printf 'abc\n' | /opt/protostar/bin/stack0
bash /workspace/Contenedores/tools/verify-lab.sh
```

Resultado esperado de `getconf LONG_BIT`: `32`. El script informa de arquitectura, SUID, `stack0`, `ptrace`, pwntools y GDB. También comprueba que `r2` esté instalado.

## Ejercicios y depuración

```bash
ls /opt/protostar/bin
cp /opt/protostar/bin/stack0 /tmp/stack0-debug
chmod 0755 /tmp/stack0-debug
# La copia NO es SUID: GDB puede depurarla sin restricciones de SUID.
gdb -q /tmp/stack0-debug
r2 -A /tmp/stack0-debug
python3 -c 'from pwn import ELF; print(ELF("/tmp/stack0-debug").arch)'
```

Los ejercicios SUID reales se ejecutan como usuario normal desde `/opt/protostar/bin`. Para GDB es preferible una copia **sin SUID**; el kernel puede impedir depurar ejecutables SUID por diseño. No deshabilites las protecciones del anfitrión para arreglarlo.

ASLR solo **dentro de la VM**:

```bash
cat /proc/sys/kernel/randomize_va_space
setarch i386 -R /tmp/stack0-debug
# Solo si un ejercicio lo exige y únicamente en el invitado:
sudo sysctl -w kernel.randomize_va_space=0
# Restaurar al terminar:
sudo sysctl -w kernel.randomize_va_space=2
```

No modificar `/proc/sys/kernel/randomize_va_space` desde Kali.

## Operación y reparación

```bash
# En Contenedores/ en Kali
vagrant rsync             # cambios nuevos del host -> VM
vagrant provision         # después de rsync
vagrant halt
vagrant destroy           # elimina solo esta VM, no los ejercicios del host
```

Radare2 6.1.8 se compila desde tag y commit fijos durante el primer aprovisionamiento; requiere conexión de red. Si falla esta fase, puedes iniciar sin ella para diagnosticar:

```bash
REVERSING_INSTALL_R2=0 vagrant up --provider=virtualbox
```

En ese modo la verificación marcará `r2` como ausente; no constituye una instalación completa. Pwndbg, GEF y Python 2 son opcionales y **no** se instalan automáticamente porque su compatibilidad con i386 requiere verificación.

## Box local y fin de HCP Vagrant Registry

El catálogo HCP Vagrant tiene cierre anunciado para el **31 de diciembre de 2026**. Conserva una copia verificada de la box i386. Para usarla localmente:

```bash
vagrant box add /ruta/debian12-i386-virtualbox.box --name reversing/debian12-i386 --provider virtualbox
REVERSING_BOX=reversing/debian12-i386 vagrant up --provider=virtualbox
```

Si usas una box distinta, verifica procedencia, checksum y kernel i386 antes de confiar en ella. Los scripts rechazan arquitecturas incorrectas.

## Compatibilidad y seguridad

- Debian 12 i386 tiene soporte LTS hasta junio de 2028.
- Protostar es histórico: los ejecutables pueden depender de detalles antiguos de glibc o cargador ELF. `stack0` es la primera prueba; el resto necesita validación individual.
- Solo NAT/SSH de Vagrant para aprovisionamiento. No se configuran puertos públicos de retos ni red bridged.
- Versiones anteriores almacenaron `Contenedores/.vagrant/`, incluida una clave privada generada. El estado actual la elimina del índice y `.gitignore` evita repetirlo; **el historial Git aún la conserva**.
- Los Dockerfiles anteriores quedan como referencia; no forman parte del flujo nuevo.

Documentación: https://developer.hashicorp.com/vagrant/docs y https://wiki.debian.org/LTS/Bookworm
