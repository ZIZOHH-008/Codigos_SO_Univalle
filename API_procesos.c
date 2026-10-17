// api de procesos completa
pid_t pid = fork();

if (pid == 0) {
    execvp(args[0], args);
    perror("execvp");
} else {
    wait(NULL);
}