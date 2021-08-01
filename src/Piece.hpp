#ifndef PIECE_H
#define PIECE_H
#pragma once
#include "Piece.hpp"
#include "PieceLogic.hpp"
#include "Window.hpp"
enum PieceTypes{
	Pawn,
	Rook,
	Knight,
	Bishop,
	Queen,
	King,
};
enum PieceColors{
	Black,
	White,
};
class Piece{
	public:
		Piece(PieceTypes PieceType);
		PieceLogic* GetPieceLogic();
		PieceTypes GetPieceType(); 
		PieceColors GetPieceColor();

		void setPosition(sf::Vector2i newPos);
		void move(sf::Vector2i deltaXY);
		void render(Window* l_window); 
	private:
		PieceLogic* pieceLogic= nullptr;
		sf::Vector2i position = sf::Vector2i(0,0); 
		PieceColors pieceColor = PieceColors::Black; 
		PieceTypes pieceType; 
};

#endif