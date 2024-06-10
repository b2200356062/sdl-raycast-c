
class Player{
    private:
        int health;
        int ammo;
        float speed;
        float xpos, ypos;
    
    public:
        Player(int health, float speed);
        int getHealth();
        int getAmmo();
        float getSpeed();
        float getxpos();
        float getypos();

        void setHealth(int health);
        void setAmmo(int ammo);
        void setSpeed(float speed);
        void setypos(float ypos);
        void setxpos(float xpos);
};