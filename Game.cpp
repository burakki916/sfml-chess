#include "Game.hpp"
#include "Window.hpp"
#include "ChessScreen.hpp"
#include "EventManager.hpp"
#include "ScreenManager.hpp"

void Game::initialize() {
	Window::initialize();
	ChessScreen::initialize();

	ScreenManager::setCurrentScreen("ChessScreen");
}

void Game::run() {
	EventManager::run();
	Game::render();
}

void Game::render() {
	Window::beginDraw();
	ScreenManager::renderScreen();
	Window::endDraw();
}