#include "Window.hpp"

sf::RenderWindow Window::mainWindow;

void Window::initialize() {
	sf::Vector2u size(720, 720);
	std::string title = "SFML Chess";

	mainWindow.create({size.x, size.y}, title);

	EventManager::connectToEvent("CloseWindow", &close);
	EventManager::bindInputToEvent("CloseWindow", sf::Event::Closed);
}

bool Window::pollEvent(sf::Event &thisEvent) {
	return mainWindow.pollEvent(thisEvent);
}

void Window::beginDraw() {
	mainWindow.clear(sf::Color(30, 30, 30, 255));
}

void Window::draw(sf::Drawable& toDraw) {
	mainWindow.draw(toDraw);
}

void Window::endDraw() {
	mainWindow.display();
}

void Window::close(EventInfo* info) {
	mainWindow.close();
}

bool Window::isOpen() {
	return mainWindow.isOpen();
}

sf::Vector2u Window::getSize() {
	return mainWindow.getSize();
}

sf::Vector2i Window::getMousePosition() {
	return sf::Mouse::getPosition(mainWindow);
}