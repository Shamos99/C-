#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

//Head Coords
int headx;
int heady;

//Fruit Coords
int fruitx;
int fruity;

//Score
int score;

//////

enum DIR
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

DIR dir; // this will be the direction the head is facing

bool gameover; // it is pretty obvious

int tailx[150], taily[150]; //store corrds of tails
int tailnum;

//Declarations

void Setup();
void Draw();
void Input();
void Logic();

void Face(int x, int y);

//////
//////
//////

int main()
{
    Setup();

    while (!gameover)
    {
        Draw();
        Input();
        Logic();
        usleep(1000); 
    }

    endwin();
    return 0;
}

//////
//////
//////

void Setup()
{
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    headx = 10;
    heady = 10;

    fruitx = (rand() % 18) + 1;
    fruity = (rand() % 18) + 1;

    dir = STOP;

    gameover = FALSE;
    score = 0;
    tailnum = 0;
}

//Draw the Entire Game....duh
void Draw()
{
    clear();

    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 20; y++)
        {
            if (x == 0 || x == 19)
                mvprintw(x, y, "#");
            else if (y == 0 || y == 19)
                mvprintw(x, y, "#");
            else if (heady == y && headx == x) //draw head
            {
                Face(headx, heady);
            }
            else if (fruity == y && fruitx == x) //draw fruit
                mvprintw(x, y, "@");
            else //print tail
            {
                for (int k = 0; k < tailnum; k++)
                {
                    if (tailx[k] == x && taily[k] == y)
                        mvprintw(x, y, "o");
                }
            }
        }
    }

    mvprintw(21, 0, "Score: %d", score); //scorecard

    refresh(); //display this crap
}

//Just draws the face the way I want it
void Face(int x, int y)
{
    if (dir == LEFT)
        mvprintw(x, y, ">");
    else if (dir == RIGHT)
        mvprintw(x, y, "<");
    else if (dir == UP)
        mvprintw(x, y, "v");
    else if (dir == DOWN)
        mvprintw(x, y, "^");
    else
        mvprintw(x, y, "o");

    return;
}

//Handle User Input
void Input()
{
    keypad(stdscr, TRUE);
    halfdelay(1);

    int c = getch();

    switch (c)
    {
    case KEY_LEFT:
        dir = LEFT;
        break;

    case KEY_RIGHT:
        dir = RIGHT;
        break;

    case KEY_UP:
        dir = UP;
        break;

    case KEY_DOWN:
        dir = DOWN;
        break;

    case 113: //If you press Q you quit the game
        gameover = TRUE;
        break;

    default:
        break;
    }
}

//Need I say what this is?
void Logic()
{

    int prevX = tailx[0]; //store prvious position of the head
    int prevY = taily[0];
    int prev2X, prev2Y;
    tailx[0] = headx; //update with the current head position
    taily[0] = heady;

    //tail algo that I have yet to figure out

    for (int i = 1; i < tailnum; i++)
    {
        prev2X = tailx[i];
        prev2Y = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    //Update Coords
    switch (dir)
    {
    case LEFT:
        heady--;
        break;

    case RIGHT:
        heady++;
        break;

    case UP:
        headx--;
        break;

    case DOWN:
        headx++;
        break;

    default:
        break;
    }

    //Scoring system
    if (headx == fruitx && heady == fruity)
    {
        fruitx = (rand() % 18) + 1;
        fruity = (rand() % 18) + 1;

        score++;
        tailnum++;
    }

    //Guy died
    if (headx == 0 || headx == 19 || heady == 0 || heady == 19)
        gameover = TRUE;

    for (int j = 0; j < tailnum; j++)
    {
        if (tailx[j] == headx && taily[j] == heady)
            gameover = true;
    }
}