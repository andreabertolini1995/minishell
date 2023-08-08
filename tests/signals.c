#include <stdio.h>
#include <signal.h>

void sigint_handler(int signo) {
    printf("\nCaught SIGINT\n");
}

int main() {
    // signal(SIGINT, sigint_handler);
    signal(SIGINT, SIG_IGN);
    while (1);                  /* Infinite loop */
}