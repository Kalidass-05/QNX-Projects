#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    printf("Parent PID = %d\n", getpid());

    pid = spawnl(P_WAIT, "./child", "child", NULL);

    if(pid == -1)
    {
        perror("spawnl");
        return 1;
    }

    printf("Child PID = %d\n", pid);

    waitpid(pid, &status, 0);

    if(WIFEXITED(status))
    {
        printf("Child exited normally\n");
        printf("Exit status = %d\n", WEXITSTATUS(status));
    }

    printf("Parent exiting\n");

    return 0;
}
