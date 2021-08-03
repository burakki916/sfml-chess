#ifndef PIECE_H
#define PIECE_H
#pragma once
#include "Piece.hpp"
#include "PieceLogic.hpp"
#include "Window.hpp"
#include "ChessScreen.hpp"

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
		//static all pieces information 
		static void initPieces();
		static Piece* board[8][8];
		static vector<Piece*> pieces; 
		//end
		Piece();
		PieceLogic* getPieceLogic();
		PieceTypes getPieceType(); 
		PieceColors getPieceColor();

		void setPosition(sf::Vector2i newPos);
		void move(sf::Vector2i deltaXY);
		static void render(); 
		virtual void setSpriteTex() {}
		static sf::Vector2i spriteTexDem;
		sf::Sprite* getSprite(); 
	protected:
		PieceLogic* pieceLogic= nullptr;
		sf::Vector2i position = sf::Vector2i(0,0); 
		PieceColors pieceColor = PieceColors::black; 
		PieceTypes pieceType = pawn;
		bool hasMoved;
		static sf::Texture piecesTexture;
		sf::Sprite pieceSprite;
	private:
		static void deletePieces(); 
		static void genPiecesOfColor(PieceColors color); 
		 
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