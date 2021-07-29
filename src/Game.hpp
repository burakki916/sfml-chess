#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <stdio.h>      
#include <stdlib.h>    
#include <time.h>   
#include <string>
#include <cmath>
#include "Window.hpp"
#include "Chess.hpp"
class Game
{
public:
	Game();
	~Game();
	void handleInput();
	void Update();
	void Render();
	Window* GetWindow();
	sf::Time GetElapsed();
	void RestartClock(); 
	void outPutMouseCords(EventDetails* l_details); 
private:
	Window m_window;
	sf::Vector2f m_increment;
	sf::Clock m_clock; 
	sf::Time m_elapsed;
	Chess myBoard; 

};

