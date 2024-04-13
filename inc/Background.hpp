#include "Game.hpp"

#pragma once
#ifndef Background_HPP
#define Background_HPP
#include <string>
#include <iostream>

class Background
{
    public:
        Background(int x, int y, std::string symbol);
        ~Background();
        int getX(){return x;};
        int getY(){return y;};
        std::string getSymbol(){return symbol;};
        void setY(int y){this->y = y;};
        void setX(int x){this->x = x;};
        void move();
    private:
        int x, y;
        std::string symbol;
};

#endif