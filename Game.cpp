#include "Game.hpp"
#include "Window.hpp"
#include "ChessScreen.hpp"
#include "EventManager.hpp"
#include "Piece.hpp"
#include "ScreenManager.hpp"

void Game::initialize() {
	Window::initialize();

	ChessScreen::initialize();
	Piece::initPieces(); 

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