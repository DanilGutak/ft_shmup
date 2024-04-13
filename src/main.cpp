#include "Game.hpp"
#include "Enemy.hpp"
#include "Background.hpp"
#include <cstdlib>

int max_y, max_x;
long score = 0;
int resize_flag = 0;
void handle_resize(int sig) {
    sig = 0;
    resize_flag = 1;
}

void create_enemies(std::vector<Enemy> &enemies) {
    int i = 0;
    while (i < max_x) {
		int type = rand() % 4 + 1;
		if (type == 1)
			enemies.push_back(Enemy(i,(rand() % max_y) * -1, 1));
		else if (type == 2)
			enemies.push_back(Enemy(i,(rand() % max_y) * -1, 2));
		else if (type == 3)
			enemies.push_back(Enemy(i,(rand() % max_y) * -1, 3));
		else if (type == 4)
			enemies.push_back(Enemy(i,(rand() % max_y) * -1, 4));
        i += max_x / 10;
    }
}
void move_enemies(std::vector<Enemy> &enemies) {
    for (unsigned int i = 0; i < enemies.size(); i++) {
        enemies[i].move();
    }
}
void move_backgrounds(std::vector<Background> &backgrounds) {
	for (unsigned int i = 0; i < backgrounds.size(); i++) {
		backgrounds[i].move();
	}
}
void create_backgrounds(std::vector<Background> &backgrounds) {
	std::string symbols[] = {"｡", "°", " ☆", "⋆"};
	for (int i = 0; i < max_x; i++) {
		for (int j = 0; j < max_y; j++) {
			int type = rand() % 200;
			if (type < 4)
				backgrounds.push_back(Background(i, j, symbols[type]));
		}
		
	}
}
int main() {
    // Initialize ncurses
    srand (time(NULL));
	setlocale(LC_ALL, "");
    initscr();
	keypad(stdscr, TRUE);
    cbreak();
    noecho();
    curs_set(0);
	raw();
    nodelay(stdscr, TRUE);
    getmaxyx(stdscr, max_y, max_x);
    if (max_y < 20 || max_x < 36) {
        endwin();
        std::cerr << RED << "Terminal too small! Please resize to at least 36x20" << RESET << std::endl;
        return 1;
    }
    signal(SIGWINCH, handle_resize);
    std::vector<Enemy> enemies;
	std::vector<Background> backgrounds;
    create_enemies(enemies);
	create_backgrounds(backgrounds);

    while (1) {
		werase(stdscr);
		clear();
		move_backgrounds(backgrounds);
		move_enemies(enemies);
        int ch1 = getch();
        int ch2 = getch();
        if (ch1 == 'q') {
            break;
        }
        if (resize_flag) {
            break;
        }
		mvprintw(2, 0, "Score: %ld", score);
        mvprintw(0, 0, "x: %d, y: %d, key1: %d,key2:%d", max_x, max_y, ch1, ch2);
        refresh();
		usleep(100000);
		score++;
    }
    // End ncurses mode
    endwin();
    if (resize_flag == 1) {
        std::cerr << RED << "Resized! Don't do it again....." << RESET <<std::endl;
    }
    return 0;
}

