#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

int main() {
    // Initialize the curses library
    initscr();
    start_color(); // Enable color support if available
    init_pair(1, COLOR_RED, COLOR_BLACK); // Define a color pair

    // Get terminal capabilities
    if (tgetent(NULL, getenv("TERM")) <= 0) {
        fprintf(stderr, "Could not access terminal database\n");
        endwin(); // End curses mode
        exit(1);
    }

    // Get terminal dimensions
    int cols = tgetnum("cols");
    int lines = tgetnum("lines");

    // Move the cursor and change color
    tputs(tgoto(tgetstr("cm", NULL), cols / 2, lines / 2), 1, putchar); // Move cursor to center
    tputs(tgetstr("so", NULL), 1, putchar); // Start standout mode (usually changes text color)
    printf("Hello, Curses!"); // Print text with changed color
    tputs(tgetstr("se", NULL), 1, putchar); // End standout mode (reset text color)
    refresh(); // Refresh the screen

    getch(); // Wait for user input

    // Clean up and end curses mode
    endwin();

    return 0;
}
