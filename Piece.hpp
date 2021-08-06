#pragma once
#include <deque>
#include <vector>
#include <unordered_set>
#include "SFML/Graphics.hpp"

enum class PieceTypes {
	pawn,
	rook,
	knight,
	bishop,
	queen,
	king,
};

enum class PieceColors {
	black,
	white,
};

class Piece {
	public:
		typedef std::deque<sf::Vector2i> Moveset;

        // == Main static members == //

        static void initialize();
        static void render();   

		static void newBoard();
		static Piece* at(sf::Vector2i thisNode);
		static Piece* getFromScreenPosition(sf::Vector2i screenPosition);
		static sf::Vector2i getNodeFromScreenPosition(sf::Vector2i screenPosition);

		// == Core logic == //

		sf::Vector2i flip(sf::Vector2i toFlipDirection); // Flip direction vector based on color

		bool isEnemy(sf::Vector2i atNode);
		bool isFriend(sf::Vector2i atNode);
		static bool isEmpty(sf::Vector2i atNode);
		static bool isValid(sf::Vector2i atNode);
		bool isEnemyKing(sf::Vector2i atNode);

		bool isMoveValid(sf::Vector2i delta);
		bool attemptMove(sf::Vector2i deltaXY);
		virtual Piece::Moveset getPossibleMoves();
		
		static bool isInCheck(PieceColors color);
		static bool isInCheckMate(PieceColors color);
		void keepKingSafe(Piece::Moveset&movements);
		
		void highlightPossibleMoves();

        // == Object members == //

		Piece();

		virtual PieceTypes getType();

		PieceColors getColor();
        void setColor(PieceColors newColor); 	

		sf::Sprite* getSprite();
        virtual void setSpriteTex() {}

		sf::Vector2i getCurrentNode();
		void setCurrentNode(sf::Vector2i newCurentNode);		

    protected: 
		static sf::Texture piecesTexture;
		static sf::Vector2i spriteTexDem;

		sf::Sprite sprite;
		bool hasMoved = false;
        PieceTypes type = PieceTypes::pawn;
		PieceColors color = PieceColors::black;
		sf::Vector2i currentNode = sf::Vector2i(0, 0);

		void updateSprite(); // Move sprite to current node
		void extend(Piece::Moveset &movements, sf::Vector2i direction); // Helper function for getPossibleMoves
    
    private: 
		static Piece* board[8][8];
		static std::unordered_set<Piece*> pieces;

		static sf::Color enemyHighlight;
		static sf::Color emptyHighlight;
		static sf::Color colors[2];

		static void deletePieces();
		static void genPiecesOfColor(PieceColors color); 
};

class PawnPiece : public Piece {
	public:
		PawnPiece() {
			type = PieceTypes::pawn;
			setSpriteTex();
		}

		void setSpriteTex() override; 
		Piece::Moveset getPossibleMoves() override;
};

class RookPiece : public Piece {
	public: 
		RookPiece() {
			type = PieceTypes::rook;
			setSpriteTex();
		}

		void setSpriteTex() override; 
		Piece::Moveset getPossibleMoves() override;
};

class KnightPiece : public Piece {
	public: 
		KnightPiece() {
			type = PieceTypes::knight;
			setSpriteTex();
		}

		void setSpriteTex() override; 
		Piece::Moveset getPossibleMoves() override;
};

class BishopPiece : public Piece {
	public: 
		BishopPiece() {
			type = PieceTypes::bishop;
			setSpriteTex();
		}

		void setSpriteTex() override; 
		Piece::Moveset getPossibleMoves() override;
};

class QueenPiece : public Piece {
	public: 
		QueenPiece() {
			type = PieceTypes::queen;
			setSpriteTex();
		}

		void setSpriteTex() override; 
		Piece::Moveset getPossibleMoves() override;
};

class KingPiece : public Piece {
	public: 
		KingPiece() {
			type = PieceTypes::king;
			setSpriteTex();
		}

		void setSpriteTex() override; 
		Piece::Moveset getPossibleMoves() override;
};