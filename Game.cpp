#include "Game.hpp"
#include "Window.hpp"
#include "ChessScreen.hpp"
#include "ScreenManager.hpp"

Piece *Game::selectedPiece = NULL;
PieceColors Game::currentTurn = PieceColors::white;

void Game::initialize() {
	Window::initialize();

	ChessScreen::initialize();
	Piece::initPieces(); 

	EventManager::connectToEvent("ClickBoard", &onClick);
	EventManager::bindInputToEvent("ClickBoard", sf::Event::MouseButtonPressed);

	// Fired by Piece class. Checked after Move/Kill
	EventManager::connectToEvent("Check", &onCheck);
	EventManager::connectToEvent("CheckMate", &onCheckMate);

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

// Select new piece or deselect current piece
void Game::selectPiece(int x, int y) {
	/*
	Piece *clickedPiece = Piece::at(x, y);

	// If click was on a piece and the piece is the current turn's color
	if (clickedPiece != NULL && clickedPiece->getColor() == currentTurn) {
		Game::selectedPiece = clickedPiece;
		clickedPiece.highlightMoves(); // Highlight possible moves
	}	
	else {
		Game::selectedPiece = NULL;
		clickedPiece.unHighlightMoves();
	}
	*/
}

void Game::onClick(EventInfo *info) {
	/*
	if (info->mouseButton.button == sf::Mouse::Left) {
		int x = info->mouseButton.x, y = info->mouseButton.y;
		
		// If there is a selected piece and move of it is successful
		if (Game::selectedPiece != NULL && Game::selectedPiece->attemptMove(x, y)) {
			selectedPiece = NULL;
			if (currentTurn = PieceColors::white) currentTurn = PieceColors::black;
			else currentTurn = PieceColors::white;
		}
		else { 
			selectPiece(x, y);
		}
	}
	*/
}

void Game::onCheck(EventInfo *info) {
	// Alert the player
	// Moves are restricted to the ones that would get out of check
}

void Game::onCheckMate(EventInfo *info) {
	// Show game over text/menu/stats
	// Option to retart or return to menu
}