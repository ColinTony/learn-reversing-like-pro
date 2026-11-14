#!/usr/bin/env bash
# Destruye SOLO la VM de este Vagrantfile y su disco.
# No elimina el repositorio, las boxes base ni las herramientas de Kali.
set -Eeuo pipefail

cd -- "$(dirname -- "${BASH_SOURCE[0]}")"
[[ -f Vagrantfile ]] || { echo '[ERROR] No se encontró Vagrantfile.' >&2; exit 1; }
command -v vagrant >/dev/null 2>&1 || { echo '[ERROR] Vagrant no está disponible.' >&2; exit 1; }

case "${1:-}" in
  --si) ;;
  '')
    echo 'Se eliminarán la VM reversing-legacy32 y TODOS los archivos guardados únicamente dentro de ella.'
    echo 'Se conservan: repositorio, archivos de Kali y box base de Vagrant.'
    read -r -p 'Escribe BORRAR para continuar: ' confirmacion || exit 1
    if [[ "$confirmacion" != BORRAR ]]; then
      echo 'Cancelado; no se eliminó nada.'
      exit 0
    fi
    ;;
  *)
    echo 'Uso: ./limpiar-vagrant.sh [--si]' >&2
    exit 2
    ;;
esac

vagrant destroy -f default
echo '[OK] VM eliminada. Para reconstruirla: vagrant up --provider=virtualbox'
