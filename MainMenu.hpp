#ifndef MAINMENU_H
#define MAINMENU_H

#pragma once
#include "Window.hpp"
#include "MenuButton.cpp"
#include <iostream>
#include "EventManager.hpp"

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
		static void init(); 
		static void render();
		static void update(); 

		static MenuButton* clickedButton(sf::Vector2i screenPosition);

		MainMenu();
		~MainMenu();
};

#endif