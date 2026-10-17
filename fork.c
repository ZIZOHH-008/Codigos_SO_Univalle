// fork
int x = 1;
pid_t rc = fork();

if (rc == 0) {
    x += 5;
    printf("hijo  x=%d\n", x);
} else {
    x += 2;
    printf("padre x=%d\n", x);
}