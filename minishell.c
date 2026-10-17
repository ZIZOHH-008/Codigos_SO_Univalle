#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 100 // Tamaño máximo en caracteres de la entrada del usuario
#define MAX_ARGS 10  // Cantidad máxima de comandos y argumentos permitidos

int main(void) {
    char linea[MAX_LINE]; // Arreglo para almacenar la línea de texto completa
    char *args[MAX_ARGS]; // Arreglo de punteros para almacenar cada palabra (comando y argumentos)

    while (1) { // Bucle infinito que mantiene la shell activa esperando entradas
        printf("> ");
        if (fgets(linea, sizeof(linea), stdin) == NULL) { // stdin standard input (Lee la entrada del usuario)
            break; // Termina la shell si se detecta un error o un EOF (como presionar Ctrl+D)
        }

        linea[strcspn(linea, "\n")] = '\0'; // Encuentra el salto de línea ('\n') y lo cambia por el fin de cadena ('\0')

        if (linea[0] == '\0') { // Si el usuario presionó solo Enter, la línea está vacía
            continue; // Vuelve al inicio del while para volver a mostrar el prompt
        }

        int i = 0;
        char *token = strtok(linea, " "); // Extrae la primera palabra hasta encontrar un espacio
        while (token != NULL && i < MAX_ARGS - 1) { // Mientras queden palabras y no se exceda el límite de argumentos
            args[i] = token; // Guarda el puntero de la palabra en el arreglo
            i++;
            token = strtok(NULL, " "); // Continúa extrayendo palabras de la misma línea original
        }
        args[i] = NULL; // Marca el final del arreglo, requisito obligatorio para que execvp funcione

        if (strcmp(args[0], "salir") == 0) { // Comprueba si la primera palabra es un comando interno de salida
            printf("Gracias por usar mini shell\n");
            break; // Rompe el ciclo while infinito, terminando el programa padre
        }

        pid_t pid = fork(); // Crea un nuevo proceso hijo. Devuelve 0 al hijo y el PID del hijo al padre[cite: 1, 2]

        if (pid < 0) { // Si devuelve un número negativo, falló la creación del proceso[cite: 2]
            perror("fork");
            exit(1);
        }

        if (pid == 0) { // Bloque de código que únicamente ejecuta el proceso hijo[cite: 1, 2]
            execvp(args[0], args); // Reemplaza la imagen del proceso actual (el hijo) para cargar y ejecutar el nuevo comando[cite: 1, 2]
            perror("execvp"); // Esta línea solo se ejecuta si execvp falla (un exec exitoso jamás retorna)[cite: 1, 2]
            exit(1); // Finaliza el hijo con un código de error si el comando no se pudo ejecutar
        }

        wait(NULL); // Código que ejecuta el padre. Pausa su ejecución hasta que el comando del hijo finalice[cite: 1, 2]
    }

    return 0;
}
