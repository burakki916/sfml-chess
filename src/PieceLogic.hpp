#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <algorithm>
class PieceLogic
{
	public:
		std::vector<sf::Vector2i> getPossibleMovements(); 
		bool testIfMoveIsValid(sf::Vector2i delta);
		virtual void setPossibleMovements();
		virtual void setTextures();
	protected:
		sf::Texture* pieceTexture;
		std::vector<sf::Vector2i> possibleMovements;
		void extend(sf::Vector2i extendDirection);
};
class Pawn : PieceLogic {
	public: 
		 void setPossibleMovements() override;
		 void setTextures() override;
};
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