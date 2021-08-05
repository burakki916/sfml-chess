#pragma once

#include <SFML/Graphics.hpp>
#include "EventManager.hpp"

class Window {
	public:
		// Initialize main window. Called by Game::initialize()
		static void initialize();

		// Checks for pending sfml events. Called by EventManager's run function every frame
		static bool pollEvent(sf::Event &thisEvent);

		// All rendering should be routed to these functions
		static void beginDraw();
		static void draw(sf::Drawable& toDraw);
		static void endDraw();
		
		// Binded to sfml Closed event. 
		static void close(EventInfo* info);

		// Check if the window is still open
		static bool isOpen();

		// Getters related to mainWindow
		static sf::Vector2u getSize();
		static sf::Vector2i getMousePosition();

	private:
		// The main object window itself
		static sf::RenderWindow mainWindow;
};