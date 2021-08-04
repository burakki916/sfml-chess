#include "Piece.hpp"
#include <iostream>

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

    // Right
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(i, 0);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

    // Left
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(-i, 0);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

    // Up
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(0, i);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

    // Down
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(0, -i);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

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

    // Up right
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(i, i);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

    // Up Left
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(-i, i);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

    // Down right
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(i, -i);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

    // Down left
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(-i, -i);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

    return movements;
}

std::vector<sf::Vector2i> QueenPiece::getPossibleMoves() {
    std::vector<sf::Vector2i> movements;

    // Right
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(i, 0);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

    // Left
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(-i, 0);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

    // Up
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(0, i);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

    // Down
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(0, -i);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

    // Up right
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(i, i);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

    // Up Left
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(-i, i);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

    // Down right
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(i, -i);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

    // Down left
    for (int i = 1; i < 8; i++) {
        sf::Vector2i toCheck(-i, -i);

        if (!isValid(currentNode + toCheck) || isFriend(currentNode + toCheck)) break;
        else if (isEmpty(currentNode + toCheck)) movements.push_back(toCheck);
        else if (isEnemy(currentNode + toCheck)) {
            movements.push_back(toCheck);
            break;
        }
    }

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