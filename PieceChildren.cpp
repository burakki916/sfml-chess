#include "Piece.hpp"

Piece::Moveset PawnPiece::getPossibleMoves() {
    Piece::Moveset movements;

    sf::Vector2i forward = flip(sf::Vector2i(0, 1));
    if (isValid(currentNode + forward) && isEmpty(currentNode + forward)) {
        movements.push_back(forward);
    }

    sf::Vector2i doubleForward = flip(sf::Vector2i(0, 2));
    if (!hasMoved && isValid(currentNode + doubleForward) && !isFriend(currentNode + doubleForward)) {
        movements.push_back(doubleForward);
    }

    sf::Vector2i diag1 = flip(sf::Vector2i(1, 1));
    if (isValid(currentNode + diag1) && isEnemy(currentNode + diag1)) {
        movements.push_back(diag1);
    }

    sf::Vector2i diag2 = flip(sf::Vector2i(-1, 1));
    if (isValid(currentNode + diag2) && isEnemy(currentNode + diag2)) {
        movements.push_back(diag2);
    }

    return movements;
}

Piece::Moveset RookPiece::getPossibleMoves() {
    Piece::Moveset movements;

    extend(movements, sf::Vector2i(1, 0));
    extend(movements, sf::Vector2i(-1, 0));
    extend(movements, sf::Vector2i(0, 1));
    extend(movements, sf::Vector2i(0, -1));

    return movements;
}

Piece::Moveset KnightPiece::getPossibleMoves() {
    Piece::Moveset movements;
    std::vector<sf::Vector2i> toCheck = {
        sf::Vector2i(2, 1),
        sf::Vector2i(2, -1),
        sf::Vector2i(-2, 1),
        sf::Vector2i(-2, -1),
        sf::Vector2i(1, 2),
        sf::Vector2i(-1, 2),
        sf::Vector2i(1, -2),
        sf::Vector2i(-1, -2),
    };

    for (auto thisCheck : toCheck) {
        if (isValid(currentNode + thisCheck) && !isFriend(currentNode + thisCheck)) {
            movements.push_back(thisCheck);
        }
    }

    return movements;
}

Piece::Moveset BishopPiece::getPossibleMoves() {
    Piece::Moveset movements;

    extend(movements, sf::Vector2i(1, 1));
    extend(movements, sf::Vector2i(-1, 1));
    extend(movements, sf::Vector2i(1, -1));
    extend(movements, sf::Vector2i(-1, -1));

    return movements;
}



Piece::Moveset QueenPiece::getPossibleMoves() {
    Piece::Moveset movements;

    extend(movements, sf::Vector2i(1, 0));
    extend(movements, sf::Vector2i(-1, 0));
    extend(movements, sf::Vector2i(0, 1));
    extend(movements, sf::Vector2i(0, -1));

    extend(movements, sf::Vector2i(1, 1));
    extend(movements, sf::Vector2i(-1, 1));
    extend(movements, sf::Vector2i(1, -1));
    extend(movements, sf::Vector2i(-1, -1));

    return movements;
}

Piece::Moveset KingPiece::getPossibleMoves() {
    Piece::Moveset movements;
    std::vector<sf::Vector2i> toCheck = {
        sf::Vector2i(1, 0),
        sf::Vector2i(1, 1),
        sf::Vector2i(1, -1),
        sf::Vector2i(-1, 0),
        sf::Vector2i(-1, 1),
        sf::Vector2i(-1, -1),
        sf::Vector2i(0, 1),
        sf::Vector2i(0, -1),
    };

    for (auto thisCheck : toCheck) {
        if (isValid(currentNode + thisCheck) && !isFriend(currentNode + thisCheck)) {
            movements.push_back(thisCheck);
        }
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