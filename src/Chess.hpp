#ifndef CHESS_H
#define CHESS_H
#pragma once
#include <vector>
#include <utility>
#include "Window.hpp"
class Chess  
{
	private:
		using tileContainer = std::vector<std::vector<sf::RectangleShape>>; 
		tileContainer Tiles;  //Drawable elements
		void TilesSetUp(); 
		std::pair<sf::Color,sf::Color> tilesColors;
		Window* m_window;
		void highlightBox(EventDetails* l_details);
		sf::RectangleShape highlightedCube; 
		sf::Texture woodTexture; 

	public:
		Chess(Window* l_window);
		void Render(Window* l_window);
		~Chess();


};
#endif

