#include <cmath>
#include <iostream>
#include "Piece.hpp"  
#include "Window.hpp"
#include "ChessScreen.hpp"

/* ----------------- Static Definitions ------------------- */

Piece* Piece::board[8][8];
vector<Piece*> Piece::pieces;
sf::Texture Piece::piecesTexture;
sf::Vector2i Piece::spriteTexDem = sf::Vector2i(213, 213);

void Piece::initialize() {
    piecesTexture.loadFromFile("pieces.png");
}

void Piece::newBoard() {
    deletePieces();
    genPiecesOfColor(PieceColors::white);
    genPiecesOfColor(PieceColors::black);
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

sf::Vector2i Piece::getNodeFromScreenPosition(sf::Vector2i screenPosition) {
    int row = 7 - std::floor(screenPosition.y / ChessScreen::tileSize.y);
    int column = std::floor(screenPosition.x / ChessScreen::tileSize.x);
    return sf::Vector2i(column, row);
}

Piece* Piece::getFromScreenPosition(sf::Vector2i screenPosition) {
    sf::Vector2i thisNode = getNodeFromScreenPosition(screenPosition);
    return board[thisNode.y][thisNode.x];
}

bool Piece::isEmpty(sf::Vector2i atNode) {
    Piece* atPiece = board[atNode.y][atNode.x];
    return atPiece == NULL;
}

Piece* Piece::at(sf::Vector2i thisNode) {
    return board[thisNode.y][thisNode.x];
}

/*-------------------- Object Definitions -----------------*/ 


Piece::Piece() {
    float boardWidth = Window::getSize().x;
    float  scaleWidth = (boardWidth / 8.0) / Piece::spriteTexDem.x;
    sprite.setScale(scaleWidth, scaleWidth);
}

std::vector<sf::Vector2i> Piece::getPossibleMoves() {
    std::vector<sf::Vector2i> blank;
    return blank;
}

bool Piece::isValid(sf::Vector2i atNode) {
    return atNode.x >= 0 && atNode.x <= 7 && atNode.y >= 0 && atNode.y <= 7;
}

bool Piece::isEnemy(sf::Vector2i atNode) {
    Piece* atPiece = board[atNode.y][atNode.x];
    return atPiece != NULL && atPiece->getColor() != this->getColor();
}

bool Piece::isFriend(sf::Vector2i atNode) {
    Piece* atPiece = board[atNode.y][atNode.x];
    return atPiece != NULL && atPiece->getColor() == this->getColor();
}

bool Piece::isMoveValid(sf::Vector2i delta) {
    // Consider converting possible moves to unordered_set
    std::vector<sf::Vector2i> thisPossibleMoves = getPossibleMoves();
    for (sf::Vector2i thisPossibleMove : thisPossibleMoves) {
        if (delta == thisPossibleMove) return true;
    }

    return false;
}

PieceTypes Piece::getType() {
    return type; 
}

bool Piece::setType(PieceTypes newType) {
    type = newType; 
    return true; 
}

PieceColors Piece::getColor() {
    return color;
}

void Piece::setColor(PieceColors newColor) {
    color = newColor; 
}

sf::Vector2i Piece::flip(sf::Vector2i toFlipDirection) {
    if (getColor() == PieceColors::black) {
        return sf::Vector2i(toFlipDirection.x, -toFlipDirection.y);
    }

    return toFlipDirection;
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


void Piece::updateSprite() {
    sprite.setPosition(sf::Vector2f(currentNode.x * ChessScreen::tileSize.x, (7 - currentNode.y) * ChessScreen::tileSize.y));
} 

bool Piece::attemptMove(sf::Vector2i toNode) {
    sf::Vector2i deltaXY = toNode - currentNode;

    if(isMoveValid(deltaXY)) {
        board[currentNode.y][currentNode.x] = NULL;
        currentNode.x += deltaXY.x;
        currentNode.y += deltaXY.y;
        board[currentNode.y][currentNode.x] = this;

        hasMoved = true;
        updateSprite();
        
        return true;
    } 
    else {
        return false;
    }
}

void Piece::genPiecesOfColor(PieceColors color) {
    for(int j = 0; j<2; j++){
        for(int i = 0; i<8;i++){
            Piece* curPiece;
            if(j==0){
                if(i==0 || i ==7){
                    curPiece = new RookPiece;
                    curPiece->setType(PieceTypes::rook);
                }
                else if(i==1 || i ==6){
                    curPiece = new KnightPiece;
                    curPiece->setType(PieceTypes::knight);
                }
                else if(i==2 || i ==5){
                    curPiece = new BishopPiece;
                    curPiece->setType(PieceTypes::bishop);
                }
                else if(i == 3){
                    curPiece = new QueenPiece;
                    curPiece->setType(PieceTypes::queen);
                }
                else if(i == 4){
                    curPiece = new KingPiece;
                    curPiece->setType(PieceTypes::king);
                }
                else {
                    curPiece = new PawnPiece;
                    curPiece->setType(PieceTypes::pawn);
                }
            } 
            else {
                curPiece = new PawnPiece;
                curPiece->setType(PieceTypes::pawn);
            }
            if(color == PieceColors::white){
                curPiece->setColor(PieceColors::white);
                curPiece->getSprite()->setColor(sf::Color(150,0,0));
                curPiece->setCurrentNode(sf::Vector2i(i,j));
                Piece::board[j][i] = curPiece; 
            } else {
                curPiece->setColor(PieceColors::black);
                curPiece->getSprite()->setColor(sf::Color(0,0,150));
                curPiece->setCurrentNode(sf::Vector2i(i,7-j));
                Piece::board[7-j][i] = curPiece; 
            }
            curPiece->setSpriteTex();
            Piece::pieces.push_back(curPiece);
            curPiece->updateSprite();
        }
    }
}

void Piece::deletePieces() {
    for(auto &itr : Piece::pieces){
        delete itr;
        pieces.pop_back(); 
    }

    for(int i =0;i<8;i++){
        for(int j = 0; j<8;j++){
            Piece::board[i][j] = nullptr;
        }
    }
}