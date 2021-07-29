#pragma once
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "EventManager.h"
class Window
{
public:
	Window();
	Window(const std::string& l_title, const sf::Vector2u& l_size);
	~Window();
	void Close(EventDetails* l_details = nullptr);

	void BeginDraw(); // clears the window
	void EndDraw(); // display the changes 
	void Update();

	bool IsDone();
	bool IsFullScreen();
	bool IsFocused(); 
	sf::Vector2u* GetWindowSize();

	void ToggleFullscreen(EventDetails* l_details);
	void Draw(sf::Drawable& l_drawable);
	sf::RenderWindow* GetRenderWindow(); 
	EventManager* GetEventManager();
	
private:
	void Setup(const std::string& l_title, const sf::Vector2u& l_size);
	void Destroy();
	void Create();
	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	sf::Vector2u m_nonFSRes; 
	sf::Vector2u m_FullScreenRes; 
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullScreen; 
	EventManager m_eventManager;
	bool m_isFocused; 

};
