#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_HIJOS 10

int main(int argc, char *argv[]) {
    int i, j;
    pid_t pid, nuevo, nuevo1;
    pid_t hijos[MAX_HIJOS];
    int tipo[MAX_HIJOS];       // 1 = xload, 2 = kcalc
    time_t inicio[MAX_HIJOS];
    time_t ini_total, fin_total;
    int cantidad = 0;
    int estado;

    ini_total = time(NULL);

    for (i = 0; i < 2; i++) {
        pid = getpid();

        for (j = 0; j < i + 2; j++) {

            /* Crear hijo que ejecutará kcalc */
            time_t inicio_kcalc = time(NULL);

            nuevo = fork();

            if (nuevo == 0) {
                break;
            }

            hijos[cantidad] = nuevo;
            tipo[cantidad] = 2;
            inicio[cantidad] = inicio_kcalc;
            cantidad++;

            /* Crear hijo que ejecutará xload */
            time_t inicio_xload = time(NULL);

            nuevo1 = fork();

            if (nuevo1 == 0) {
                printf("Soy XLOAD - PID: %d - Padre: %d\n",
                       getpid(), getppid());

                execlp("xload", "xload", NULL);

                perror("Error al ejecutar xload");
                exit(1);
            }

            hijos[cantidad] = nuevo1;
            tipo[cantidad] = 1;
            inicio[cantidad] = inicio_xload;
            cantidad++;
        }

        if (pid != getpid()) {
            printf("Soy KCALC - PID: %d - Padre: %d\n",
                   getpid(), getppid());

            execlp("kcalc", "kcalc", NULL);

            perror("Error al ejecutar kcalc");
            exit(1);
        }
    }

    /* Esperar a todos los hijos */
    for (i = 0; i < cantidad; i++) {
        pid_t terminado = wait(&estado);
        time_t fin_hijo = time(NULL);

        for (j = 0; j < cantidad; j++) {
            if (hijos[j] == terminado) {
                if (tipo[j] == 1) {
                    printf("XLOAD - PID %d - Tiempo: %ld segundos\n",
                           terminado, fin_hijo - inicio[j]);
                } else {
                    printf("KCALC - PID %d - Tiempo: %ld segundos\n",
                           terminado, fin_hijo - inicio[j]);
                }
                break;
            }
        }
    }

    fin_total = time(NULL);

    printf("Tiempo total de ejecucion: %ld segundos\n",
           fin_total - ini_total);

    return 0;
}