#include <iostream>
#include "Game.h"

int main() {
    Game newGame;
    while(!newGame.GetWindow()->IsDone()){
        newGame.Update();
        newGame.handleInput();
        newGame.Render();
    }
}