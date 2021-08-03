#include <cmath>
#include "Game.hpp"
#include "Window.hpp"
int main() {
	Game::initialize();
	while (Window::isOpen()) {
		Game::run();
	}
}

