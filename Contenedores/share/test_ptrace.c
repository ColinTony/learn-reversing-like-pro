#include <sys/ptrace.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) {
        printf("ptrace failed: %s\n", strerror(errno));
        return 1;
    }
    printf("ptrace succeeded\n");
    return 0;
}
