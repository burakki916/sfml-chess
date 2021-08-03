#include "Piece.hpp"  
Piece::Piece(){
    int roomWidth = Window::getSize().x;
    int roomHeight = Window::getSize().y; 
    float  scaleWidth = ((float)(roomWidth/8) / (float)Piece::spriteTexDem.x);
    pieceSprite.setScale(scaleWidth,scaleWidth);
    
}
/* ----------------- static piece information ------------------- */ 
Piece* Piece::board[8][8];
vector<Piece*> Piece::pieces;
sf::Vector2i Piece::spriteTexDem = sf::Vector2i(213,213);
sf::Texture Piece::piecesTexture;

void Piece::initPieces() {

    if(piecesTexture.loadFromFile("pieces.png")){
        std::cout << "texture loaded successfully! " << std::endl;
    }
    deletePieces();
    genPiecesOfColor(PieceColors::white);
    genPiecesOfColor(PieceColors::black);
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
Piece* Piece::getPieceFromMouse(sf::Vector2i mousePos) {
    int row = 7-std::floor((mousePos.y / ChessScreen::tileSize.y));
    int column = std::floor(mousePos.x / ChessScreen::tileSize.x);
    return board[row][column];
}
/*-------------------- general piece stuff -----------------*/ 
PieceLogic* Piece::getPieceLogic() {
    return pieceLogic;
}
bool Piece::setPieceLogic(PieceLogic& newLogic) {
    pieceLogic = &newLogic;
    return true; 
}
PieceTypes Piece::getPieceType() {
    return pieceType; 
}
bool Piece::setPieceType(PieceTypes newType) {
    pieceType = newType; 
    return true; 
}

PieceColors Piece::getPieceColor() {
    return pieceColor;
}
bool Piece::setPieceColor(PieceColors newColor) {
    pieceColor = newColor; 
}

sf::Sprite* Piece::getSprite() {
    return &pieceSprite; 
}

sf::Vector2i Piece::getPosition(){
    return position; 
}
bool Piece::setPosition(sf::Vector2i newPos) {
    //std::cout << "new pos is " << newPos.x << "," << newPos.y << std::endl; 
    pieceSprite.setPosition(sf::Vector2f(newPos.x*ChessScreen::tileSize.x, (7-newPos.y)* ChessScreen::tileSize.y));
    //std::cout << "Position on screen is " << pieceSprite.getPosition().x << "," << pieceSprite.getPosition().y << std::endl; 
    return true; 
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

void Piece::genPiecesOfColor(PieceColors color) {
    for(int j = 0; j<2; j++){
        for(int i = 0; i<8;i++){
            Piece* curPiece;
            if(j==0){
                if(i==0 || i ==7){
                    curPiece = new RookPiece;
                    curPiece->setPieceType(PieceTypes::rook);
                }
                else if(i==1 || i ==6){
                    curPiece = new KnightPiece;
                    curPiece->setPieceType(PieceTypes::knight);
                }
                else if(i==2 || i ==5){
                    curPiece = new BishopPiece;
                    curPiece->setPieceType(PieceTypes::bishop);
                }
                else if(i == 3){
                    curPiece = new QueenPiece;
                    curPiece->setPieceType(PieceTypes::queen);
                }
                else if(i == 4){
                    curPiece = new KingPiece;
                    curPiece->setPieceType(PieceTypes::king);
                }
                else {
                    curPiece = new PawnPiece;
                    curPiece->setPieceType(PieceTypes::pawn);
                }
            } 
            else {
                curPiece = new PawnPiece;
                curPiece->setPieceType(PieceTypes::pawn);
            }
            if(color == PieceColors::white){
                curPiece->setPieceColor(PieceColors::white);
                curPiece->getSprite()->setColor(sf::Color(150,0,0));
                curPiece->setPosition(sf::Vector2i(i,j));
                Piece::board[j][i] = curPiece; 
            } else {
                curPiece->setPieceColor(PieceColors::black);
                curPiece->getSprite()->setColor(sf::Color(0,0,150));
                curPiece->setPosition(sf::Vector2i(i,7-j));
                Piece::board[7-j][i] = curPiece; 
            }
            curPiece->setSpriteTex();
            Piece::pieces.push_back(curPiece);
            
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