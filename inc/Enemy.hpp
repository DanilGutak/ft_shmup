#include "Game.hpp"
#pragma once
#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Bullet.hpp"
class Bullet;
class Enemy
{
    public:
        Enemy(int x, int y, int type);
        ~Enemy();
        void move();
        int getX();
        int getY();
        int getType();
        std::string getSymbol();
        void setY(int y);
        void setX(int x);
        void setSymbol(std::string symbol);
        void shoot(std::vector<Bullet> &bullets);
    private:
        int x, y;
        int type;
        int status;
        std::string symbol;
};

#endif