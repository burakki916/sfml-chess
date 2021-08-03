#include "Game.hpp"
#include "Window.hpp"
#include "ChessScreen.hpp"
#include "EventManager.hpp"
#include "Piece.hpp"

void Game::initialize() {
	Window::initialize();

	ChessScreen::initialize();
	Piece::initPieces(); 
}

void Game::run() {
	EventManager::run();
	Game::render();
}

void Game::render() {
	Window::beginDraw();
	ChessScreen::render();
	Piece::render(); 
	Window::endDraw();
	
}