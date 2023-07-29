#include <stdio.h>
#include <stdlib.h>

extern char** environ;

// int main() {
//     // Traverse the environment variables using the "environ" global variable
//     char** env = environ;

//     while (*env != NULL) {
//         printf("%s\n", *env);
//         env++;
//     }

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    const char* filename = "/etc/profile"; // Replace with the actual path to your environment file
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the buffer
        printf("%s", buffer);
    }

    if (bytesRead == -1) {
        perror("Error reading file");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}

