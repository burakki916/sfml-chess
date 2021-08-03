#include "Piece.hpp"  
Piece* Piece::board[8][8];
vector<Piece*> Piece::pieces;
sf::Vector2i Piece::spriteTexDem = sf::Vector2i(213,213);
sf::Texture Piece::piecesTexture;
//this function is crazy 
void Piece::initPieces() { // super crazy 

    if(piecesTexture.loadFromFile("pieces.png")){
        std::cout << "texture loaded successfully! " << std::endl;
    }
    deletePieces();
    genPiecesOfColor(PieceColors::white);
    genPiecesOfColor(PieceColors::black);
}

Piece::Piece(){
    int roomWidth = Window::getSize().x;
    int roomHeight = Window::getSize().y; 
    float  scaleWidth = ((float)(roomWidth/8) / (float)Piece::spriteTexDem.x);
    pieceSprite.setScale(scaleWidth,scaleWidth);
    
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
    
    std::cout << "new pos is " << newPos.x << "," << newPos.y << std::endl; 
    pieceSprite.setPosition(sf::Vector2f(newPos.x*ChessScreen::tileSize.x, (7-newPos.y)* ChessScreen::tileSize.y));
    std::cout << "Position on screen is " << pieceSprite.getPosition().x << "," << pieceSprite.getPosition().y << std::endl; 
    //pieceSprite.setPosition(sf::Vector2f(5,5));
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
            Window::draw(*board[row][column]->getSprite());
            }
        }
    }
}

sf::Sprite* Piece::getSprite() {
    return &pieceSprite; 
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
void Piece::genPiecesOfColor(PieceColors color) {
    for(int j = 0; j<2; j++){
        for(int i = 0; i<8;i++){
            Piece* curPiece;
            if(j==0){
                if(i==0 || i ==7){
                    curPiece = new RookPiece;
                }
                else if(i==1 || i ==6){
                    curPiece = new KnightPiece;
                }
                else if(i==2 || i ==5){
                    curPiece = new BishopPiece;
                }
                else if(i == 3){
                    curPiece = new QueenPiece;
                }
                else if(i == 4){
                    curPiece = new KingPiece;
                }
                else {
                    curPiece = new PawnPiece;
                }
            } 
            else {
                curPiece = new PawnPiece;
            }
            if(color == PieceColors::white){
                curPiece->getSprite()->setColor(sf::Color(150,0,0));
                curPiece->setPosition(sf::Vector2i(i,j));
                Piece::board[j][i] = curPiece; 
            } else {
                curPiece->getSprite()->setColor(sf::Color(0,0,150));
                curPiece->setPosition(sf::Vector2i(i,7-j));
                Piece::board[7-j][i] = curPiece; 
            }
            curPiece->setSpriteTex();
            Piece::pieces.push_back(curPiece);
            
        }
    }
}

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



