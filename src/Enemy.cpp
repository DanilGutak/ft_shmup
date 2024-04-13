#include "Enemy.hpp"
#include <ncurses.h>
#include <cstdlib>

Enemy::Enemy(int x, int y, int type) : x(x), y(y), type(type), status(1){
    //draw enemy
    if (type == 1)
    {
        this->setSymbol("🗿");
        mvprintw(y, x, "%s", this->getSymbol().c_str());
    }
    else if (type == 2)
    {
        this->setSymbol("🗡️");
        mvprintw(y, x, "%s", this->getSymbol().c_str());
    }
    else if (type == 3)
    {
        this->setSymbol("💣");
        mvprintw(y, x, "%s", this->getSymbol().c_str());
    }
    else if (type == 4)
    {
        this->setSymbol("👾");//pistol
        mvprintw(y, x, "%s", this->getSymbol().c_str());
    }
    return;
}
int Enemy::getX() {
    return x;
}
int Enemy::getY() {
    return y;
}
int Enemy::getType() {
    return type;
}
void Enemy::setY(int y) {
    this->y = y;
}
void Enemy::setX(int x) {
    this->x = x;
}
void Enemy::setSymbol(std::string symbol) {
    this->symbol = symbol;
}
std::string Enemy::getSymbol() {
    return symbol;
}
Enemy::~Enemy() {
    //erase enemy
    mvprintw(y, x, " ");
    return;
}
void Enemy::move() {
    //erase enemy
    mvprintw(y, x, " ");
    //move enemy
    if (type == 1)
    {
        if (y < max_y)
            y++;
        else
        {
            y = 0;
            x = rand() % max_x;
        }
    }
    else if (type == 2)
    {
        if (y < max_y && x < max_x)
        {
            y += 2;
            x += rand() % 3 - 2;
        }
        else
        {
            y = 0;
            x = rand() % max_x;
        }
    }
    else if (type == 3)
    {
        if (this->status == 0)
        {
            this->status = 1;
            for (int i = -1; i < 2; i++)
                for (int j = -1; j < 2; j++)
                    mvprintw(y + i, x + j, " ");
            mvprintw(y, x + 1, " ");
        }
        else
        {
            this->status = 1;
            mvprintw(y, x, " ");
        }
        if (y < max_y)
            y += 1;
        else
        {
            y = 0;
            x = rand() % max_x;
        }
        if (rand() % 13 == 0)
        {
            //draw explosion 1 block around coordinates
            for (int i = -1; i < 2; i++)
                for (int j = -1; j < 2; j++)
                        mvprintw(y + i, x + j, "💥");
            mvprintw(y, x + 2, "💥");
            
            //TODO: add player hit detection
            this->status = 0;
        }
    }
    else if (type == 4)
    {
        if (score % 3 == 0)
        {
            if (y < max_y && x < max_x)
                y += 1;
            else
            {
                y = 0;
                x = rand() % max_x;
            }
        }

    }
    //draw enemy
    mvprintw(y, x, "%s", this->getSymbol().c_str());
    return;
}