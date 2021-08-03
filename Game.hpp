#pragma once
#include "Piece.hpp"
#include "EventManager.hpp"

class Game {
	public:
		static Piece *selectedPiece;
		static PieceColors currentTurn;

		// Perform any initializations. Called by main.
		// This is the function that calls the initialization methods of all other classes.
		static void initialize();
		
		// Called every frame. Called by main
		// Call necessary run/update functions in other classes.
		static void run();

		// Handles renderings
		// Should hand control to other classes as much as possible.
		static void render();

		// Main click event
		static void onClick(EventInfo* info);
		
		// Events called by piece class on move/kill
		static void onCheck(EventInfo* info);
		static void onCheckMate(EventInfo* info);

	private:
		// Helper. Select new piece or deselect current piece by clicking on x, y
		static void selectPiece(sf::Vector2i thisNode);
};
