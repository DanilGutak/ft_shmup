

class Player
{
    public:
        Player(int x, int y);
        void move(int key);
        int getX();
        int getY();
    private:
        int x, y;
        int hp;
};