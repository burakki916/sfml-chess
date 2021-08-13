#include "MenuButton.hpp"
#include "Window.hpp"

sf::Vector2f MenuButton::size;
sf::Texture MenuButton::buttonTex;
sf::Font MenuButton::buttonFont;

void MenuButton::initialize() {
	size = sf::Vector2f(Window::getSize().x * 0.40, Window::getSize().y * 0.05);
	buttonFont.loadFromFile("resources/mcFont.ttf");
	buttonTex.loadFromFile("resources/stone.png");
	buttonTex.setRepeated(true);
}

MenuButton::MenuButton(std::string initName, std::string text) {
	name = initName;
	buttonText.setString(text);
	
	buttonText.setFont(MenuButton::buttonFont);
	buttonText.setFillColor(sf::Color::White);
	buttonText.setCharacterSize(MenuButton::size.y * 0.50);
	buttonText.setOrigin(buttonText.getLocalBounds().width / 2, buttonText.getLocalBounds().height / 2);
	buttonDrawable.setTexture(&MenuButton::buttonTex);
	buttonDrawable.setTextureRect(sf::IntRect(0, 0, MenuButton::size.x / 4, MenuButton::size.y / 4));
	buttonDrawable.setSize(size);
	buttonDrawable.setOrigin(MenuButton::size.x / 2, MenuButton::size.y / 2);
	buttonDrawable.setOutlineThickness(3);
	buttonDrawable.setOutlineColor(sf::Color::Black);

	makeDropShadow();
}

void MenuButton::makeDropShadow() {
	dropShadow = buttonText;
	dropShadow.setFillColor(sf::Color(sf::Color(40, 40, 40)));
	dropShadow.setPosition(sf::Vector2f(buttonText.getPosition().x + 2, buttonText.getPosition().y + 3));
}

void MenuButton::render() {
	Window::draw(buttonDrawable);
	Window::draw(dropShadow);
	Window::draw(buttonText);
}

std::string MenuButton::getName() {
	return name;
}

void MenuButton::setPosition(sf::Vector2f newPosition) {
	buttonText.setPosition(newPosition);
	buttonDrawable.setPosition(newPosition);
	makeDropShadow();
}

void MenuButton::setSize(sf::Vector2f newSize) {
	buttonDrawable.setSize(newSize);
	buttonText.setCharacterSize(newSize.y * 0.80);
}

bool MenuButton::contains(sf::Vector2i screenPosition) {
	sf::FloatRect bounds = buttonDrawable.getGlobalBounds();
	return bounds.contains(screenPosition.x, screenPosition.y);
}