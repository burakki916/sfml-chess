#include <iostream>
#include "Window.hpp"
#include "ChessScreen.hpp"
#include "EventManager.hpp"

sf::Texture ChessScreen::woodTexture;
sf::RectangleShape ChessScreen::tileContainer[8][8];

sf::Color ChessScreen::tileColor1 = sf::Color(50, 30, 29);
sf::Color ChessScreen::tileColor2 = sf::Color(212, 187, 0);
sf::Color ChessScreen::selectedColor = sf::Color(255, 255, 255);
sf::RectangleShape *ChessScreen::selectedTile = NULL;
sf::Color ChessScreen::selectedTileOldColor;

void ChessScreen::initialize() {
    if (!woodTexture.loadFromFile("MCWood.jpg")) {
        std::cout << "ERROR: Can't find texture : \"MCWood.jpg\"" << std::endl;
    }

    ChessScreen::setupTiles();

    EventManager::connectToEvent("ClickTile", &highlightTile);
    EventManager::bindInputToEvent("ClickTile", sf::Event::MouseButtonPressed);
}

void ChessScreen::render() {
    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 8; column++) {
            Window::draw(tileContainer[row][column]);
        }
    }
}

void ChessScreen::setupTiles() {
    sf::Vector2u windowSize = Window::getSize();
    sf::Vector2f tileSize(windowSize.x/8, windowSize.y/8);

    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 8; column++) {
            sf::RectangleShape newRect;
            
            if ((row + column) % 2 == 0) newRect.setFillColor(tileColor1);
            else newRect.setFillColor(tileColor2);

            newRect.setSize(tileSize);
            newRect.setPosition(column*tileSize.x, row*tileSize.y);
            newRect.setTexture(&woodTexture);
            tileContainer[row][column] = newRect;
        }
    }
}

void ChessScreen::highlightTile(EventInfo *info) {
    sf::Vector2i mousePos = Window::getMousePosition();
    
    sf::Vector2u windowSize = Window::getSize();
    sf::Vector2f tileSize(windowSize.x / 8, windowSize.y / 8);

    int row = mousePos.y / tileSize.y;
    int column = mousePos.x / tileSize.x;

    if (row >= 0 && row <= 8 && column >= 0 && column <= 8) {
        if (selectedTile != NULL) {
            selectedTile->setFillColor(selectedTileOldColor);
        }

        selectedTile = &tileContainer[row][column];
        selectedTileOldColor = selectedTile->getFillColor();
        selectedTile->setFillColor(selectedColor);
    }
}