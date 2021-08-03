#include "Piece.hpp"  
Piece* Piece::board[8][8];
vector<Piece*> Piece::pieces;
sf::Vector2i Piece::spriteTexDem = sf::Vector2i(213,213);
sf::Texture Piece::piecesTexture;
void Piece::initPieces() {

    if(piecesTexture.loadFromFile("pieces.png")){
        std::cout << "texture loaded successfully! " << std::endl;
    }
    int tileWidth = Window::getSize().x/8; 
    int tileHeight = Window::getSize().y/8; 
    for(auto &itr : Piece::pieces){
        delete itr;
        pieces.pop_back(); 
    }
    for(int i =0;i<8;i++){
        for(int j = 0; j<8;j++){
            board[i][j] = nullptr;
        }
    }

    //making white pieces 
    
    for(int i =0; i<8; i++){
        Piece* curPiece = new PawnPiece;
        curPiece->setSpriteTex();
        curPiece->setPosition(sf::Vector2i(tileWidth*i,tileHeight));
        Piece::pieces.push_back(curPiece);
        Piece::board[1][i] = curPiece; 
    }
    
        // making white pawns 
    
    // making black pieces 

        // making black pawns 
}

Piece::Piece(){
    int roomWidth = Window::getSize().x;
    int roomHeight = Window::getSize().y; 
    float  scaleWidth = ((float)(roomWidth/8) / (float)Piece::spriteTexDem.x);
    std:: cout << "scale factor of the piece is " << scaleWidth << std::endl; 
    pieceSprite.setScale(scaleWidth,scaleWidth);
    pieceSprite.setColor(sf::Color(255, 255, 255));
}
PieceLogic* Piece::getPieceLogic() {
    return pieceLogic;
}
PieceTypes Piece::getPieceType() {
    return pieceType; 
    
}
PieceColors Piece::getPieceColor() {
    return pieceColor;
}
void Piece::setPosition(sf::Vector2i newPos) {
    
    pieceSprite.setPosition((newPos.x)*Window::getSize().x/8,(8-newPos.y)*Window::getSize().y/8);
   // pieceSprite.setPosition(5,5);
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
void Piece::render() {
    for(int row = 0; row<8; row++){
        for(int column=0; column<8;column++ ){
            if(board[row][column]!=nullptr ){
            //std::cout << "trying to render!" << std::endl;
            Window::draw(*board[row][column]->getSprite());
            }
        }
    }
}

sf::Sprite* Piece::getSprite() {
    return &pieceSprite; 
}

void PawnPiece::setSpriteTex() {
    pieceSprite.setTexture(Piece::piecesTexture);
    pieceSprite.setTextureRect(sf::IntRect(Piece::spriteTexDem.x*5,0,Piece::spriteTexDem.x,Piece::spriteTexDem.y)); 
}


