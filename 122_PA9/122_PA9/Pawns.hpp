#pragma once

#include "ChessPieces.hpp"

class Pawns : public ChessPieces
{
public:
	Pawns(Team newT);
	~Pawns();

	 void killOpponentPiece();

	 bool move(sf::Vector2i &newCoordinates);

	 bool checkPath();

	 int checkIfCheckmate(); // returns 0 if no, 1 if check, 2 if checkmate

	 int getNumMoves() const;

	 char getType()
	 {
		 return this->type;
	 }

	 Team getTeam()
	 {
		 return this->t;
	 }
private:
	int numMoves;
};

Pawns::Pawns(Team newT)
{
	this->t = newT;
	this->numMoves = 0;
	tex.loadFromFile("White Pawn.png");
	this->setTexture(&tex);

	type = 'P';

	numMoves = 0;
}

Pawns::~Pawns()
{
	
}

int Pawns::getNumMoves() const
{
	return this->numMoves;
}

void Pawns::killOpponentPiece()
{

}

bool Pawns::move(sf::Vector2i &newCoordinates)
{
	this->setX(newCoordinates.x);
	this->setY(newCoordinates.y);

	return true;
}


bool Pawns::checkPath()
{
	return false;
}

int Pawns::checkIfCheckmate() // returns 0 if no, 1 if check, 2 if checkmate
{
	return 0;
}