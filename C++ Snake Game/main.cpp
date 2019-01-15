#include "game.h"
#include "startmenu.h"


int main(){
    Start_Menu startmenu;

    int *arr = startmenu.choice();
    startmenu.~Start_Menu();

    Game game(arr);

    game.run_game();
}