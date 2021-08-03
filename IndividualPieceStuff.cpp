#include "Piece.hpp"
#include <iostream>

std::vector<sf::Vector2i> PawnPiece::getPossibleMoves() {
    std::vector<sf::Vector2i> movements;

    if (isEmpty(currentNode + flip(sf::Vector2i(0, 1)))) {
        movements.push_back(flip(sf::Vector2i(0, 1)));
    }

    if (!hasMoved && !isFriend(currentNode + flip(sf::Vector2i(0, 2)))) {
        movements.push_back(flip(sf::Vector2i(0, 2)));
    }

    if (isEnemy(currentNode + flip(sf::Vector2i(1, 1)))) {
        movements.push_back(flip(sf::Vector2i(1, 1)));
    }

    if (isEnemy(currentNode + flip(sf::Vector2i(-1, 1)))) {
        movements.push_back(flip(sf::Vector2i(-1, 1)));
    }

    return movements;
}

// Textures

void PawnPiece::setSpriteTex() {
    sprite.setTexture(Piece::piecesTexture);
    sprite.setTextureRect(sf::IntRect(Piece::spriteTexDem.x*5,0,Piece::spriteTexDem.x,Piece::spriteTexDem.y));
}

void RookPiece::setSpriteTex() {
    sprite.setTexture(Piece::piecesTexture);
    sprite.setTextureRect(sf::IntRect(Piece::spriteTexDem.x*4,0,Piece::spriteTexDem.x,Piece::spriteTexDem.y));
}

void KnightPiece::setSpriteTex() {
    sprite.setTexture(Piece::piecesTexture);
    sprite.setTextureRect(sf::IntRect(Piece::spriteTexDem.x*3,0,Piece::spriteTexDem.x,Piece::spriteTexDem.y));
}

void BishopPiece::setSpriteTex() {
    sprite.setTexture(Piece::piecesTexture);
    sprite.setTextureRect(sf::IntRect(Piece::spriteTexDem.x*2,0,Piece::spriteTexDem.x,Piece::spriteTexDem.y));
}

void QueenPiece::setSpriteTex() {
    sprite.setTexture(Piece::piecesTexture);
    sprite.setTextureRect(sf::IntRect(Piece::spriteTexDem.x*1,0,Piece::spriteTexDem.x,Piece::spriteTexDem.y));
}

void KingPiece::setSpriteTex() {
    sprite.setTexture(Piece::piecesTexture);
    sprite.setTextureRect(sf::IntRect(Piece::spriteTexDem.x*0,0,Piece::spriteTexDem.x,Piece::spriteTexDem.y));
}