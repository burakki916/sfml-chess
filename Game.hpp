#pragma once
#include "Piece.hpp"
#include "EventManager.hpp"

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

		// Main rendering loop
		// Should hand control to other classes as much as possible.
		static void render();

		static void resetGame();

		// Main click event
		static void onClick(EventInfo* info);
		static void onKeyPressed(EventInfo* info);
		// Select piece at node or deselect piece if empty
		static void selectPiece(sf::Vector2i thisNode);

		static void onCheck();
		static void onCheckMate();
};
