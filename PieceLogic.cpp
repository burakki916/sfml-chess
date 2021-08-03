#include "PieceLogic.hpp"  
std::vector<sf::Vector2i> PieceLogic::possibleMovements;
sf::Texture* PieceLogic::pieceTexture;
bool PieceLogic::testIfMoveIsValid(sf::Vector2i delta) {
    auto pos = std::find(possibleMovements.begin(),possibleMovements.end(),delta);
    if(pos==possibleMovements.end()){
        return false; 
    } else {
        return true; 
    }
}
std::vector<sf::Vector2i> PieceLogic::getPossibleMovements() {
    return possibleMovements; 
}
void PieceLogic::extend(sf::Vector2i extendDirection) {
    for(int i =1; i<=8;i++){
        possibleMovements.push_back(sf::Vector2i(i*extendDirection.x,i*extendDirection.y));
    }
}
void PawnLogic::setPossibleMovements() {
    possibleMovements.push_back(sf::Vector2i(0,1));
    possibleMovements.push_back(sf::Vector2i(0,2));
    possibleMovements.push_back(sf::Vector2i(1,1));
    possibleMovements.push_back(sf::Vector2i(-1,1));
}
void PawnLogic::setTextures() {
    //
}
/*
void Rook::setPossibleMovements() {
    
}

void Rook::setTextures() {
    //
}

void Knight::setPossibleMovements() {
    
}

void Knight::setTextures() {
    //
}

void Bishop::setPossibleMovements() {
    
}

void Bishop::setTextures() {
    //
}

void Queen::setPossibleMovements() {
    
}

void Queen::setTextures() {
    //
}

void King::setPossibleMovements() {
    
}

void King::setTextures() {
    //
}
*/

