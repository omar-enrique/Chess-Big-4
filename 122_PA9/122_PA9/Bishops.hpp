#pragma once

#include "ChessPieces.hpp"

class Bishops : public ChessPieces
{
public:
	Bishops(Team newT);
	~Bishops();

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

Bishops::Bishops(Team newT) 
{
	this->t = newT;
	tex.loadFromFile("White Bishop.png");
	this->setTexture(&tex);

	type = 'B';
}

Bishops::~Bishops()
{

}

void Bishops::killOpponentPiece()
{

}

bool Bishops::move(sf::Vector2i &newCoordinates)
{
	this->setX(newCoordinates.x);
	this->setY(newCoordinates.y);

	return true;
}


bool Bishops::checkPath()
{
	return false;
}

int Bishops::checkIfCheckmate() // returns 0 if no, 1 if check, 2 if checkmate
{
	return 0;
}