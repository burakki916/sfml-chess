#include "Piece.hpp"
#include <iostream>

void Piece::extend(std::vector<sf::Vector2i>& movements, sf::Vector2i direction) {
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(direction.x * i, direction.y * i);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }
}

bool Piece::isInCheck(PieceColors color) {
    for (auto& thisPiece : pieces) { // For each piece
        if (thisPiece->getColor() != color) { // If it is an enemy
            for (auto& thisEnemyMovement : thisPiece->getPossibleMoves()) { // For each of their moves
                if (thisPiece->isEnemyKing(thisPiece->getCurrentNode() + thisEnemyMovement)) { // If they kill enemy (our) king
                    return true;
                }
            }
        }
    }

    return false;
}

bool Piece::isInCheckMate(PieceColors color) {
    for (auto& thisPiece : pieces) { // For each piece
        if (thisPiece->getColor() == color) { // If it ours
            std::vector<sf::Vector2i> possibleMoves = thisPiece->getPossibleMoves();
            if (thisPiece->keepKingSafe(possibleMoves).size() > 0) { // If it has a move
                return false;
            }
        }
    }

    return true;
}

std::vector<sf::Vector2i> Piece::keepKingSafe(std::vector<sf::Vector2i> &movements) {
    std::vector<sf::Vector2i> safeMovements;

    for (auto &thisMovement : movements) {
        // Temporary move to location
        board[currentNode.y][currentNode.x] = NULL;
        currentNode.x += thisMovement.x;
        currentNode.y += thisMovement.y;
        Piece* pieceCap = board[currentNode.y][currentNode.x];
        board[currentNode.y][currentNode.x] = this;

        if (pieceCap != NULL) { // Kill current piece
            for (auto i = pieces.begin(); i != pieces.end(); ++i) {
                if (pieceCap == *i) {
                    pieces.erase(i);
                    break;
                }
            }
        }

        if (!Piece::isInCheck(getColor())) safeMovements.push_back(thisMovement);

        // Move back
        if (pieceCap != NULL) pieces.push_back(pieceCap);
        board[currentNode.y][currentNode.x] = pieceCap;
        currentNode.x -= thisMovement.x;
        currentNode.y -= thisMovement.y;
        board[currentNode.y][currentNode.x] = this;
    }

    return safeMovements;
}

std::vector<sf::Vector2i> PawnPiece::getPossibleMoves() {
    std::vector<sf::Vector2i> movements;

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

std::vector<sf::Vector2i> RookPiece::getPossibleMoves() {
    std::vector<sf::Vector2i> movements;

    extend(movements, sf::Vector2i(1, 0));
    extend(movements, sf::Vector2i(-1, 0));
    extend(movements, sf::Vector2i(0, 1));
    extend(movements, sf::Vector2i(0, -1));

    return movements;
}

std::vector<sf::Vector2i> KnightPiece::getPossibleMoves() {
    std::vector<sf::Vector2i> movements;
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

std::vector<sf::Vector2i> BishopPiece::getPossibleMoves() {
    std::vector<sf::Vector2i> movements;

    extend(movements, sf::Vector2i(1, 1));
    extend(movements, sf::Vector2i(-1, 1));
    extend(movements, sf::Vector2i(1, -1));
    extend(movements, sf::Vector2i(-1, -1));

    return movements;
}



std::vector<sf::Vector2i> QueenPiece::getPossibleMoves() {
    std::vector<sf::Vector2i> movements;

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


std::vector<sf::Vector2i> KingPiece::getPossibleMoves() {
    std::vector<sf::Vector2i> movements;
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