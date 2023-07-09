#include <ncurses.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>

int draw_home();
void draw_game();
void draw_game_board(WINDOW *win);
void draw_game_stats(WINDOW *win, int iteration);

WINDOW *create_win(int startx, int starty, int lines, int columns);
void destroy_win(WINDOW *win);

int main() {	
	initscr();
    raw(); // Disable user input buffering
    noecho(); // Prevents user input from echoing to output
    setlocale(LC_ALL, "");

    // Enable color
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);

    if (draw_home() == 0) {
        draw_game();
    }

	endwin(); // End curses mode
	
    return EXIT_SUCCESS;
}

// Draw functions

int draw_home() {
    WINDOW *win = create_win(0, 0, LINES, COLS);

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

    int ch;
    while (TRUE) {
        int ch = wgetch(win);
        if (ch == '\n') {
            wmove(win, ++y, x);
            wprintw(win, "Starting...");
            wrefresh(win);
            sleep(1);
            destroy_win(win);
            return 0;
        } else {
            wmove(win, ++y, x);
            wprintw(win, "Bye...");
            wrefresh(win);
            sleep(1);
            destroy_win(win);
            return 1;
        }
    }
}

void draw_game() {
    WINDOW *win = create_win(0, 0, LINES, COLS);

    draw_game_stats(win, 1234);

    wrefresh(win);
    wgetch(win);

    destroy_win(win);
}

void draw_game_board(WINDOW *win) {

}

void draw_game_stats(WINDOW *win, int iteration) {
    int win_height, win_width;
    getmaxyx(win, win_height, win_width);

    mvwaddch(win, win_height-3, 0, ACS_LTEE); // Create left tee on border
    mvwhline(win, win_height-3, 1, ACS_HLINE, win_width-2); // Create line
    mvwaddch(win, win_height-3, win_width-1, ACS_RTEE);  // Create right tee on border
    mvwprintw(win, win_height-2, 2, "Iteration: %d", iteration);

    char *string = "Press R to restart";
    int starty = win_width - 2 - strlen(string);
    mvwprintw(win, win_height-2, starty, string);
}

// Utility functions

WINDOW *create_win(int startx, int starty, int lines, int columns) {
    WINDOW *win = newwin(lines, columns, starty, startx);
    box(win, 0, 0);
    keypad(win, TRUE); // Allows function keys on default window "stdscr"
    wrefresh(win);

    return win;
}

void destroy_win(WINDOW *win) {
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
}