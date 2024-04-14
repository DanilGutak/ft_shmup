#ifndef PLAYER_HPP
#define PLAYER_HPP

#define PLAYER_SYMBOL "A"
class Player
{
    public:
        Player(int x, int y, int hp = 10, bool invincible = false, int score = 0) {
            this->x = x;
            this->y = y;
            this->hp = hp;
            this->invincible = invincible;
            this->score = score;
        }
        ~Player() {}
        void move(int key);
        bool check_collision(int x, int y);
        int getX();
        int getY();
        int getHP();
        void looseHP();
        void setInvincible(bool invincible);
        void set_score(int score);
        int get_score();
        bool getInvincible();
    private:
        int x, y;
        int hp;
        bool invincible;
        int score;
};

#endif