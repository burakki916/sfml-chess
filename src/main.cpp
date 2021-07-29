#include <iostream>
#include "Game.hpp"

int main() {
    Game newGame;
    while(!newGame.GetWindow()->IsDone()){
        newGame.Update();
        newGame.handleInput();
        newGame.Render();
    }
}