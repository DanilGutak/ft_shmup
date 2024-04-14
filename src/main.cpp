#include "Game.hpp"
#include "Enemy.hpp"
#include "Background.hpp"
#include <cstdlib>
#include <cmath>

int max_y, max_x;
long score = 0;
void print_passed_time(int start_time) {
    int passed_time = time(NULL) - start_time;
    mvprintw(max_y - 1, max_x - 50, "Time: %d yr. %d mo. %d wk. %d d. %d h. %d min. %d sec.", passed_time / 525960, passed_time / 43200, passed_time / 10080, passed_time / 1440, passed_time / 360, passed_time / 60, passed_time % 60);
}

void print_health(int hp) {
    for (int i = 0; i < hp; i++) {
        mvprintw((max_y / 2) + i , 0,"🧡");
    }
}

int resize_flag = 0;
void handle_resize(int sig) {
    sig = 0;
    resize_flag = 1;
}

void create_enemies(std::vector<Enemy> &enemies) {
    int i = 2;
    while (i < max_x - 2) {
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
void move_enemies(std::vector<Enemy> &enemies, std::vector<Bullet> &bullets) {
    for (unsigned int i = 0; i < enemies.size(); i++) {
        enemies[i].move();
		if (score % 100 == 0)
		enemies[i].shoot(bullets);
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

void check_for_enemy_hit_player(std::vector<Enemy> &enemies, Player &player, int score) {
	for (unsigned long i = 0; i < enemies.size(); i++) {
		if (player.check_collision(enemies[i].getX(), enemies[i].getY()) == true && (score - player.get_score() > 1100000)) {
			player.looseHP();
			player.setInvincible(true);
			player.set_score(score);
			// enemies.erase(enemies.begin() + i);
		}
	}
	if (score - player.get_score() > 1500000) {
		player.setInvincible(false);
	}
}
void check_for_bullet_hit_player(std::vector<Bullet> &bullets, Player &player) {
	for (unsigned long i = 0; i < bullets.size(); i++) {
		if (player.check_collision(bullets[i].getX(), bullets[i].getY()) == true  && (score - player.get_score() > 1100000)) {
			player.looseHP();
			player.setInvincible(true);
			player.set_score(score);
			// bullets.erase(bullets.begin() + i);
		}
	}
	if (score - player.get_score() > 1500000) {
		player.setInvincible(false);
	
}
}

void print_boder() {
	wattron(stdscr, COLOR_PAIR(1));
	wborder(stdscr, '|', '|', '-', '-', '*', '*', '*', '*');
	wattroff(stdscr, COLOR_PAIR(1));
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
    init_pair(1, COLOR_RED, COLOR_WHITE);
    curs_set(0);
	raw();
    nodelay(stdscr, TRUE);

	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	 // White on white

    bkgd(COLOR_PAIR(2));
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
    long difficulty = 400000;
	long ndifficulty = difficulty;
	player.set_score(score);
    while (1 && player.getHP() > 0) {
        
        int ch = getch();
		if (ch != -1) {
			ch1 = ch;
		}
		if (score % difficulty == 0)
		{
			werase(stdscr);
			refresh();
			if (enemies.size() < 10)
				create_enemies(enemies);
			move_backgrounds(backgrounds);
			move_enemies(enemies, bullets);
			print_boder();
			mvprintw(player.getY(), player.getX(), "🚀");
			for (int i = 0; i < max_y; i++) {
				mvprintw(i, 1, " ");
				mvprintw(i, max_x - 2, " ");

			}
			print_passed_time(start_time);
			check_for_enemy_hit_player(enemies, player, score);
			print_health(player.getHP());
            mvprintw(1, 1, "Score: %ld", score);
			mvprintw(2, 1, "diff: %ld", ndifficulty);

			if (ch1 == 'w' || ch1 == 'a' || ch1 == 's' || ch1 == 'd') {
				player.move(ch1);
                ch1 = '1';
            }
			if (ch1 == 'q' || resize_flag) {
				break;
			}
			if (ch1 ==' ' && player.getY() > 1) {
				shoot_bullet(bullets, player.getX(), player.getY() - 1, "player");
			    ch1 = '1';
			}
			attron(COLOR_PAIR(1)); // Change color to red

			for (unsigned long i = 0; i < bullets.size(); i++) {
				if (bullets[i].getY() <= 0 || bullets[i].getY() > max_y - 1){
					bullets.erase(bullets.begin() + i);
				}
				// if (i >= bullets.size()) {
				// 	break;
				// }
				check_for_bullet_hit_player(bullets, player);
				for (unsigned long j = 0; j < enemies.size(); j++) {
					if (bullets[i].check_collision(enemies[j].getX(), enemies[j].getY())) {
						if (enemies[j].getType() != 3) {
							enemies.erase(enemies.begin() + j);
						}
						bullets.erase(bullets.begin() + i);
						break;
					}
				}
				
				if (i >= bullets.size()) {
					break;
				}
				bullets[i].print();
				bullets[i].move();
            }
			attroff(COLOR_PAIR(1));
            ndifficulty = std::max(1L, static_cast<long>(difficulty * exp(-0.000000005 * score)));
		}
        // wbkgd(stdscr, COLOR_PAIR(1));
		score++;
    }
    // End ncurses mode
    endwin();
    if (resize_flag == 1) {
        std::cerr << RED << "Resized! Don't do it again....." << RESET <<std::endl;
    }
	if (player.getHP() <= 0) {
        std::cerr << RED << "Game Over!" << RESET << std::endl;
    }
    return 0;
}

