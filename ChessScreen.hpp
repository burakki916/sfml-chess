#pragma once

#include "EventManager.hpp"
#include <SFML/Graphics.hpp>
#include "Piece.hpp"
#include <utility> 

class SelectedTile {
public:
	sf::Color color;
	sf::RectangleShape* obj;
	SelectedTile(sf::RectangleShape* initObj, sf::Color initColor) {
		obj = initObj;
		color = initColor;
	}
};

class ChessScreen {
	public:
		static sf::Texture woodTexture;
		static sf::Texture ironTexture;

		static sf::RectangleShape tileContainer[8][8];
		static sf::Color tileColor1;
		static sf::Color tileColor2;
		static sf::Vector2f tileSize; 

		static sf::Color selectedColor;

		static std::vector<SelectedTile> selectedTiles;

		// Initialize objects & events
		static void initialize();
		// Called every frame where ChessScreen is rendered
		static void render();

		// Change the color of a specific node
		static void highlightTile(sf::Vector2i thisNode, sf::Color thisColor);
		static void highlightTile(sf::Vector2i thisNode, sf::Color thisColor, float transparency);
		static void clearHighlightedTiles();

	private:
		// Helper function for initialize
		static void setupTiles();
};