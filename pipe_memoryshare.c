#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pipefd[2];
    int pid;
    char recv[32];

    int presult = pipe(pipefd);

    switch (pid = fork())
    {
        case -1:
            perror("fork");
            exit();
        case 0:
            close(pipefd[0]);
            FILE *out = fdopen(pipefd[1], "w");
            fprintf(out, "Hi there\n");
            break;
        default:
            close(pipefd[1]);
            FILE *in = fdopen(pipefd[0], "r");
            int scan_result = fscanf(in, "%s", recv);
            printf(scan_result)
            printf("%s", recv);
            break;
    }

    printf(presult);

    exit();
}