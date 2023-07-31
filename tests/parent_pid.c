#include <stdio.h>
#include <unistd.h>

int main() {
    int pid_pipe[2]; // File descriptors for the pipe

    if (pipe(pid_pipe) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process
        close(pid_pipe[1]); // Close the write end of the pipe in the child
        int parent_pid;
        read(pid_pipe[0], &parent_pid, sizeof(int)); // Read the parent's PID from the pipe
        close(pid_pipe[0]); // Close the read end of the pipe in the child

        printf("Child process: My PID = %d\n", getpid());
        printf("Child process: My parent's PID = %d\n", parent_pid);
    } else {
        // Parent process
        close(pid_pipe[0]); // Close the read end of the pipe in the parent
        write(pid_pipe[1], &pid, sizeof(int)); // Write the child's PID to the pipe
        close(pid_pipe[1]); // Close the write end of the pipe in the parent

        printf("Parent process: My PID = %d\n", getpid());
        printf("Parent process: My child's PID = %d\n", pid);
    }

    return 0;
}
