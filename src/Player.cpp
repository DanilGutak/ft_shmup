#include "../inc/Game.hpp"
#include "../inc/Player.hpp"

#include <cstdlib>

void Player::move(int key) {
	static int time;

	if (key == 'w' || key == 's' || key == 'a' || key == 'd') {
		time++;
	}
	else {
		time = 0;
	}
	int speed = 1;
	if (time >5 ) {
		speed = 2;
	}
	if (time > 10) {
		speed = 3;
	}
	switch (key) {
		case 'w':
			if (y > 1) {
				y -= 1;
			}
			break;
		case 's':
			if (y < LINES - 2) {
				y+= 1;
			}
			break;
		case 'a':
			if (x > 2) {
				x-= 1;
			}
			break;
		case 'd':
			if (x < COLS - 2) {
				x+= 1;
			}
			break;
	}
}

bool Player::check_collision(int x, int y) {
	if (abs(this->x - x) <= 1 && this->y == y) {
		// this->hp -= 1;
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

void Player::looseHP() {
	hp--;
}

void Player::setInvincible(bool invincible) {
	this->invincible = invincible;
}

void Player::set_score(int score) {
	this->score = score;
}

int Player::get_score() {
	return score;
}

bool Player::getInvincible() {
	return invincible;
}