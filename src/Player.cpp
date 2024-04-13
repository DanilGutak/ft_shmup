#include "../inc/Game.hpp"
#include "../inc/Player.hpp"

#include <cstdlib>

void Player::move(int key) {
	switch (key) {
		case 'w':
			if (y > 1) {
				y--;
			}
			break;
		case 's':
			if (y < LINES - 2) {
				y++;
			}
			break;
		case 'a':
			if (x > 1) {
				x--;
			}
			break;
		case 'd':
			if (x < COLS - 2) {
				x++;
			}
			break;
	}
}

bool Player::check_collision(int x, int y) {
	if (abs(this->x - x) <= 1 && this->y == y) {
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

