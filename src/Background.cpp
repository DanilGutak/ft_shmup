#include "Background.hpp"
#include <ncurses.h>
#include <cstdlib>
#include <iostream>

Background::Background(int x, int y, std::string symbol) : x(x), y(y), symbol(symbol){
    mvprintw(y, x, "%s", this->getSymbol().c_str());
    return;
}
Background::~Background() {
    mvprintw(y, x, " ");
    return;
}
void Background::move() {
    //erase Background
    mvprintw(y, x, " ");
    if (y < max_y)
        y++;
    else
    {
        y = 0;
        x = rand() % max_x;
    }
    mvprintw(y, x, "%s", this->getSymbol().c_str());
    return;
}