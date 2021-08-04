#pragma once
#include <vector>
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

        // Static Members 

		static Piece* board[8][8];
		static std::vector<Piece*> pieces;
		static sf::Vector2i spriteTexDem;

        static void initialize();
        static void render();   

		static void newBoard();
		static Piece* at(sf::Vector2i thisNode);
		static Piece* getFromScreenPosition(sf::Vector2i screenPosition);
		static sf::Vector2i getNodeFromScreenPosition(sf::Vector2i screenPosition);

		// Core logic 

		bool attemptMove(sf::Vector2i deltaXY);
		bool isEnemy(sf::Vector2i atNode);
		bool isFriend(sf::Vector2i atNode);
		static bool isEmpty(sf::Vector2i atNode);
		static bool isValid(sf::Vector2i atNode);

		bool isMoveValid(sf::Vector2i delta);
		virtual std::vector<sf::Vector2i> getPossibleMoves();	


        // Object members 

		void updateSprite();

		PieceTypes getType();
        bool setType(PieceTypes newType); 

		PieceColors getColor();
        void setColor(PieceColors newColor); 
		sf::Vector2i flip(sf::Vector2i toFlip);

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

		void extend(std::vector<sf::Vector2i> &movements, sf::Vector2i direction);
    
    private: 
		static void deletePieces();
		static void genPiecesOfColor(PieceColors color); 
};

class PawnPiece : public Piece {
	public: 
		void setSpriteTex() override; 
		std::vector<sf::Vector2i> getPossibleMoves() override;
};

class RookPiece : public Piece {
	public: 
		void setSpriteTex() override; 
		std::vector<sf::Vector2i> getPossibleMoves() override;
};

class KnightPiece : public Piece {
	public: 
		void setSpriteTex() override; 
		std::vector<sf::Vector2i> getPossibleMoves() override;
};

class BishopPiece : public Piece {
	public: 
		void setSpriteTex() override; 
		std::vector<sf::Vector2i> getPossibleMoves() override;
};

class QueenPiece : public Piece {
	public: 
		void setSpriteTex() override; 
		std::vector<sf::Vector2i> getPossibleMoves() override;
};

class KingPiece : public Piece {
	public: 
		void setSpriteTex() override; 
		std::vector<sf::Vector2i> getPossibleMoves() override;
};