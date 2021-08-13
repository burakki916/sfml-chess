#ifndef MAINMENU_H
#define MAINMENU_H

#pragma once
#include "Window.hpp"
#include "MenuButton.hpp"

class MainMenu  
{
	private:
		static sf::Texture titleBarTexture; 
		static sf::RectangleShape titleBar;
		static std::vector<MenuButton*> buttons; 

		static MenuButton* singlePlayerButton;
		static MenuButton* multiplayerButton;
		static MenuButton* settingsButton;

	public:
		static void initialize();
		static void render();

		static MenuButton* clickedButton(sf::Vector2i screenPosition);
};

#endif