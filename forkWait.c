// wait+fork
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("antes pid=%d\n", getpid());
    pid_t rc = fork();
    int x = 1;
    if (rc == 0) {
        x += 5;
        printf("hijo pid=%d y x=%d\n", getpid(), x);
    } else {
        x += 2;
        wait(NULL);
        printf("padre pid=%d hijo=%d x=%d\n", getpid(), rc, x);
    }
    printf("[%d] x=%d\n", getpid(), x);
}