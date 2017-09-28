#pragma once

#include "ChessPieces.hpp"


class Queens : public ChessPieces
{
public:
	Queens(Team newT);
	 ~Queens(void);

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

Queens::Queens(Team newT)
{
	this->t = newT;
	tex.loadFromFile("White Queen.png");
	this->setTexture(&tex);

	type = 'Q';
}

Queens::~Queens()
{

}

void Queens::killOpponentPiece()
{

}

bool Queens::move(sf::Vector2i &newCoordinates)
{
	this->setX(newCoordinates.x);
	this->setY(newCoordinates.y);

	return true;
}


bool Queens::checkPath()
{
	return false;
}

int Queens::checkIfCheckmate() // returns 0 if no, 1 if check, 2 if checkmate
{
	return 0;
}