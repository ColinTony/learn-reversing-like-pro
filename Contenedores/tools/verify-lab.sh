#!/usr/bin/env bash
# Ejecutar como usuario normal DENTRO de la VM.
set -Eeuo pipefail
pass() { printf '[OK] %s\n' "$*"; }
fail() { printf '[FALLO] %s\n' "$*" >&2; exit 1; }

[[ "$(getconf LONG_BIT)" == 32 ]] || fail 'El kernel no es de 32 bits'
uname -m | grep -Eq '^i[3-6]86$' || fail "Kernel incorrecto: $(uname -m)"
pass "Kernel i386: $(uname -m), $(uname -r)"

for cmd in gcc gdb readelf file python3 r2; do
  command -v "$cmd" >/dev/null || fail "Falta $cmd"
done
python3 -c 'import pwn' || fail 'Falta pwntools'
pass 'Herramientas instaladas'

BIN=/opt/protostar/bin/stack0
[[ -x "$BIN" ]] || fail "No existe $BIN"
file "$BIN" | grep -q 'ELF 32-bit' || fail 'stack0 no es ELF de 32 bits'
stat -c %a "$BIN" | grep -Eq '^[2467][0-7]{3}$' || fail 'stack0 no tiene SUID'
[[ "$(stat -c %u "$BIN")" == 0 ]] || fail 'stack0 no pertenece a root'
pass 'stack0 ELF32 y SUID root en filesystem invitado'

TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT
printf 'abc\n' | "$BIN" > "$TMP/stack0.out" 2>&1 || fail 'stack0 no se ejecuta'
pass 'stack0 se ejecuta sin modificar el binario'

cat > "$TMP/check.c" <<'C'
#include <stdio.h>
#include <sys/ptrace.h>
int main(void) {
  if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1) { perror("ptrace"); return 1; }
  puts("ptrace OK");
  return 0;
}
C
gcc -O0 -g -fno-pie -no-pie "$TMP/check.c" -o "$TMP/check"
"$TMP/check" | grep -q 'ptrace OK' || fail 'ptrace(PTRACE_TRACEME) falló'
pass 'ptrace(PTRACE_TRACEME) funciona'

cat > "$TMP/debug.c" <<'C'
#include <stdio.h>
int main(void) { puts("debug OK"); return 0; }
C
gcc -O0 -g -fno-pie -no-pie "$TMP/debug.c" -o "$TMP/debug"
gdb -q -nx -batch \
  -ex 'set pagination off' -ex 'set disable-randomization off' \
  -ex 'break main' -ex run -ex 'info registers eip' \
  --args "$TMP/debug" > "$TMP/gdb.out" 2>&1 || { cat "$TMP/gdb.out"; fail 'GDB terminó con error'; }
grep -q 'Breakpoint 1,' "$TMP/gdb.out" || { cat "$TMP/gdb.out"; fail 'GDB no detuvo en main'; }
grep -Eq '(^|[[:space:]])eip[[:space:]]' "$TMP/gdb.out" || fail 'GDB no mostró EIP'
pass 'GDB + breakpoint + registro EIP'

sysctl kernel.randomize_va_space
command -v setarch >/dev/null && setarch i386 -R /bin/true && pass 'setarch i386 -R funciona en el invitado'
pass 'Pruebas mínimas superadas; no se modificó ASLR del host'
