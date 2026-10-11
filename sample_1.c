
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    // pid_t parent = getpid();
    pid_t pid = fork();

    if (pid == -1)
    {
        // Error: failed to fork()
        perror("fork failed");
        return EXIT_FAILURE;
    }
    else if (pid > 0)
    {
        // Parent process
        int status;

        printf("Parent id: %d\n", (int)getpid());
        printf("Parent will be waiting for child to complete\n");

        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid failed");
            return EXIT_FAILURE;
        }

        printf("Child process completed\n");
    }
    else
    {
        // Child process
        printf("Child process 1 id: %d\n", (int)getpid());
        printf("Parent process 1 id: %d\n", (int)getppid());

        execl("/bin/ls", "ls", "-r", "-t", "-l", NULL);

        // Executed only if execl() fails
        perror("execl failed");
        _exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
