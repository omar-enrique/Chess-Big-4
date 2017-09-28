#pragma once

#include "ChessPieces.hpp"

class Kings : public ChessPieces
{
public:
	Kings(Team newT);
	~Kings();

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

Kings::Kings(Team newT)
{
	this->t = newT;
	tex.loadFromFile("White King.png");
	this->setTexture(&tex);

	type = 'K';
}

Kings::~Kings()
{

}

void Kings::killOpponentPiece()
{

}

bool Kings::move(sf::Vector2i &newCoordinates)
{
	this->setX(newCoordinates.x);
	this->setY(newCoordinates.y);

	return true;
}


bool Kings::checkPath()
{
	return false;
}

int Kings::checkIfCheckmate() // returns 0 if no, 1 if check, 2 if checkmate
{
	return 0;
}