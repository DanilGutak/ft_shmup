#include "../inc/Game.hpp"

#include <cstdlib>

void shoot_bullet(std::vector<Bullet> &bullets, int x, int y, std::string who_shot)
{
	bullets.push_back(Bullet(x, y, who_shot));
}

void Bullet::print()
{
	if (y > 0 && y < max_y -1)
	{
		if (this->who_shot == "player")
			mvprintw(y, x, "🠵");
		else
			mvprintw(y, x, "❚");
	}
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
	if (abs(this->x - x) <= 1 && this->y == y)
		return true;
	return false;
}
