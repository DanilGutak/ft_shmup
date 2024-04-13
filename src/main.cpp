#include "Game.hpp"
#include "Enemy.hpp"
#include "Background.hpp"
#include <cstdlib>

int max_y, max_x;
long score = 0;
void print_passed_time(int start_time) {
    int passed_time = time(NULL) - start_time;
    mvprintw(LINES - 1, COLS - 20, "Time: %d min. %d sec.", passed_time / 60, passed_time % 60);
}

void print_health(int hp) {
    // for (int i = 0; i < hp; i++) {
        mvprintw(LINES - 1, 1,"%d", hp);
    // }
}

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
    start_color();
    noecho();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    curs_set(0);
	raw();
    nodelay(stdscr, TRUE);
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
    std::vector<Enemy> enemies;
	std::vector<Background> backgrounds;
    create_enemies(enemies);
	create_backgrounds(backgrounds);
	int ch1 = '1';
    long diffulity = 300001;
    while (1) {
        
        int ch = getch();
		if (ch != -1) {
			ch1 = ch;
		}
		if (score % diffulity == 0)
		{
			werase(stdscr);
			refresh();
			move_backgrounds(backgrounds);
			move_enemies(enemies);
			wattron(stdscr, COLOR_PAIR(1));
			wborder(stdscr, '|', '|', '-', '-', '*', '*', '*', '*');
			wattroff(stdscr, COLOR_PAIR(1));
			// print x and y on the screen
			// mvprintw(0, 0, "x: %d, y: %d", max_x, max_y);
			mvprintw(player.getY(), player.getX(), PLAYER_SYMBOL);
			print_passed_time(start_time);
            for (unsigned long i = 0; i < enemies.size(); i++) {
                player.check_collision(enemies[i].getX(), enemies[i].getY());
            }
			print_health(player.getHP());
            mvprintw(1, 1, "Score: %ld", diffulity - 1);
            if (player.getHP() <= 9) {
                std::cerr << RED << "Game Over!" << RESET << std::endl;
                break;
            }
			if (ch1 == 'w' || ch1 == 'a' || ch1 == 's' || ch1 == 'd') {
				player.move(ch1);
                ch1 = '1';
            }
			if (ch1 == 'q' || resize_flag) {
				break;
			}
			if (ch1 ==' ') {
				shoot_bullet(bullets, player.getX(), player.getY() - 1);
			    ch1 = '1';
			}
			for (unsigned long i = 0; i < bullets.size(); i++) {
				bullets[i].move();
				if (bullets[i].getY() < 0) {
					bullets.erase(bullets.begin() + i);
				}
				bullets[i].print();
			refresh();
            }
            // diffulity -= 50;
		}
        // wbkgd(stdscr, COLOR_PAIR(1));
		score++;
    }
    // End ncurses mode
    endwin();
    if (resize_flag == 1) {
        std::cerr << RED << "Resized! Don't do it again....." << RESET <<std::endl;
    }
    return 0;
}

