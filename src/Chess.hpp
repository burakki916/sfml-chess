#ifndef CHESS_H
#define CHESS_H
#pragma once
#include <vector>
#include <utility>
#include "Window.h"
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
	public:
		Chess(Window* l_window);
		void Render(Window* l_window);
		~Chess();


};
#endif

