#pragma once
#include "Piece.hpp"
#include "EventManager.hpp"
#include <SFML/Network.hpp>

enum class GameType {
	Multiplayer,
	Singleplayer
};

enum class ConnectionStatus {
	None,
	Waiting,
	Connected
};

class Game {
	public:
		// Perform any initializations. Called by main.
		// This is the function that calls the initialization methods of other classes.
		static void initialize();
		
		// Called every frame. Called by main
		// Call necessary run/update functions in other classes.
		static void run();

	private:
		static Piece* selectedPiece;
		static PieceColors currentTurn;
		static GameType gameType;
		static PieceColors myColor;

		// Server-client or client-server
		static sf::TcpSocket connection;
		static sf::TcpListener listener;
		static ConnectionStatus connectionStatus;

		// Main rendering loop
		// Should hand control to other classes as much as possible.
		static void render();

		static void runConnections();

		static void resetGame();

		// Main click event
		static void onClick(EventInfo* info);
		static void handleSinglePlayerClick(int x, int y);

		static void broadcastMove(sf::Vector2i pieceAt, sf::Vector2i moveTo);
		static void handleMultiplayerClick(int x, int y);

		static void onKeyPressed(EventInfo* info);
		// Select piece at node or deselect piece if empty
		static void selectPiece(sf::Vector2i thisNode);

		static void onCheck();
		static void onCheckMate();
};
