#include "../inc/Game.hpp"


void print_passed_time(int start_time) {
    int passed_time = time(NULL) - start_time;
    mvprintw(LINES - 1, COLS - 20, "Time: %d min. %d sec.", passed_time / 60, passed_time % 60);
}

void print_health(int hp) {
    for (int i = 0; i < hp; i++) {
        mvprintw(LINES - 1, i + 1, "H");
    }
}

int resize_flag = 0;
void handle_resize(int sig) {
    sig = 0;
    resize_flag = 1;
}
int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    start_color();
    noecho();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    curs_set(0);
    nodelay(stdscr, TRUE);
    int max_y, max_x;
    int start_time = time(NULL);
    getmaxyx(stdscr, max_y, max_x);
    if (max_y < 20 || max_x < 36) {
        endwin();
        std::cerr << RED << "Terminal too small! Please resize to at least 36x20" << RESET << std::endl;
        return 1;
    }
    Player player(max_x / 2, max_y - 2);
    std::vector<Bullet> bullets;
    signal(SIGWINCH, handle_resize);
    while (1) {
        
        // wbkgd(stdscr, COLOR_PAIR(1));
        wattron(stdscr, COLOR_PAIR(1));
        wborder(stdscr, '|', '|', '-', '-', '*', '*', '*', '*');
        wattroff(stdscr, COLOR_PAIR(1));
        // print x and y on the screen
        // mvprintw(0, 0, "x: %d, y: %d", max_x, max_y);
        mvprintw(player.getY(), player.getX(), PLAYER_SYMBOL);
        print_passed_time(start_time);
        print_health(player.getHP());
        int ch = getch();
        player.move(ch);
        if (ch == 'q' || resize_flag) {
            break;
        }
        if (ch ==' ') {
			shoot_bullet(bullets, player.getX(), player.getY() - 1);
        }
        // if (resize_flag) {
        //     break;
        // }
        for (unsigned long i = 0; i < bullets.size(); i++) {
            bullets[i].move();
            if (bullets[i].getY() < 0) {
                bullets.erase(bullets.begin() + i);
            }
            bullets[i].print();
        }
        wrefresh(stdscr);
        
        refresh();
        usleep(10000);
    }
    // End ncurses mode
    endwin();
    if (resize_flag == 1) {
        std::cerr << RED << "Resized! Don't do it again....." << RESET <<std::endl;
    }
    return 0;
}

