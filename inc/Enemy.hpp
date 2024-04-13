#include "Game.hpp"
#pragma once
#ifndef ENEMY_HPP
#define ENEMY_HPP

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
    private:
        int x, y;
        const int type;
        int status;
        std::string symbol;
};

#endif