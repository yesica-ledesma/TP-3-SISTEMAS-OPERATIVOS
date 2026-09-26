#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, j;
    pid_t pid, nuevo;

    for (i = 0; i < 2; i++) {
        pid = getpid();

        for (j = 0; j < i + 2; j++) {
            nuevo = fork(); /* 1 */

            if (nuevo != 0) {
                nuevo = fork(); /* 2 */
                break;
            }
        }

        if (pid != getpid())
            break;
    }

    printf("PID: %d - Padre: %d - i: %d - j: %d\n",
           getpid(), getppid(), i, j);

    return 0;
}