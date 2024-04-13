#include "../inc/Game.hpp"

void shoot_bullet(std::vector<Bullet> &bullets, int x, int y)
{
	bullets.push_back(Bullet(x, y, "player"));
	mvprintw(y, x, "|");
}

void Bullet::print()
{
	if (y > 0)
		mvprintw(y, x, "|");
	mvprintw(y + 1, x, " ");
}

void Bullet::move()
{
	if (this->who_shot == "player")
		y--;
	else
		y++;
}

int Bullet::getX()
{
	return x;
}

int Bullet::getY()
{
	return y;
}

bool Bullet::check_collision(int x, int y) //if bullet is at x, y return true
{
	if (this->x == x && this->y == y)
		return true;
	return false;
}
