#pragma once
#include "Piece.hpp"
#include "EventManager.hpp"
#include <SFML/Network.hpp>

enum class GameType {
	multiplayer,
	singleplayer
};

enum class ConnectionStatus {
	none,
	waiting,
	connected
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
		
		// Check for connection updates each frame
		static void runConnections();
		static void listenForConnection();
		static void receiveMovePacket();

		static void resetGame();

		// Main click event
		static void onClick(EventInfo* info);
		static void handleSinglePlayerClick(int x, int y);
		static void handleMultiplayerClick(int x, int y);

		// Send info on my move to other player
		static void sendMovePacket(sf::Vector2i pieceAt, sf::Vector2i moveTo);
		// Setup host to listen for client
		static void setupListener();
		// Attempt to connect to host
		static void attemptConnection();

		static void onKeyPressed(EventInfo* info);
		// Select piece at node or deselect piece if empty
		static void selectPiece(sf::Vector2i thisNode);

		static void onCheck();
		static void onCheckMate();
};
