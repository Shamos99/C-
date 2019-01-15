enum DIR {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Game {

private:

    int difficulty;

    int headx;     //head coords
    int heady;

    int fruitx;   //fruit coords
    int fruity;

    int score;
    bool gameover;
    DIR dir;

    int tailx[150], taily[150];
    int tailnum;

    int sizex;
    int sizey;

public:

    void run_game();
    Game(int *x);

private:

    void Setup();
    void Draw();
    void Input();
    void Logic();
    void Face(int x, int y);
};