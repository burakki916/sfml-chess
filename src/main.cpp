#include <iostream>
#include "Game.h"

// yo
int main() {
    Game newGame;
    while(!newGame.GetWindow()->IsDone()){
        newGame.Update();
        newGame.handleInput();
        newGame.Render();
    }
}