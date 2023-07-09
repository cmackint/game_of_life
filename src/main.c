#include <ncurses.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>


int start_screen() {
    WINDOW *win = newwin(LINES, COLS, 0, 0);
    keypad(win, TRUE); // Allows function keys on default window "stdscr"

    int x = COLS / 2;
    int y = LINES / 2;
    wmove(win, y, x);
    wattron(win, A_BOLD);
    wprintw(win, "The Game of Life");
    wattroff(win, A_BOLD);

    wmove(win, ++y, x -= 1);
    wprintw(win, "Created by ");
    wattron(win, COLOR_PAIR(1));
    wchar_t flower[] = {L'\u273F', ' ', 'C', 'a', 'm', ' ', L'\u273F', '\0'};
    waddwstr(win, flower);
    wattroff(win, COLOR_PAIR(1));

    wmove(win, y += 2, x -= 1);
    wattron(win, A_DIM);
    wprintw(win, "Press Enter to start...");
    wattroff(win, A_DIM);

	int ch = wgetch(win);
    if (ch == '\n') {
        wmove(win, ++y, x);
        wprintw(win, "Starting...");
    } else {
        wmove(win, ++y, x);
        wprintw(win, "Bye...");
    }

	wrefresh(win); // Print to terminal
    wgetch(win); // Wait for user input 
}

int main() {	
	initscr();
    raw(); // Disable user input buffering
    noecho(); // Prevents user input from echoing to output
    setlocale(LC_ALL, "");

    // Enable color
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    start_screen();

	endwin(); // End curses mode
	
    return EXIT_SUCCESS;
}
