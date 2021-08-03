#include "Piece.hpp"  
void PawnPiece::setSpriteTex() {
    pieceSprite.setTexture(Piece::piecesTexture);
    pieceSprite.setTextureRect(sf::IntRect(Piece::spriteTexDem.x*5,0,Piece::spriteTexDem.x,Piece::spriteTexDem.y)); 
}
void RookPiece::setSpriteTex() {
    pieceSprite.setTexture(Piece::piecesTexture);
    pieceSprite.setTextureRect(sf::IntRect(Piece::spriteTexDem.x*4,0,Piece::spriteTexDem.x,Piece::spriteTexDem.y)); 
}

void KnightPiece::setSpriteTex() {
    pieceSprite.setTexture(Piece::piecesTexture);
    pieceSprite.setTextureRect(sf::IntRect(Piece::spriteTexDem.x*3,0,Piece::spriteTexDem.x,Piece::spriteTexDem.y)); 
}

void BishopPiece::setSpriteTex() {
    pieceSprite.setTexture(Piece::piecesTexture);
    pieceSprite.setTextureRect(sf::IntRect(Piece::spriteTexDem.x*2,0,Piece::spriteTexDem.x,Piece::spriteTexDem.y));     
}

void QueenPiece::setSpriteTex() {
    pieceSprite.setTexture(Piece::piecesTexture);
    pieceSprite.setTextureRect(sf::IntRect(Piece::spriteTexDem.x*1,0,Piece::spriteTexDem.x,Piece::spriteTexDem.y));     
}

void KingPiece::setSpriteTex() {
    pieceSprite.setTexture(Piece::piecesTexture);
    pieceSprite.setTextureRect(sf::IntRect(Piece::spriteTexDem.x*0,0,Piece::spriteTexDem.x,Piece::spriteTexDem.y));     
}