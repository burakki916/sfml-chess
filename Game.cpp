#include <iostream>
#include "Game.hpp"
#include "Window.hpp"
#include "ChessScreen.hpp"
#include "ScreenManager.hpp"

Piece *Game::selectedPiece = NULL;
PieceColors Game::currentTurn = PieceColors::white;

void Game::initialize() {
	Window::initialize();
	ChessScreen::initialize();
	Piece::initialize();

	Piece::newBoard();

	EventManager::connectToEvent("ClickBoard", &onClick);
	EventManager::bindInputToEvent("ClickBoard", sf::Event::MouseButtonPressed);

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

void Game::selectPiece(sf::Vector2i thisNode) {
	Piece *clickedPiece = Piece::at(thisNode);

	if (clickedPiece != NULL && clickedPiece->getColor() == currentTurn) {
		Game::selectedPiece = clickedPiece;
		Game::selectedPiece->highlightPossibleMoves();
		ChessScreen::highlightTile(thisNode, sf::Color(0, 180, 0));
	}	
	else Game::selectedPiece = NULL;
}

void Game::onClick(EventInfo *info) {
	if (info->mouseButton.button == sf::Mouse::Left) {
		int x = info->mouseButton.x, y = info->mouseButton.y;
		sf::Vector2i thisNode = Piece::getNodeFromScreenPosition(sf::Vector2i(x, y));
		ChessScreen::clearHighlightedTiles();

		// If there is a selected piece and move of it is successful
		if (Game::selectedPiece != NULL && Game::selectedPiece->attemptMove(thisNode)) {
			Game::selectedPiece = NULL;
			
			if (Game::currentTurn == PieceColors::white) Game::currentTurn = PieceColors::black;
			else Game::currentTurn = PieceColors::white;

			if (Piece::isInCheckMate(currentTurn)) Game::onCheckMate();
			else if (Piece::isInCheck(currentTurn)) Game::onCheck();
		}
		else Game::selectPiece(thisNode);
	}
}

void Game::onCheck() {
	std::cout << "In check!" << std::endl;
	// Alert the player
	// Moves are restricted to the ones that would get out of check
}

void Game::onCheckMate() {
	std::cout << "In check mate!" << std::endl;
	// Show game over text/menu/stats
	// Option to retart or return to menu
}