#pragma once
#include "EventManager.hpp"
#include <SFML/Graphics.hpp>
#include "Piece.hpp"
#include <utility> 
class ChessScreen {
	public:
		static sf::Texture woodTexture;

		static sf::RectangleShape tileContainer[8][8];
		static sf::Color tileColor1;
		static sf::Color tileColor2;
		static sf::Vector2f tileSize; 

		static sf::Color selectedColor;
		static sf::RectangleShape *selectedTile;
		static sf::Color selectedTileOldColor;

		// Initialize objects & events
		static void initialize();
		// Called every frame where ChessScreen is rendered
		static void render();

		// Callback connected to sfml MouseButtonPressed event.
		// On click it checks the current mouse position and highlights chess square.
		// Will probably be handled elsewhere in the future. This class is mainly for rendering, not calculation/events.
		static void highlightTile(EventInfo* info);

	private:
		// Helper function for initialize
		static void setupTiles();
};