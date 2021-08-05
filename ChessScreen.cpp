#include "Piece.hpp"
#include "Window.hpp"
#include "ChessScreen.hpp"

sf::Texture ChessScreen::woodTexture;
sf::Texture ChessScreen::ironTexture;

sf::Color ChessScreen::tileColor1 = sf::Color(50, 28, 12);
sf::Color ChessScreen::tileColor2 = sf::Color(160, 120, 70);
sf::Vector2f ChessScreen::tileSize; 

sf::RectangleShape ChessScreen::tileContainer[8][8];
std::vector<SelectedTile> ChessScreen::selectedTiles;

void ChessScreen::initialize() {
    woodTexture.loadFromFile("MCWood.jpg");
    ironTexture.loadFromFile("IronBlock.jpg");

    ChessScreen::setupTiles();
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
    tileSize = sf::Vector2f(windowSize.x/8, windowSize.y/8);

    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 8; column++) {
            sf::RectangleShape newRect;
            
            if ((row + column) % 2 == 0) newRect.setFillColor(tileColor1);
            else newRect.setFillColor(tileColor2);

            newRect.setSize(tileSize);
            newRect.setPosition(column*tileSize.x, (7-row)*tileSize.y);
            newRect.setTexture(&woodTexture);
            tileContainer[row][column] = newRect;
        }
    }
}

void ChessScreen::highlightTile(sf::Vector2i thisNode, sf::Color thisColor, float transparency) {
    if (Piece::isValid(thisNode)) {
        sf::RectangleShape* thisTile = &tileContainer[thisNode.y][thisNode.x];
        selectedTiles.push_back(SelectedTile(thisTile, thisTile->getFillColor()));

        thisTile->setTexture(&ironTexture);
        thisTile->setFillColor(sf::Color(
            thisColor.r - transparency * (thisColor.r - thisTile->getFillColor().r),
            thisColor.g - transparency * (thisColor.g - thisTile->getFillColor().g),
            thisColor.b - transparency * (thisColor.b - thisTile->getFillColor().b)
        ));
    }
}

void ChessScreen::highlightTile(sf::Vector2i thisNode, sf::Color thisColor) {
    highlightTile(thisNode, thisColor, 0.5f);
}

void ChessScreen::clearHighlightedTiles() {
    for (auto &thisSelectedTile : selectedTiles) {
        thisSelectedTile.obj->setTexture(&woodTexture);
        thisSelectedTile.obj->setFillColor(thisSelectedTile.color);
        selectedTiles.pop_back(); 
    }
}

sf::Vector2f ChessScreen::getTileSilze() {
    return ChessScreen::tileSize;
}