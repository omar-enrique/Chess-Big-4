#pragma once

#include <SFML\Graphics.hpp>
#include<SFML\Network.hpp>
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::string;

typedef enum Team {
	BLACK, WHITE
};
class ChessPieces : public sf::RectangleShape // Base Class for All of the Chess Pieces
{
public:
	ChessPieces();
	~ChessPieces();
	virtual void killOpponentPiece() = 0;

	virtual bool move(sf::Vector2i &newCoordinates) = 0;

	virtual bool checkPath() = 0;

	virtual int checkIfCheckmate() = 0; // returns 0 if no, 1 if check, 2 if checkmate

	virtual char getType() {
		return type;
	}

	virtual Team getTeam() {
		return t;
	}

	int getX();
	void setX(int newX);

	int getY();
	void setY(int newY);

	int getIndex();
	void setIndex(int i);

protected:
	int x; // Position on row of chess board
	int y; // Position on column of chess board
	int arrayIndex; // Stores the Chess Piece's index from the array it is stored in, very important for
	// deleting/killing off chess pieces.

	char type; // Stores what type of chess piece it is. For example, 'K' is for King.

	Team t; // Stores what team the chess piece is on.

	sf::Texture tex; // Stores the texture of the chess piece
};

ChessPieces::ChessPieces()
{

}
ChessPieces::~ChessPieces()
{

}
int ChessPieces::getX()
{
	return x;
}
void ChessPieces::setX(int newX)
{
	x = newX;
}

int ChessPieces::getY()
{
	return y;
}
void ChessPieces::setY(int newY)
{
	y = newY;
}

int ChessPieces::getIndex()
{
	return arrayIndex;
}

void ChessPieces::setIndex(int i)
{
	arrayIndex = i;
}