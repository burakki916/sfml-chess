#include "Piece.hpp"  
#include "Window.hpp"
#include "ChessScreen.hpp"
#include <math.h>

/* ----------------- Static Definitions ------------------- */

Piece* Piece::board[8][8];
std::unordered_set<Piece*> Piece::pieces;

sf::Texture Piece::piecesTexture;
sf::Vector2i Piece::spriteTexDem = sf::Vector2i(213, 213);

sf::Color Piece::enemyHighlight = sf::Color(255, 50, 50);
sf::Color Piece::emptyHighlight = sf::Color(25, 125, 255);
sf::Color Piece::colors[2] = { sf::Color(0, 0, 150), sf::Color(150, 0, 0) };

void Piece::initialize() {
    piecesTexture.loadFromFile("pieces.png");
}

void Piece::render() {
    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 8; column++) {
            if (board[row][column] != nullptr) {
                Window::draw(*board[row][column]->getSprite());
            }
        }
    }
}

void Piece::newBoard() {
    deletePieces();
    genPiecesOfColor(PieceColors::white);
    genPiecesOfColor(PieceColors::black);
}

Piece* Piece::at(sf::Vector2i thisNode) {
    return board[thisNode.y][thisNode.x];
}

Piece* Piece::getFromScreenPosition(sf::Vector2i screenPosition) {
    sf::Vector2i thisNode = getNodeFromScreenPosition(screenPosition);
    return board[thisNode.y][thisNode.x];
}

sf::Vector2i Piece::getNodeFromScreenPosition(sf::Vector2i screenPosition) {
    int row = 7 - floor(screenPosition.y / ChessScreen::getTileSilze().y);
    int column = floor(screenPosition.x / ChessScreen::getTileSilze().x);
    return sf::Vector2i(column, row);
}

void Piece::deletePieces() {
    pieces.clear();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete Piece::board[i][j];
            Piece::board[i][j] = nullptr;
        }
    }
}

void Piece::genPiecesOfColor(PieceColors color) {
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 8; i++) {
            Piece* curPiece;
            if (j == 0) {
                if (i == 0 || i == 7) curPiece = new RookPiece;
                else if (i == 1 || i == 6) curPiece = new KnightPiece;
                else if (i == 2 || i == 5) curPiece = new BishopPiece;
                else if (i == 3) curPiece = new QueenPiece;
                else if (i == 4)  curPiece = new KingPiece;
                else curPiece = new PawnPiece;
            }
            else curPiece = new PawnPiece;

            curPiece->setColor(color);
            int row = color == PieceColors::white ? j : 7 - j;
            curPiece->setCurrentNode(sf::Vector2i(i, row));
            Piece::board[row][i] = curPiece;

            Piece::pieces.emplace(curPiece);
            curPiece->updateSprite();
        }
    }
}

/*-------------------- Core Logic -----------------*/ 

sf::Vector2i Piece::flip(sf::Vector2i toFlipDirection) {
    if (getColor() == PieceColors::black) return sf::Vector2i(toFlipDirection.x, -toFlipDirection.y);
   else return toFlipDirection;
}

bool Piece::isEnemy(sf::Vector2i atNode) {
    Piece* atPiece = board[atNode.y][atNode.x];
    return atPiece != NULL && atPiece->getColor() != this->getColor();
}

bool Piece::isFriend(sf::Vector2i atNode) {
    Piece* atPiece = board[atNode.y][atNode.x];
    return atPiece != NULL && atPiece->getColor() == this->getColor();
}

bool Piece::isEmpty(sf::Vector2i atNode) {
    Piece* atPiece = board[atNode.y][atNode.x];
    return atPiece == NULL;
}

bool Piece::isValid(sf::Vector2i atNode) {
    return atNode.x >= 0 && atNode.x <= 7 && atNode.y >= 0 && atNode.y <= 7;
}

bool Piece::isEnemyKing(sf::Vector2i atNode) {
    Piece* atPiece = board[atNode.y][atNode.x];
    return atPiece != NULL && atPiece->getColor() != this->getColor() && atPiece->getType() == PieceTypes::king;
}

