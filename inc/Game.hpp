
#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <vector>

#include "Player.hpp"
#include "Enemy.hpp"
extern int max_y, max_x;
extern long score;
#include "Bullet.hpp"


#define BOLD "\033[1m"
#define RESET "\033[0m"
#define UNDERLINE "\033[4m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

void shoot_bullet(std::vector<Bullet> &bullets, int x, int y);


#endif