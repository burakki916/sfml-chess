#include "Piece.hpp"  


Piece::Piece(PieceTypes PieceType)
{
	switch(PieceType){
        case Pawn:
            //set 
            break;
        case Rook:
            //set 
            break;
        case Knight:
            //set 
            break;
        case Bishop:
            //set 
            break;
        case Queen:
            //set 
            break;
        case King:
            //set
            break;
    }
}
PieceLogic* Piece::GetPieceLogic() {
    return pieceLogic;
}
PieceTypes Piece::GetPieceType() {
    return pieceType; 
}
PieceColors Piece::GetPieceColor() {
    return pieceColor;
}
void Piece::move(sf::Vector2i deltaXY) {
    //add logic later 
    if(pieceLogic->testIfMoveIsValid(deltaXY)){
            position.x += deltaXY.x;
            position.y += deltaXY.y;
            if(hasMoved == false ) hasMoved = true; 
    } else {
        std::cout << "Bad move retard! " << std::endl; // change this later lol 
    }
}

