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
	int i = 0;
	while (i < hp){
        mvprintw((max_y / 3) + i , 0,"💟");
		i++;
	}
	while (i < 10) {
		mvprintw((max_y / 3) + i , 0,"💔");
		i++;
	}
}

int resize_flag = 0;
void handle_resize(int sig) {
    sig = 0;
    resize_flag = 1;
}

void create_enemies(std::vector<Enemy> &enemies, int number) {
    int i = 4;
    while (i < max_x - 2) {
		// 1 - normal, 2 - diagonal, 3 - bomb, 4 - shooter
		// chanses 1 - 40%, 2 - 30%, 3 - 10%, 4 - 20%
		int type = rand() % 10;
		if (type < 4)
			enemies.push_back(Enemy(i,(rand() % max_y) * -1, 1));
		else if (type < 7)
			enemies.push_back(Enemy(i,(rand() % max_y) * -1, 2));
		else if (type < 8)
			enemies.push_back(Enemy(i,(rand() % max_y) * -1, 3));
		else
			enemies.push_back(Enemy(i,(rand() % max_y) * -1, 4));
		i += max_x / number;
    }
}
void move_enemies(std::vector<Enemy> &enemies, std::vector<Bullet> &bullets) {
    for (unsigned int i = 0; i < enemies.size(); i++) {
        enemies[i].move();
		if (rand()%9 == 0)
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
		if (enemies[i].getType() == 3){
			// check in 3x3 area
			for (int j = -1; j < 2; j++) {
				for (int k = -1; k < 2; k++) {
					if (player.check_collision(enemies[i].getX() + k, enemies[i].getY() + j) == true && (score - player.get_score() > 1100000)) {
						player.looseHP();
						player.setInvincible(true);
						player.set_score(score);
						// enemies.erase(enemies.begin() + i);
					}
				}
			}
		}
		else if (player.check_collision(enemies[i].getX(), enemies[i].getY()) == true && (score - player.get_score() > 1100000)) {
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
	init_pair(3, COLOR_WHITE, COLOR_WHITE);
	 // White on white

    bkgd(COLOR_PAIR(2));
    int start_time = time(NULL);
	int kills = 0;
    getmaxyx(stdscr, max_y, max_x);
    if (max_y < 20 || max_x < 100) {
        endwin();
        std::cerr << RED << "Terminal too small! Please resize to at least 100x20" << RESET << std::endl;
        return 1;
    }
    Player player(max_x / 2, max_y - 2);
    std::vector<Bullet> bullets;
    signal(SIGWINCH, handle_resize);
    std::vector<Enemy> enemies;
	std::vector<Background> backgrounds;
    create_enemies(enemies, max_y * max_x / 200);
	create_backgrounds(backgrounds);
	int ch1 = '1';
    long difficulty = 400000;
	long ndifficulty = difficulty;
	player.set_score(score);
	long real_score = 0;
	int ammo = 20;
    while (1 && player.getHP() > 0) {
        
        int ch = getch();
		if (ch != -1) {
			ch1 = ch;
		}
		if (score % ndifficulty == 0)
		{
			if (rand() % 50 == 0 && ammo < 20)
				ammo++;
			werase(stdscr);
			refresh();
			move_backgrounds(backgrounds);
			move_enemies(enemies, bullets);
			print_boder();
			if (player.getInvincible() == true)
				mvprintw(player.getY(), player.getX(), "🛡");
			else
				mvprintw(player.getY(), player.getX(), "🚀");
			for (int i = 0; i < max_y; i++) {
				mvprintw(i, 1, " ");
				mvprintw(i, max_x - 2, " ");

			}
			print_passed_time(start_time);
			check_for_enemy_hit_player(enemies, player, score);
			print_health(player.getHP());
            mvprintw(0, 3, "Score: %ld", real_score/100000);
			mvprintw(0, 85, "Kills: %d", kills);
			mvprintw(0, 65, "Ammo: %d", ammo);
			if (ndifficulty > 300000)
				mvprintw(0, 30, "Difficulty: Easy");
			else if (ndifficulty > 200000)
				mvprintw(0, 30, "Difficulty: Normal");
			else if (ndifficulty > 150000)
				mvprintw(0, 30, "Difficulty: Hard");
			else
				mvprintw(0, 30, "Difficulty: Insane");

			player.move(ch1);
			if (ch1 == 'w' || ch1 == 'a' || ch1 == 's' || ch1 == 'd') {
                ch1 = '1';
            }
			if (ch1 == 'q' || resize_flag) {
				break;
			}
			if (ch1 ==' ' && player.getY() > 1 && ammo > 0) {
				shoot_bullet(bullets, player.getX(), player.getY() - 1, "player");
			    ch1 = '1';
				ammo--;
			}
			attron(COLOR_PAIR(1)); // Change color to red
			for (unsigned long i = 0; i < bullets.size(); i++) {
				if (bullets[i].getY() <= 0 || bullets[i].getY() > max_y - 1){
					bullets.erase(bullets.begin() + i);
				}
				if (i >= bullets.size()) {
					break;
				}
				check_for_bullet_hit_player(bullets, player);
				for (unsigned long j = 0; j < enemies.size(); j++) {
					if (bullets[i].check_collision(enemies[j].getX(), enemies[j].getY())) {
						if (enemies[j].getType() != 3 && bullets[i].who_shot == "player") {
							real_score += enemies[j].getType() * 10000000;
							// if (bullet.get_who_shot() == "player")
							// 	kills++;
							kills++;
							enemies.erase(enemies.begin() + j);
							create_enemies(enemies, 1);
							bullets.erase(bullets.begin() + i);
						}
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
			if (ch1 == 'p') {
				while (getch() != 'p' || resize_flag == 1) {
					mvprintw(max_y/3, max_x/2, "Paused");
				}
				ch1 = '1';
			}
		}
		score++;
		real_score++;
    }
    // End ncurses mode
	if (resize_flag == 1) {
        std::cerr << RED << "Resized! Don't do it again....." << RESET <<std::endl;
    }
	else
	{
		clear();
		if (player.getHP() == 0)
			mvprintw(max_y / 2, max_x / 3, "Game Over!");
		else if (player.getHP() > 0)
			mvprintw(max_y / 2, max_x / 3, "You Quit! Why?!");
		mvprintw(max_y / 2 + 1, max_x / 3, "Score: %ld", real_score/100000);
		mvprintw(max_y / 2 + 2, max_x / 3, "Kills: %d", kills);
		if (ndifficulty > 300000)
			mvprintw(max_y / 2 + 3, max_x / 3, "Difficulty: Easy");
		else if (ndifficulty > 200000)
			mvprintw(max_y / 2 + 3, max_x / 3, "Difficulty: Normal");
		else if (ndifficulty > 150000)
			mvprintw(max_y / 2 + 3, max_x / 3, "Difficulty: Hard");
		else
			mvprintw(max_y / 2 + 3, max_x / 3, "Difficulty: Insane");

		mvprintw(max_y / 2 + 4, max_x / 3, "Press q to exit");
		mvprintw(max_y / 2 + 5, max_x / 3, "Press r to restart");
		print_boder();
		while(1)
		{
			int ch = getch();
			if (ch == 'q' || ch == 'Q') {
				break;}
			else if (ch == 'r' || ch == 'R') {
				system("clear");
				system("make run");
				break;
			}
			
		}
	}
	endwin();
    return 0;
}

