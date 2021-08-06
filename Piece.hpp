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
        Piece();

        // == Static Members ==

		typedef std::deque<sf::Vector2i> Moveset;

		static Piece* board[8][8];
		static std::unordered_set<Piece*> pieces;

		static sf::Vector2i spriteTexDem;
		static sf::Color enemyHighlight;
		static sf::Color emptyHighlight;

        static void initialize();
        static void render();   

		static void newBoard();
		static Piece* at(sf::Vector2i thisNode);
		static Piece* getFromScreenPosition(sf::Vector2i screenPosition);
		static sf::Vector2i getNodeFromScreenPosition(sf::Vector2i screenPosition);

		// == Core logic ==

		// Flip direction vector based on color
		sf::Vector2i flip(sf::Vector2i toFlipDirection);

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

        // == Object members ==

		// Move sprite to current node
		void updateSprite();

		PieceTypes getType();
        bool setType(PieceTypes newType); 

		PieceColors getColor();
        void setColor(PieceColors newColor); 	

		sf::Sprite* getSprite();
        virtual void setSpriteTex() {}

		sf::Vector2i getCurrentNode();
		void setCurrentNode(sf::Vector2i newCurentNode);		

    protected: 
		static sf::Texture piecesTexture;

		sf::Sprite sprite;
		bool hasMoved = false;
        PieceTypes type = PieceTypes::pawn;
		PieceColors color = PieceColors::black;
		sf::Vector2i currentNode = sf::Vector2i(0, 0);

		// Helper function for getPossibleMoves
		void extend(Piece::Moveset &movements, sf::Vector2i direction);
    
    private: 
		static void deletePieces();
		static void genPiecesOfColor(PieceColors color); 
};

class PawnPiece : public Piece {
	public: 
		void setSpriteTex() override; 
		Piece::Moveset getPossibleMoves() override;
};

class RookPiece : public Piece {
	public: 
		void setSpriteTex() override; 
		Piece::Moveset getPossibleMoves() override;
};

class KnightPiece : public Piece {
	public: 
		void setSpriteTex() override; 
		Piece::Moveset getPossibleMoves() override;
};

class BishopPiece : public Piece {
	public: 
		void setSpriteTex() override; 
		Piece::Moveset getPossibleMoves() override;
};

class QueenPiece : public Piece {
	public: 
		void setSpriteTex() override; 
		Piece::Moveset getPossibleMoves() override;
};

class KingPiece : public Piece {
	public: 
		void setSpriteTex() override; 
		Piece::Moveset getPossibleMoves() override;
};