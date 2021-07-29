#include "Game.h"
Game::Game() :
	m_window("SFML Window", sf::Vector2u(720,720 )), myBoard(&m_window)
{
	RestartClock();
}
Game::~Game() {}

void Game::handleInput()
{

}

void Game::Update()
{
	m_window.Update(); 
	m_elapsed = m_clock.getElapsedTime(); 
	float timestep = 1.0f / 0.011;
	if (m_elapsed > sf::seconds(5)) {
		
	}

}

void Game::Render()
{
	m_window.BeginDraw(); //clears screen 
	myBoard.Render(GetWindow()); 
	m_window.EndDraw(); // display
}

Window* Game::GetWindow()
{
	return &m_window;
}

sf::Time Game::GetElapsed()
{
	return m_elapsed; 
}

void Game::RestartClock()
{
	m_elapsed = m_clock.restart(); 
}
