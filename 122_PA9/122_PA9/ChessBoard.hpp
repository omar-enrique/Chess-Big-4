#include <SFML\Graphics.hpp>
#include <iostream>
#include "ChessPieces.hpp"

class ChessBoard : public sf::RectangleShape
{
public:
	ChessBoard();
	ChessBoard(const sf::Color &color, const sf::Vector2f &position, const sf::Vector2f &size);
	~ChessBoard();

	bool getIsOccupied();
	void setIsOccupied(bool &s);

	bool getIsSpecialMoveValid()
	{
		return isSpecialMoveValid;
	}
	void setIsSpecialMoveValid(bool &s)
	{
		isSpecialMoveValid = s;
	}
	void setChessPiece(ChessPieces *&piece);

	ChessPieces *& getChessPiece();  // Must return a pointer to a reference of the chess piece. Do not change.

	bool killChessPiece();
protected:
	bool spaceIsOccupied;
	bool isSpecialMoveValid;
	ChessPieces *piece; // Stores the chess piece that is currently located at the current chess board piece
};

ChessBoard::ChessBoard()
{

}

ChessBoard::ChessBoard(const sf::Color &color, const sf::Vector2f &position, const sf::Vector2f &size)
{
	this->setFillColor(color);
	this->setPosition(position);
	this->setSize(size);

	spaceIsOccupied = false;
	piece = nullptr;
	isSpecialMoveValid = false;
}

ChessBoard::~ChessBoard()
{

}

bool ChessBoard::getIsOccupied()
{
	return spaceIsOccupied;
}

void ChessBoard::setIsOccupied(bool &s)
{
	spaceIsOccupied = s;
}

void ChessBoard::setChessPiece(ChessPieces *&piece)
{
	this->piece = piece;
}

ChessPieces *& ChessBoard::getChessPiece()  // Must return a pointer to a reference of the chess piece. Do not change.
{
	return piece;
}

bool ChessBoard::killChessPiece()
{
	if (piece->getType() != 'K')
	{
		delete piece;
		return true;
	}
	switch (piece->getTeam())
	{
	case BLACK:
		std::cout << "White side wins!" << endl;
		break;
	case WHITE:
		std::cout << "Black side wins!" << endl;

		break;
	}
	exit(EXIT_SUCCESS);
	return true;
}