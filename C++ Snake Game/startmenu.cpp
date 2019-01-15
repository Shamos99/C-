
#include <ncurses.h>
#include <string>
#include "startmenu.h"

using namespace std;

void Start_Menu::setup() {

    //ncurses shit
    initscr();
    clear();
    noecho();
    cbreak();

    getmaxyx(stdscr, row, col);
    string title = "Welcome to the not so great Snake Game!";

    //print title
    int pos = (col / 2) - (((int) title.length()) / 2); //print title at this x-coord
    attron(A_BOLD);
    mvprintw(2, pos, "%s", title.c_str());
    attroff(A_BOLD);


    string play = "Select a difficulty and press enter...";

    const char *difficulty[] = {
            "Easy",
            "Medium",
            "Hard"
    };

    mvprintw(row / 4, (col / 2) - (((int) play.size()) / 2), "%s", play.c_str());

    int half_row = row / 3;

    for (int x = 0; x < 3; x++) {
        mvprintw(half_row + x, col / 2 - 4, difficulty[x]);
    }

    this->dif_x = col / 2 - 5;
    move(half_row, this->dif_x);

    this->positions[0] = half_row;
    this->positions[1] = half_row + 1;
    this->positions[2] = half_row + 2;

    refresh();
}

void Start_Menu::input() {

    int c = getch();
    keypad(stdscr, true);
    halfdelay(1);

    switch (c) {
        case KEY_UP:
            if (dif_y == 0)
                dif_y = 2;
            else
                dif_y = (dif_y - 1) % 3;

            move(this->positions[dif_y], dif_x);
            break;
        case KEY_DOWN:
            dif_y = (dif_y + 1) % 3;
            move(this->positions[dif_y], dif_x);
            break;
        case 10:
            this->difficulty_is_set = true;
            break;
        default:
            break;

    }

    return;
}

int* Start_Menu::choice() {

    this->setup();
    this->difficulty_is_set = false;

    while (!this->difficulty_is_set) {
        input();
    }

    endwin();

    static int array[] = {dif_y,row,col};

    return array;
}


