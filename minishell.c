#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 100
#define MAX_ARGS 10

int main(void) {
	char linea[MAX_LINE];
	char *args[MAX_ARGS];

	while (1) {
		printf("> ");
		if (fgets(linea, sizeof(linea), stdin) == NULL) { // stdin standard input
			break;
		}

		linea[strcspn(linea, "\n")] = '\0';

		if (linea[0] == '\0') {
			continue;
		}

		int i = 0;
		char *token = strtok(linea, " ");
		while (token != NULL && i < MAX_ARGS - 1) {
			args[i] = token;
			i++;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		if (strcmp(args[0], "salir") == 0) {
			printf("Gracias por usar mini shell\n");
			break;
		}

		pid_t pid = fork();

		if (pid < 0) {
			perror("fork");
			exit(1);
		}

		if (pid == 0) {
			execvp(args[0], args);
			perror("execvp");
			exit(1);
		}

		wait(NULL);
	}

	return 0;
};