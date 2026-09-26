#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    int i, j;
    pid_t pid;

    pid=fork();

    if(pid!=0)
    {
        printf("SOY EL PROCESO PADRE:%d (PROCESOS) Y MI PADRE ES:%d\n",
               getpid(),getppid());

        wait(NULL);
        //execlp ("ps", "ps","-eaf", NULL);
    }
    else
    {
        pid=fork();

        if(pid!=0)
        {
            printf("SOY EL PROCESO HIJO: %d (ESPACIO EN DISCO) Y MI PADRE ES:%d\n",
                   getpid(),getppid());

            execlp ("df","df","-h", NULL);
            wait(NULL);
        }
        else
        {
            printf("SOY EL PROCESO HIJO:%d (LS) Y MI PADRE ES:%d\n",
                   getpid(),getppid());

            execlp("ls","ls","-l",NULL);
            exit(0);
        }
    }

    return 0;
}