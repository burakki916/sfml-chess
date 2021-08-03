#ifndef PIECE_H
#define PIECE_H
#pragma once
#include <cmath>
#include "PieceLogic.hpp"
#include "Window.hpp"
#include "ChessScreen.hpp"
#include "EventManager.hpp"

enum PieceTypes{
	pawn,
	rook,
	knight,
	bishop,
	queen,
	king,
};
enum PieceColors{
	black,
	white,
};
class Piece{
	public:
        Piece();

        /* ----------------- static piece information ------------------- */ 
        static void initPieces();
        static void render();
        static Piece* board[8][8];
		static vector<Piece*> pieces; 
        static Piece* getPieceFromMouse(sf::Vector2i mousePos);
        static sf::Vector2i spriteTexDem; 

        /* -------------------- individual piece stuff--------------------*/ 
        PieceLogic* getPieceLogic();
        bool setPieceLogic(PieceLogic& newLogic); 

		PieceTypes getPieceType();
        bool setPieceType(PieceTypes newType); 

		PieceColors getPieceColor();
        bool setPieceColor(PieceColors newColor); 

		sf::Sprite* getSprite();
        virtual void setSpriteTex() {}

        sf::Vector2i getPosition(); 
        bool setPosition(sf::Vector2i newPos);
        void move(sf::Vector2i deltaXY); // move to setPosition ?
    protected: 
        PieceLogic* pieceLogic= nullptr;
        PieceTypes pieceType = pawn;
        PieceColors pieceColor = PieceColors::black;
        sf::Sprite pieceSprite;
        sf::Vector2i position = sf::Vector2i(0,0); 
        static sf::Texture piecesTexture;

        bool hasMoved; 
    private: 
		static void genPiecesOfColor(PieceColors color); 
        static void deletePieces(); 

};
class PawnPiece : public Piece {
	public: 
		void setSpriteTex() override; 
};
class RookPiece : public Piece {
	public: 
		void setSpriteTex() override; 
};
class KnightPiece : public Piece {
	public: 
		void setSpriteTex() override; 
};
class BishopPiece : public Piece {
	public: 
		void setSpriteTex() override; 
};
class QueenPiece : public Piece {
	public: 
		void setSpriteTex() override; 
};
class KingPiece : public Piece {
	public: 
		void setSpriteTex() override; 
};
#endif