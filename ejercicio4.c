#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int num;
    int n = 3;
    pid_t nuevo;

    for (num = 1; num <= n; num++) {
        nuevo = fork();

        if ((num == n) && (nuevo == 0))
            execlp("ls", "ls", "-l", NULL);
    }

    return 0;
}