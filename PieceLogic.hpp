#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <algorithm>
class PieceLogic
{
	public:
		static std::vector<sf::Vector2i> getPossibleMovements(); 
		bool testIfMoveIsValid(sf::Vector2i delta);
		virtual void setPossibleMovements() {}
		virtual void setTextures() {}
	protected:
		static sf::Texture* pieceTexture;
		static std::vector<sf::Vector2i> possibleMovements;
		static void extend(sf::Vector2i extendDirection);
};
class PawnLogic : PieceLogic {
	public: 
		 void setPossibleMovements() override;
		 void setTextures() override;
};
/*
class Rook : PieceLogic {
	public: 
		 void setPossibleMovements() override;
		 void setTextures() override;
};
class Knight : PieceLogic {
	public: 
		 void setPossibleMovements() override;
		 void setTextures() override;
};
class Bishop : PieceLogic {
	public: 
		 void setPossibleMovements() override;
		 void setTextures() override;
};
class Queen : PieceLogic {
	public: 
		 void setPossibleMovements() override;
		 void setTextures() override;
};
class King : PieceLogic {
	public: 
		 void setPossibleMovements() override;
		 void setTextures() override;
};
*/
