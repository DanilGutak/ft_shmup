#ifndef PLAYER_HPP
#define PLAYER_HPP

#define PLAYER_SYMBOL "A"
class Player
{
    public:
        Player(int x, int y, int hp = 10) {
            this->x = x;
            this->y = y;
            this->hp = hp;
        }
        void move(int key);
        bool check_collision(int x, int y);
        int getX();
        int getY();
        int getHP();
    private:
        int x, y;
        int hp;
};

#endif