bool Piece::isMoveValid(sf::Vector2i delta) {
    Piece::Moveset thisPossibleMoves = getPossibleMoves();
    keepKingSafe(thisPossibleMoves);
    for (sf::Vector2i &thisPossibleMove : thisPossibleMoves) {
        if (delta == thisPossibleMove) return true;
    }

    return false;
}

bool Piece::attemptMove(sf::Vector2i toNode) {
    sf::Vector2i deltaXY = toNode - currentNode;

    if (isMoveValid(deltaXY)) {
        board[currentNode.y][currentNode.x] = NULL;
        currentNode.x += deltaXY.x;
        currentNode.y += deltaXY.y;

        Piece* atPiece = board[currentNode.y][currentNode.x];

        if (atPiece != NULL) { // Kill current piece
            pieces.erase(pieces.find(atPiece));
            delete board[currentNode.y][currentNode.x];
        }

        board[currentNode.y][currentNode.x] = this;

        hasMoved = true;
        updateSprite();

        return true;
    }
    else {
        return false;
    }
}

Piece::Moveset Piece::getPossibleMoves() {
    Piece::Moveset blank;
    return blank;
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
            Piece::Moveset possibleMoves = thisPiece->getPossibleMoves();
            thisPiece->keepKingSafe(possibleMoves);
            if (possibleMoves.size() > 0) { // If it has a move
                return false;
            }
        }
    }

    return true;
}

void Piece::keepKingSafe(Piece::Moveset& movements) {
    auto thisMovement = movements.begin();
    while (thisMovement != movements.end()) {
        // Temporary move to location
        board[currentNode.y][currentNode.x] = NULL;
        currentNode.x += thisMovement->x;
        currentNode.y += thisMovement->y;
        Piece* pieceCap = board[currentNode.y][currentNode.x];
        board[currentNode.y][currentNode.x] = this;

        if (pieceCap != NULL) { // Would kill piece
            pieces.erase(pieces.find(pieceCap));
        }

        bool allowsKingDeath = Piece::isInCheck(getColor());

        // Move back
        if (pieceCap != NULL) pieces.emplace(pieceCap);
        board[currentNode.y][currentNode.x] = pieceCap;
        currentNode.x -= thisMovement->x;
        currentNode.y -= thisMovement->y;
        board[currentNode.y][currentNode.x] = this;

        if (allowsKingDeath) thisMovement = movements.erase(thisMovement);
        else thisMovement++;
    }
}

void Piece::highlightPossibleMoves() {
    Piece::Moveset thisPossibleMoves = getPossibleMoves();
    keepKingSafe(thisPossibleMoves);
    for (sf::Vector2i &thisPossibleMove : thisPossibleMoves) {
        thisPossibleMove = thisPossibleMove + currentNode;
        if (isEnemy(thisPossibleMove)) ChessScreen::highlightTile(thisPossibleMove, enemyHighlight);
        else ChessScreen::highlightTile(thisPossibleMove, emptyHighlight);
    }
}

void Piece::extend(Piece::Moveset& movements, sf::Vector2i direction) {
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

/*-------------------- Object Definitions -----------------*/

Piece::Piece() {
    float boardWidth = Window::getSize().x;
    float  scaleWidth = (boardWidth / 8.0) / Piece::spriteTexDem.x;
    sprite.setScale(scaleWidth, scaleWidth);
}

void Piece::updateSprite() {
    sprite.setPosition(sf::Vector2f(currentNode.x * ChessScreen::getTileSilze().x, (7 - currentNode.y) * ChessScreen::getTileSilze().y));
}

PieceTypes Piece::getType() {
    return type; 
}

PieceColors Piece::getColor() {
    return color;
}

void Piece::setColor(PieceColors newColor) {
    color = newColor; 
    getSprite()->setColor(colors[(int)color]);
}

sf::Sprite* Piece::getSprite() {
    return &sprite; 
}

sf::Vector2i Piece::getCurrentNode() {
    return currentNode;
}

void Piece::setCurrentNode(sf::Vector2i newCurentNode) {
    currentNode = newCurentNode;
}