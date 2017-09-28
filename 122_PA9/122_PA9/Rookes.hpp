#pragma once

#include "ChessPieces.hpp"

class Rookes : public ChessPieces
{
public:
	Rookes(Team newT);
	~Rookes();

	 void killOpponentPiece();

	 bool move(sf::Vector2i &newCoordinates);

	 bool checkPath();

	 int checkIfCheckmate(); // returns 0 if no, 1 if check, 2 if checkmate

	 char getType()
	 {
		 return this->type;
	 }

	 Team getTeam()
	 {
		 return this->t;
	 }
private:

};

Rookes::Rookes(Team newT)
{
	this->t = newT;
	tex.loadFromFile("White Rook.png");
	this->setTexture(&tex);

	type = 'R';
}

Rookes::~Rookes()
{

}

void Rookes::killOpponentPiece()
{

}

bool Rookes::move(sf::Vector2i &newCoordinates)
{
	this->setX(newCoordinates.x);
	this->setY(newCoordinates.y);

	return true;
}


bool Rookes::checkPath()
{
	return false;
}

int Rookes::checkIfCheckmate() // returns 0 if no, 1 if check, 2 if checkmate
{
	return 0;
}