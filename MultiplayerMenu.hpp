#pragma once
#include "Window.hpp"
#include "MenuButton.hpp"

class MultiplayerMenu
{
	private:
		static std::vector<MenuButton*> buttons; 

		static MenuButton* hostButton;
		static MenuButton* joinButton;

	public:
		static void initialize();
		static void render(); 

		static MenuButton* clickedButton(sf::Vector2i screenPosition);
};
