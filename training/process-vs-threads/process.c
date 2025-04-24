#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main()
{
    pid_t pid = fork();
    if (pid == -1) return 1;
    printf("Process id: %d\n", getpid());
    if (pid != 0)
        wait(NULL);
    
    return 0;
}