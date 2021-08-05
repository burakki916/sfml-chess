#pragma once
#include <SFML/Graphics.hpp>

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
		// Initialize objects & textures
		static void initialize();

		// Called every frame where ChessScreen is rendered
		static void render();

		// Change the color of a specific node. Transparency keeps some of old color
		static void highlightTile(sf::Vector2i thisNode, sf::Color thisColor);
		static void highlightTile(sf::Vector2i thisNode, sf::Color thisColor, float transparency);
		static void clearHighlightedTiles();

		static sf::Vector2f getTileSilze();

	private:
		static sf::Texture woodTexture;
		static sf::Texture ironTexture;

		static sf::Color tileColor1;
		static sf::Color tileColor2;
		static sf::Vector2f tileSize;

		static sf::RectangleShape tileContainer[8][8];
		static std::vector<SelectedTile> selectedTiles;

		// Helper function for initialize
		static void setupTiles();
};