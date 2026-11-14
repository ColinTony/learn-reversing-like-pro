#!/usr/bin/env bash
set -Eeuo pipefail
ROOT=/workspace/Contenedores/WarGames
SOURCE="$ROOT/protozip/protostar/bin"
if [ ! -d "$SOURCE" ]; then
  SOURCE="$ROOT/protostar_build/protostar/bin"
fi
if [ ! -d "$SOURCE" ]; then
  echo '[ERROR] No se encuentran los binarios Protostar en /workspace.' >&2
  exit 1
fi
install -d -m 0755 /opt/protostar/bin /opt/ejercicios/bin
count=0
for bin in "$SOURCE"/*; do
  [ -f "$bin" ] || continue
  name="${bin##*/}"
  case "$name" in
    stack[0-7]|heap[0-3]|format[0-4]|net[0-4]|final[0-2])
      install -o root -g root -m 4755 "$bin" "/opt/protostar/bin/$name"
      count=$((count + 1))
      ;;
  esac
done
if [ "$count" -lt 8 ]; then
  echo "[ERROR] Se instalaron solamente $count binarios Protostar." >&2
  exit 1
fi
if [ -f "$ROOT/ejercicios/p100.c" ]; then
  install -m 0644 "$ROOT/ejercicios/p100.c" /opt/ejercicios/bin/p100.c
  gcc -O0 -fno-stack-protector -fno-pie -no-pie -z execstack \
    /opt/ejercicios/bin/p100.c -o /opt/ejercicios/bin/p100
fi
echo "[OK] Instalados $count binarios Protostar. Fuente: $SOURCE"
