#!/usr/bin/env bash
set -Eeuo pipefail
R2_TAG=6.1.8
R2_SHA=d904d02e1157b45135c6e61651d890bac8abe873
if command -v r2 >/dev/null 2>&1 && r2 -v | grep -q "$R2_TAG"; then
  echo "[OK] Radare2 $R2_TAG ya está instalado."
  exit 0
fi
mkdir -p /opt/reversing-src
if [ ! -d /opt/reversing-src/radare2/.git ]; then
  git clone --depth 1 --branch "$R2_TAG" \
    https://github.com/radareorg/radare2.git /opt/reversing-src/radare2
fi
cd /opt/reversing-src/radare2
if [ "$(git rev-parse HEAD)" != "$R2_SHA" ]; then
  echo '[ERROR] SHA de Radare2 distinto al esperado: no se compilará.' >&2
  exit 1
fi
if [ ! -f build/build.ninja ]; then
  meson setup build --prefix=/usr/local
fi
meson compile -C build -j 2
meson install -C build
ldconfig
command -v r2
r2 -v
