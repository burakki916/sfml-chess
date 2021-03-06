#include <iostream>

#include "Game.hpp"
#include "Window.hpp"
#include "MainMenu.hpp"
#include "MenuButton.hpp"
#include "ChessScreen.hpp"
#include "ScreenManager.hpp"
#include "MultiplayerMenu.hpp"

GameType Game::gameType;
PieceColors Game::myColor;
Piece *Game::selectedPiece = NULL;
PieceColors Game::currentTurn = PieceColors::white;

sf::TcpSocket Game::connection;
sf::TcpListener Game::listener;
ConnectionStatus Game::connectionStatus = ConnectionStatus::none;

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
	Game::runConnections();
	EventManager::run();
	Game::render();
}

void Game::render() {
	Window::beginDraw();
	ScreenManager::renderScreen();
	Window::endDraw();
}

void Game::runConnections() {
	if (Game::connectionStatus == ConnectionStatus::none) return;
	else if (Game::connectionStatus == ConnectionStatus::waiting) listenForConnection();
	else if (Game::connectionStatus == ConnectionStatus::connected) receiveMovePacket();
}

void Game::listenForConnection() {
	listener.setBlocking(false);
	if (listener.accept(connection) == sf::Socket::Done) {
		resetGame();
		myColor = PieceColors::white;
		Game::gameType = GameType::multiplayer;
		ScreenManager::setCurrentScreen("ChessScreen");

		std::cout << "Connection established." << std::endl;
		Game::connectionStatus = ConnectionStatus::connected;
	}
}

void Game::receiveMovePacket() {
	sf::Packet packet;
	connection.setBlocking(false);
	if (connection.receive(packet) == sf::Socket::Done) {
		sf::Int8 atX, atY, toX, toY;
		packet >> atX >> atY >> toX >> toY;

		Piece* thisPiece = Piece::at(sf::Vector2i(atX, atY));
		if (thisPiece != NULL && thisPiece->attemptMove(sf::Vector2i(toX, toY))) {
			if (Game::currentTurn == PieceColors::white) Game::currentTurn = PieceColors::black;
			else Game::currentTurn = PieceColors::white;

			if (Piece::isInCheckMate(currentTurn)) Game::onCheckMate();
			else if (Piece::isInCheck(currentTurn)) Game::onCheck();
		}
	}
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

void Game::sendMovePacket(sf::Vector2i pieceAt, sf::Vector2i moveTo) {
	sf::Packet packet;
	sf::Int8 atX = pieceAt.x, atY = pieceAt.y, toX = moveTo.x, toY = moveTo.y;
	
	packet << atX << atY << toX << toY;
	connection.send(packet);
}

void Game::handleMultiplayerClick(int x, int y) {
	if (currentTurn == myColor) {
		sf::Vector2i thisNode = Piece::getNodeFromScreenPosition(sf::Vector2i(x, y));
		ChessScreen::clearHighlightedTiles();

		if (Game::selectedPiece != NULL) {
			sf::Vector2i preMovePosition = selectedPiece->getCurrentNode();
			if (Game::selectedPiece->attemptMove(thisNode)) {
				sendMovePacket(preMovePosition, thisNode);

				Game::selectedPiece = NULL;

				if (Game::currentTurn == PieceColors::white) Game::currentTurn = PieceColors::black;
				else Game::currentTurn = PieceColors::white;

				if (Piece::isInCheckMate(currentTurn)) Game::onCheckMate();
				else if (Piece::isInCheck(currentTurn)) Game::onCheck();
			}	
		}
		else Game::selectPiece(thisNode);
	}
}

void Game::onClick(EventInfo *info) {
	if (info->mouseButton.button == sf::Mouse::Left) {
		int x = info->mouseButton.x, y = info->mouseButton.y;
			
		if (ScreenManager::getCurrentScreen() == "ChessScreen") {
			if (Game::gameType == GameType::singleplayer) handleSinglePlayerClick(x, y);
			else if (Game::gameType == GameType::multiplayer) handleMultiplayerClick(x, y);
		}
		else if (ScreenManager::getCurrentScreen() == "MenuScreen") {
			MenuButton* selectedButton = MainMenu::clickedButton(sf::Vector2i(x, y));
			
			if (selectedButton == NULL) return;
			else if (selectedButton->getName() == "Multiplayer") ScreenManager::setCurrentScreen("MultiplayerMenuScreen");
			else if (selectedButton->getName() == "SinglePlayer") {
				resetGame();
				Game::gameType = GameType::singleplayer;
				ScreenManager::setCurrentScreen("ChessScreen");
			}
		}
		else if (ScreenManager::getCurrentScreen() == "MultiplayerMenuScreen") {
			MenuButton* selectedButton = MultiplayerMenu::clickedButton(sf::Vector2i(x, y));

			if (selectedButton == NULL) return;
			else if (selectedButton->getName() == "Host") setupListener();
			else if (selectedButton->getName() == "Join") attemptConnection();	
		}
	}
}

void Game::setupListener() {
	listener.setBlocking(true);
	if (listener.listen(10777) == sf::Socket::Done) {
		std::cout << "Waiting for client connection." << std::endl;
		Game::connectionStatus = ConnectionStatus::waiting;
	}
	else std::cout << "Error setting up listener socket." << std::endl;
}

void Game::attemptConnection() {
	connection.setBlocking(true);
	if (connection.connect("192.168.1.189", 10777) == sf::Socket::Done) {
		resetGame();
		myColor = PieceColors::black;
		Game::gameType = GameType::multiplayer;
		ScreenManager::setCurrentScreen("ChessScreen");

		std::cout << "Connection established." << std::endl;
		Game::connectionStatus = ConnectionStatus::connected;
	}
	else std::cout << "Error connecting to server." << std::endl;
}

void Game::onKeyPressed(EventInfo* info) {
	if (ScreenManager::getCurrentScreen() == "ChessScreen") {
		if (info->key.code == sf::Keyboard::Escape && gameType == GameType::singleplayer) {
			ScreenManager::setCurrentScreen("MenuScreen");
		}
		else if (info->key.code == sf::Keyboard::R && gameType == GameType::singleplayer) {
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