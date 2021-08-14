#include <iostream>
#include "Game.hpp"
#include "Window.hpp"
#include "ChessScreen.hpp"
#include "ScreenManager.hpp"
#include "MainMenu.hpp"
#include "MenuButton.hpp"
#include "MultiplayerMenu.hpp"
#include <SFML/Network.hpp>

Piece *Game::selectedPiece = NULL;
PieceColors Game::currentTurn = PieceColors::white;
GameType Game::gameType;

void Game::initialize() {
	Window::initialize();
	ChessScreen::initialize();
	Piece::initialize();
	MenuButton::initialize();
	MainMenu::initialize();
	MultiplayerMenu::initialize();

	EventManager::connectToEvent("ClickBoard", &onClick);
	EventManager::bindInputToEvent("ClickBoard", sf::Event::MouseButtonPressed);

	EventManager::connectToEvent("KeyPressed", &onKeyPressed);
	EventManager::bindInputToEvent("KeyPressed", sf::Event::KeyPressed);

	ScreenManager::setCurrentScreen("MenuScreen");
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

void Game::resetGame() {
	Game::selectedPiece = NULL;
	ChessScreen::clearHighlightedTiles();
	Game::currentTurn = PieceColors::white;
	Piece::newBoard();
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

void Game::handleSinglePlayerClick(int x, int y) {
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

void Game::onClick(EventInfo *info) {
	if (info->mouseButton.button == sf::Mouse::Left) {
		int x = info->mouseButton.x, y = info->mouseButton.y;
			
		if (ScreenManager::getCurrentScreen() == "ChessScreen") {
			if (Game::gameType == GameType::Singleplayer) {
				handleSinglePlayerClick(x, y);
			}	
		}
		else if (ScreenManager::getCurrentScreen() == "MenuScreen") {
			MenuButton* selectedButton = MainMenu::clickedButton(sf::Vector2i(x, y));
			
			if (selectedButton == NULL) 
				return;
			else if (selectedButton->getName() == "SinglePlayer") {
				resetGame();
				Game::gameType = GameType::Singleplayer;
				ScreenManager::setCurrentScreen("ChessScreen");
			}
			else if (selectedButton->getName() == "Multiplayer") {
				ScreenManager::setCurrentScreen("MultiplayerMenuScreen");
			}
		}
		else if (ScreenManager::getCurrentScreen() == "MultiplayerMenuScreen") {
			MenuButton* selectedButton = MultiplayerMenu::clickedButton(sf::Vector2i(x, y));

			if (selectedButton == NULL)
				return;
			else if (selectedButton->getName() == "Host") {
				sf::TcpSocket client;
				sf::TcpListener listener;

				if (listener.listen(10777) == sf::Socket::Done) {
					std::cout << "Waiting for client connection." << std::endl;
					if (listener.accept(client) == sf::Socket::Done) {
						std::cout << "Connection established." << std::endl;
					} 
					else std::cout << "Error accepting client connection." << std::endl;
				} 
				else std::cout << "Error setting up listener socket." << std::endl;
			}
			else if (selectedButton->getName() == "Join") {
				sf::TcpSocket socket;
				sf::Socket::Status status = socket.connect("192.168.1.189", 10777);

				if (status == sf::Socket::Done) {
					std::cout << "Connection established." << std::endl;
				}
				else std::cout << "Error connecting to server." << std::endl;
			}
		}
	}
}

void Game::onKeyPressed(EventInfo* info) {
	if (ScreenManager::getCurrentScreen() == "ChessScreen") {
		if (info->key.code == sf::Keyboard::Escape) {
			ScreenManager::setCurrentScreen("MenuScreen");
		}
		else if (info->key.code == sf::Keyboard::R) {
			resetGame();
		}
	}
	else if (ScreenManager::getCurrentScreen() == "MultiplayerMenuScreen") {
		if (info->key.code == sf::Keyboard::Escape) {
			ScreenManager::setCurrentScreen("MenuScreen");
		}
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