#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    int i, j;
    pid_t pid;

    pid=fork();

    if(pid==0)
    {
        printf("SOY EL PROCESO HIJO:%d (PROCESOS) Y MI PADRE ES:%d\n",
               getpid(),getppid());

        execlp ("ps", "ps", NULL);
        exit(0);
    }
    else
    {
        pid=fork();

        if(pid==0)
        {
            printf("SOY EL PROCESO HIJO: %d (ESPACIO EN DISCO) Y MI PADRE ES:%d\n",
                   getpid(),getppid());

            execlp ("df","df","-h", NULL);
            exit(0);
        }
        else
        {
            printf("SOY EL PROCESO PADRE:%d (LS) Y MI PADRE ES:%d\n",
                   getpid(),getppid());

            execlp("ls","ls","-l",NULL);
            wait(NULL);
        }
    }

    wait(NULL);
    return 0;
}