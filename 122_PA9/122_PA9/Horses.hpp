#pragma once

#include "ChessPieces.hpp"

class Horses : public ChessPieces
{
public:
	Horses(Team newT);
	~Horses();

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

Horses::Horses(Team newT)
{
	this->t = newT;
	tex.loadFromFile("White Horse.png");
	this->setTexture(&tex);

	type = 'H';
}

Horses::~Horses()
{

}

void Horses::killOpponentPiece()
{

}

bool Horses::move(sf::Vector2i &newCoordinates)
{
	this->setX(newCoordinates.x);
	this->setY(newCoordinates.y);

	return true;
}


bool Horses::checkPath()
{
	return false;
}

int Horses::checkIfCheckmate() // returns 0 if no, 1 if check, 2 if checkmate
{
	return 0;
}

