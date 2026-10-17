// exec
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char *const cmd[] = { "ls", "-l", NULL };
    printf("Mi pid es %d\n", getpid());
    execvp(cmd[0], cmd);
    printf("Este codigo no se ejecuta\n");
}