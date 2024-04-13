#include "../inc/Game.hpp"
#include "../inc/Player.hpp"


void Player::move(int key) {
	switch (key) {
		case 'w':
			if (y > 1) {
				y--;
				mvprintw(y + 1, x, " ");
			}
			break;
		case 's':
			if (y < LINES - 2) {
				y++;
				mvprintw(y - 1, x, " ");
			}
			break;
		case 'a':
			if (x > 1) {
				x--;
				mvprintw(y, x + 1, " ");
			}
			break;
		case 'd':
			if (x < COLS - 2) {
				x++;
				mvprintw(y, x - 1, " ");
			}
			break;
	}
}

bool Player::check_collision(int x, int y) {
	if (this->x == x && this->y == y) {
		this->hp -= 1;
		return true;
	}
	return false;
}

int Player::getX() {
	return x;
}


int Player::getY() {
	return y;
}

int Player::getHP() {
	return hp;
}
