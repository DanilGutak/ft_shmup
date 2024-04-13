#ifndef BULLET_HPP
#define BULLET_HPP

#include <string>

class Bullet
{
    public:
        Bullet(int x, int y, std::string who_shot) {
            this->x = x;
            this->y = y;
            this->who_shot = who_shot;
        }
        void move();
        void shoot(int x, int y);
        void print();
        bool check_collision(int x, int y);
        int getX();
        int getY();
    private:
        int x, y;
        std::string who_shot;
};

// void shoot_bullet(std::vector<Bullet> &bullets, int x, int y);
// void Bullet::print();
// void Bullet::move();
// int Bullet::getX();
// int Bullet::getY();
// bool Bullet::check_collision(int x, int y); //if bullet is at x, y return true

#endif