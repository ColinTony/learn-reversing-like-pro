#!/usr/bin/env bash
set -Eeuo pipefail
export DEBIAN_FRONTEND=noninteractive
if [ "$(getconf LONG_BIT)" != 32 ] || ! uname -m | grep -Eq '^i[3-6]86$'; then
  echo 'ERROR: esta VM no utiliza un kernel nativo de 32 bits.' >&2
  exit 1
fi
. /etc/os-release
if [ "$ID" != debian ] || [ "$VERSION_ID" != 12 ]; then
  echo "ERROR: se esperaba Debian 12 i386; encontrado ${PRETTY_NAME}." >&2
  exit 1
fi
apt-get update
apt-get install -y --no-install-recommends \
  build-essential gcc g++ make binutils gdb gdbserver libc6-dbg \
  python3 python3-pip python3-pwntools \
  git curl wget ca-certificates sudo file strace ltrace procps \
  vim nano less netcat-openbsd socat \
  pkg-config meson ninja-build cmake autoconf automake libtool \
  libssl-dev libzip-dev zlib1g-dev liblz4-dev
install -d -m 0755 /opt/protostar/bin /opt/ejercicios/bin
python3 -c 'from pwn import context; print("pwntools:", context.arch)'
echo '[OK] Paquetes base del laboratorio i386 instalados.'
