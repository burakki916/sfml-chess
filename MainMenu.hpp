#ifndef MAINMENU_H
#define MAINMENU_H
#pragma once
#include "Window.hpp"
#include "MenuButton.cpp"
#include <iostream>
class MainMenu  
{
	private:
		static sf::Texture titleBarTexture; 
		static sf::RectangleShape titleBar;
		static std::vector<MenuButton> buttons;  
	public:
		static void init(); 
		static void render();
		static void update(); 
		MainMenu();
		~MainMenu();

};

#endif