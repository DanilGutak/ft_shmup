#include "Game.hpp"



int resize_flag = 0;
void handle_resize(int sig) {
    sig = 0;
    resize_flag = 1;
}
int main() {
    // Initialize ncurses

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    if (max_y < 20 || max_x < 36) {
        endwin();
        std::cerr << RED << "Terminal too small! Please resize to at least 80x24" << RESET << std::endl;
        return 1;
    }
    Player player(max_x, max_y);
    signal(SIGWINCH, handle_resize);
    while (1) {
        
        // print x and y on the screen
        mvprintw(0, 0, "x: %d, y: %d", max_x, max_y);
        int ch = getch();
        if (ch == 'q') {
            break;
        }
        if (resize_flag) {
            break;
        }
        refresh();
    }
    // End ncurses mode
    endwin();
    if (resize_flag == 1) {
        std::cerr << RED << "Resized! Don't do it again....." << RESET <<std::endl;
    }
    return 0;
}

