#pragma once
#include <SFML/Graphics.hpp>

class MenuButton {
	public:
		MenuButton(std::string initName, std::string text);

		static void initialize();
		void render();

		bool contains(sf::Vector2i screenPosition);

		std::string getName();
		void setPosition(sf::Vector2f newPosition);
		void setSize(sf::Vector2f newSize);

	private:
		static sf::Vector2f size;
		static sf::Texture buttonTex;
		static sf::Font buttonFont;

		sf::Vector2i location;
		sf::RectangleShape buttonDrawable;
		sf::Text buttonText;
		sf::Text dropShadow;
		std::string name = "N/A";

		void makeDropShadow();
};