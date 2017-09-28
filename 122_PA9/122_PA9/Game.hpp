#include "ChessPieces.hpp"
#include "ChessBoard.hpp"
#include "Bishops.hpp"
#include "Kings.hpp"
#include "Horses.hpp"
#include "Rookes.hpp"
#include "Pawns.hpp"
#include "Queens.hpp"

#define WIDTH 81.25
#define HEIGHT 81.25

class Game
{
public:
	Game(float width, float height);
	~Game();

	void drawBoard(sf::RenderWindow &win);

	void drawGame(sf::RenderWindow &win);

	bool checkIfPieceInSpot(sf::Vector2i &f, Team team);

	bool tryMovePiece(sf::Vector2i &start, sf::Vector2i &end, Team team);

	void shiftArrayPositions(ChessPieces *arr[], int startIndex, int length);

	bool moveKing(int &x1, int &x2, int &y1, int &y2, Team team);

	bool moveQueen(int &x1, int &x2, int &y1, int &y2, Team team);

	bool moveBishop(int &x1, int &x2, int &y1, int &y2, Team team);

	bool moveRooke(int &x1, int &x2, int &y1, int &y2, Team team);

	bool moveHorse(int &x1, int &x2, int &y1, int &y2, Team team);

	bool moveBlackPawn(int &x1, int &x2, int &y1, int &y2, Team team);

	bool moveWhitePawn(int &x1, int &x2, int &y1, int &y2, Team team);

	bool check(ChessPieces *&piece);

private:
	ChessBoard board[8][8]; // VERY IMPORTANT NOTE!!! : board[y-position][x-position] for entire project

	ChessPieces *blackTeam[16];
	ChessPieces *whiteTeam[16];

	sf::Text escapeText;
	sf::Font font;

	int totalTurns;

	int numBlackPieces;
	int numWhitePieces;
};

Game::Game(float width, float height) // VERY IMPORTANT NOTE!!! : board[y-position][x-position] for entire project
{
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}
	bool value = true;
	for (int r = 0; r < 8; r++) // This creates the chess Board, checkered style. Essential to understand how this works
	{
		for (int c = 0; c < 8; c++)
		{
			if (r % 2 == 0) // This is here so that every other row, the first tile of the row will be red, and in between will be white
			{
				if (c % 2 == 0) // This is here so that every column the tiles will change from red to white to red to white...
				{
					board[r][c].setFillColor(sf::Color(255, 193, 122));
					board[r][c].setPosition(sf::Vector2f(width / 8 * c, width / 8 * r));
					board[r][c].setSize(sf::Vector2f(width / 8, width / 8));
				}
				else
				{
					board[r][c].setFillColor(sf::Color(112, 84, 53));
					board[r][c].setPosition(sf::Vector2f(width / 8 * c, width / 8 * r));
					board[r][c].setSize(sf::Vector2f(width / 8, width / 8));
				}
			}
			else // This is here so that every other row, the first tile of the row will be red, and in between will be white
			{
				if ((c+1) % 2 == 0)
				{
					board[r][c].setFillColor(sf::Color(255, 193, 122));
					board[r][c].setPosition(sf::Vector2f(width / 8 * c, width / 8 * r));
					board[r][c].setSize(sf::Vector2f(width / 8, width / 8));
				}
				else
				{
					board[r][c].setFillColor(sf::Color(112, 84, 53));
					board[r][c].setPosition(sf::Vector2f(width / 8 * c, width / 8 * r));
					board[r][c].setSize(sf::Vector2f(width / 8, width / 8));
				}
			}

			if (r == 0 || r == 1 || r == 6 || r == 7)
			{
				value = true;
				board[r][c].setIsOccupied(value);
				if (r == 1 || r == 6) 
				{
					board[r][c].setIsSpecialMoveValid(value);
				}
			}
			else
			{
				value = false;
				board[r][c].setIsOccupied(value);
				board[r][c].setIsSpecialMoveValid(value);
			}
		}
	}

	for (int i = 0; i < 16; i++) //This for loop sets up the black team on the top side of the chess board
	{
		if (i < 8)
		{
			blackTeam[i] = new Pawns(BLACK);
			blackTeam[i]->setSize(sf::Vector2f(WIDTH, HEIGHT));
			blackTeam[i]->setPosition(sf::Vector2f(width / 2 - 325 + WIDTH * i, height / 2 - 325 + HEIGHT * 1));
			blackTeam[i]->setX(i);
			blackTeam[i]->setY(1);

			blackTeam[i]->setFillColor(sf::Color::Black);
		}
		else
		{
			if (i == 8)
				blackTeam[i] = new Rookes(BLACK);
			else if (i == 9)
				blackTeam[i] = new Horses(BLACK);
			else if (i == 10)
				blackTeam[i] = new Bishops(BLACK);
			else if (i == 11)
			{
				blackTeam[i] = new Queens(BLACK);
			}
			else if (i == 12)
				blackTeam[i] = new Kings(BLACK);
			else if (i == 13)
				blackTeam[i] = new Bishops(BLACK);
			else if (i == 14)
				blackTeam[i] = new Horses(BLACK);
			else
				blackTeam[i] = new Rookes(BLACK);

			blackTeam[i]->setX((i-8));
			blackTeam[i]->setY(0);
			blackTeam[i]->setFillColor(sf::Color::Black);

			blackTeam[i]->setSize(sf::Vector2f(WIDTH, HEIGHT));
			blackTeam[i]->setPosition(sf::Vector2f(width / 2 - 325 + WIDTH * (i - 8), height / 2 - 325 + HEIGHT * 0));
		}

		blackTeam[i]->setIndex(i);

		board[blackTeam[i]->getY()][blackTeam[i]->getX()].setChessPiece(blackTeam[i]);
	}

	for (int i = 0; i < 16; i++) //This for loop sets up the white team on the bottom side of the chess board
	{
		if (i < 8)
		{
			whiteTeam[i] = new Pawns(WHITE);
			whiteTeam[i]->setSize(sf::Vector2f(WIDTH, HEIGHT));
			whiteTeam[i]->setPosition(sf::Vector2f(width / 2 - 325 + WIDTH * i, height / 2 - 325 + HEIGHT * 6));
			whiteTeam[i]->setX(i);
			whiteTeam[i]->setY(6);
		}
		else
		{
			if (i == 8)
				whiteTeam[i] = new Rookes(WHITE);
			else if (i == 9)
				whiteTeam[i] = new Horses(WHITE);
			else if (i == 10)
				whiteTeam[i] = new Bishops(WHITE);
			else if (i == 11)
			{
				whiteTeam[i] = new Queens(WHITE);
			}
			else if (i == 12)
				whiteTeam[i] = new Kings(WHITE);
			else if (i == 13)
				whiteTeam[i] = new Bishops(WHITE);
			else if (i == 14)
				whiteTeam[i] = new Horses(WHITE);
			else
				whiteTeam[i] = new Rookes(WHITE);

			whiteTeam[i]->setX((i - 8));
			whiteTeam[i]->setY(7);

			whiteTeam[i]->setSize(sf::Vector2f(WIDTH, HEIGHT));
			whiteTeam[i]->setPosition(sf::Vector2f(width / 2 - 325 + WIDTH * (i - 8), height / 2 - 325 + HEIGHT * 7));
		}
		whiteTeam[i]->setIndex(i);

		board[whiteTeam[i]->getY()][whiteTeam[i]->getX()].setChessPiece(whiteTeam[i]);
	}

	escapeText.setFont(font);
	escapeText.setString("Press \'ESC\' to exit out of game.");
	escapeText.setColor(sf::Color::White);
	escapeText.setPosition(sf::Vector2f(0, 0));
	escapeText.setCharacterSize(16);

	totalTurns = 0;

	numBlackPieces = 16;
	numWhitePieces = 16;
}

Game::~Game()
{
	for (int i = 0; i < 16; i++)
	{
		if (numBlackPieces > i)
			delete blackTeam[i];

		if (numWhitePieces > i)
			delete whiteTeam[i];
	}
}

void Game::drawBoard(sf::RenderWindow &win)
{
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			win.draw(board[r][c]); // Draws the entire board to the screen
		}
	}
}

void Game::drawGame(sf::RenderWindow &win)
{
	drawBoard(win); //Must be executed before anything else so that everything else is drawn ABOVE the board

	for (int c = 0; c < 16; c++)
	{
		if(numBlackPieces > c)
			win.draw(*blackTeam[c]); // Draws the black and white pieces to the screen
	
		if (numWhitePieces > c)
			win.draw(*whiteTeam[c]);
	}

	win.draw(escapeText);

}

/*
		Function: bool checkIfPieceInSpot(sf::Vector2i &f, Team team)
		Description: This function checks to see if the position the user clicked is a valid chess piece that they can select.
		Parameters: sf::Vector2i &start, sf::Vector2i &end, Team team
		Precondition: This function must receive the team that the current user is on, so it can determine if the chess piece selected is
			a chess piece associated to their team.  It must also receive the pixel position of the object the user is trying to click.
		Postcondition: Returns true if the user's selected object is a valid chess piece. False if it's not. 
		Returns: bool value
*/
bool Game::checkIfPieceInSpot(sf::Vector2i &f, Team team) 
{
	int x = 0, y = 0;

	x = f.x / 81.25; // Converts x pixels selected to the x index of the board
	y = f.y / 81.25; // Converts y pixels selected to the y index of the board

	if (board[y][x].getIsOccupied() == true && board[y][x].getChessPiece()->getTeam() == team)
		return true;
	else
		return false;
}

/*
		Function: bool tryMovePiece(sf::Vector2i &start, sf::Vector2i &end, Team team)
		Description: This function can only be executed iff a user has previously selected a valid chess piece and the checkIfPieceInSpot()
			function returned true. This function trys to move the chess piece selected to the position the user chose.
		Parameters: sf::Vector2i &start, sf::Vector2i &end, Team team
		Precondition: This function can only be executed iff a user has previously selected a valid chess piece and the checkIfPieceInSpot()
			function returned true. Must receive the pixel position of the chess piece the user selected and the pixel position of the box
			where the user wants to move the chess piece.
		Postcondition: Returns true if the user could move the chess piece to desired location and false if not.
		Returns: bool value
*/
bool Game::tryMovePiece(sf::Vector2i &start, sf::Vector2i &end, Team team)
{
	bool value = false;

	int deletedIndex = 0;

	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	bool inCheck = false;

	x1 = start.x / 81.25; // Converts x pixels selected to the x index of the board
	y1 = start.y / 81.25; // Converts y pixels selected to the y index of the board
	x2 = end.x / 81.25; // Converts x pixels selected to the x index of the board
	y2 = end.y / 81.25; // Converts y pixels selected to the y index of the board

	if (x1 == x2 && y1 == y2)
		return false;

	if (board[y1][x1].getChessPiece()->getType() == 'K')
	{
		if (moveKing(x1, x2, y1, y2, team))
		{
			inCheck = check(board[y2][x2].getChessPiece());

			return true;
		}
		else
		{
			return false;
		}
	}
	if (board[y1][x1].getChessPiece()->getType() == 'Q')
	{
		if(moveQueen(x1, x2, y1, y2, team))
		{
			inCheck = check(board[y2][x2].getChessPiece());

			return true;
		}
		else
		{
			return false;
		}
	}
	if (board[y1][x1].getChessPiece()->getType() == 'R')
	{
		if (moveRooke(x1, x2, y1, y2, team))
		{
			inCheck = check(board[y2][x2].getChessPiece());

			return true;
		}
		else
		{
			return false;
		}
	}
	if (board[y1][x1].getChessPiece()->getType() == 'B')
	{
		if (moveBishop(x1, x2, y1, y2, team))
		{
			inCheck = check(board[y2][x2].getChessPiece());

			return true;
		}
		else
		{
			return false;
		}
	}
	if (board[y1][x1].getChessPiece()->getType() == 'H')
	{
		if (moveHorse(x1, x2, y1, y2, team))
		{
			inCheck = check(board[y2][x2].getChessPiece());

			return true;
		}
		else
		{
			return false;
		}
	}
	if (board[y1][x1].getChessPiece()->getType() == 'P' && team == WHITE)
	{	
		if (moveWhitePawn(x1, x2, y1, y2, team))
		{
			inCheck = check(board[y2][x2].getChessPiece());

			return true;
		}
		else
		{
			return false;
		}
	}
	if (board[y1][x1].getChessPiece()->getType() == 'P' && team == BLACK)
	{
		if (moveBlackPawn(x1, x2, y1, y2, team))
		{
			inCheck = check(board[y2][x2].getChessPiece());

			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

/*
		Function: void shiftArrayPositions(ChessPieces *arr[], int startIndex, int length)
		Description: This function is designed to shift an array of chess pieces after a chess piece has been killed.  If a chess piece dies
			it's memory is deleted, which will cause an error if we try to draw the array of chess pieces to the board again.  So this
			is designed to shift the array so that there are no gaps in the array.
		Parameters: ChessPieces *arr[], int startIndex, int length
		Precondition: Needs the array whose chess piece was killed. Needs the index of the Chess piece that was deleted, so that the shift 
			down of the array can begin at the index that has no memory.
		Postcondition: The array has been shifted. After this function is ran the number of chess pieces in this array MUST be reduced by 1.
			The game class keeps track of the number of chess pieces on each team (in each array). If the number of chess pieces for the
			array that was passed in is not reduced, the program will have an error when drawing the chess pieces.
		Returns: none
*/
void Game::shiftArrayPositions(ChessPieces *arr[], int startIndex, int length)
{
	ChessPieces *pNext = arr[startIndex+1];

	for (int i = startIndex + 1; i < length; i++)
	{
		if (i == length - 1)
		{
			arr[i]->setIndex(i - 1);
			arr[i - 1] = arr[i];
			arr[i] = nullptr;
		}
		else
		{
			arr[i]->setIndex(i-1);
			arr[i - 1] = arr[i];
		}
	}
}

/*
		Function: bool moveKing(int &x1, int &x2, int &y1, int &y2, Team team)
		Description: This function moves the king from its orignal x and y coordinates to its new x and y coordinates determined by
			mouse clicks.  This function contains a series of checks that are exclusive to a king, which check if the position it wants to
			go to is occupied, if the user is trying to kill an opponent's chess piece, if there are any pieces between the king and the
			position it wants to move to, and if the user is not clicking a position the King piece simply cannot reach.
		Parameters: int &x1, int &x2, int &y1, int &y2, Team team
		Precondition: This function will only run if the user clicked a valid chess piece to move, that is, if the user clicked one of their
			remaining chess pieces on the board, the one that corresponds to their team. The function will pass in the original x and y
			position of the chess piece with respect to the Chess Board's indexes and will pass in the position the user wants to move
			the chess piece too.  The function must also take in the team the current user is on, to determine kill moves.
		Postcondition: Returns true if the king was able to move to the position which the user wanted to move to, and false if the king
			could not move to the user's desired position
		Returns: bool value
	*/
bool Game::moveKing(int &x1, int &x2, int &y1, int &y2, Team team)
{
	bool value = false;

	int deletedIndex = 0;

	if ((x1 - 1 == x2 && y1 == y2) || (x1 + 1 == x2 && y1 == y2) || (x1 == x2 && y1 + 1 == y2) || (x1 == x2 && y1 - 1 == y2) || (x1 + 1 == x2 && y1 == y2) || (x1 - 1 == x2 && y1 == y2) || (x1 + 1 == x2 && y1 + 1 == y2) || (x1 - 1 == x2 && y1 + 1 == y2) || (x1 - 1 == x2 && y1 - 1 == y2) || (x1 + 1 == x2 && y1 - 1 == y2))
	{
		if (board[y2][x2].getIsOccupied())
		{
			if (board[y2][x2].getChessPiece()->getTeam() != team)
			{
				deletedIndex = board[y2][x2].getChessPiece()->getIndex();
				board[y2][x2].killChessPiece();

				if (team == WHITE)
				{
					shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
					numBlackPieces--;
				}
				else
				{
					shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
					numWhitePieces--;
				}

				board[y2][x2].getChessPiece() = new Kings(team);

				board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

				board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

				board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

				board[y1][x1].getChessPiece() = nullptr;

				value = true;
				board[y2][x2].setIsOccupied(value);

				value = false;
				board[y1][x1].setIsOccupied(value);

				return true;
			}
			else
				return false;
		}
		else
		{
			board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

			board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

			board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

			board[y1][x1].getChessPiece() = nullptr;

			value = true;
			board[y2][x2].setIsOccupied(value);

			value = false;
			board[y1][x1].setIsOccupied(value);

			return true;
		}
	}
}

/*
		Function: bool moveQueen(int &x1, int &x2, int &y1, int &y2, Team team)
		Description: This function moves the Queen from its orignal x and y coordinates to its new x and y coordinates determined by
			mouse clicks.  This function contains a series of checks that are exclusive to a Queen, which check if the position it wants to
			go to is occupied, if the user is trying to kill an opponent's chess piece, if there are any pieces between the Queen and the
			position it wants to move to, and if the user is not clicking a position the Queen piece simply cannot reach.
		Parameters: int &x1, int &x2, int &y1, int &y2, Team team
		Precondition: This function will only run if the user clicked a valid chess piece to move, that is, if the user clicked one of their
			remaining chess pieces on the board, the one that corresponds to their team. The function will pass in the original x and y
			position of the chess piece with respect to the Chess Board's indexes and will pass in the position the user wants to move
			the chess piece too.  The function must also take in the team the current user is on, to determine kill moves.
		Postcondition: Returns true if the Queen was able to move to the position which the user wanted to move to, and false if the Queen
			could not move to the user's desired position
		Returns: bool value
	*/
bool Game::moveQueen(int &x1, int &x2, int &y1, int &y2, Team team)
{
	int tempX = x1;
	int tempY = y1;

	bool value = false;
	bool blockedPath = false;

	int deletedIndex = 0;

	if (y2 > y1 && x2 > x1)
	{
		if (abs(y2 - y1) == abs(x2 - x1))
		{
			for (int i = 1; i <= abs(y2 - y1); i++)
			{
				if (board[y1 + i][x1 + i].getIsOccupied() && y1 + i == y2 && x1 + i == x2)
				{
					if (board[y2][x2].getChessPiece()->getTeam() != team)
					{
						deletedIndex = board[y2][x2].getChessPiece()->getIndex();
						board[y2][x2].killChessPiece();

						if (team == WHITE)
						{
							shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
							numBlackPieces--;
						}
						else
						{
							shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
							numWhitePieces--;
						}

						board[y2][x2].getChessPiece() = new Queens(team);

						board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

						board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

						board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

						board[y1][x1].getChessPiece() = nullptr;

						value = true;
						board[y2][x2].setIsOccupied(value);

						value = false;
						board[y1][x1].setIsOccupied(value);

						return true;
					}
					else
					{
						return false;
					}

				}
				else
				{
					if (board[y1 + i][x1 + i].getIsOccupied())
					{
						return false;
					}
				}
			}

		}
		else
			return false;

	}
	else if (y2 > y1 && x2 < x1)
	{
		if (abs(y2 - y1) == abs(x2 - x1))
		{
			for (int i = 1; i <= abs(y2 - y1); i++)
			{
				if (board[y1 + i][x1 - i].getIsOccupied() && y1 + i == y2 && x1 - i == x2)
				{
					if (board[y2][x2].getChessPiece()->getTeam() != team)
					{
						deletedIndex = board[y2][x2].getChessPiece()->getIndex();
						board[y2][x2].killChessPiece();

						if (team == WHITE)
						{
							shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
							numBlackPieces--;
						}
						else
						{
							shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
							numWhitePieces--;
						}

						board[y2][x2].getChessPiece() = new Queens(team);

						board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

						board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

						board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

						board[y1][x1].getChessPiece() = nullptr;

						value = true;
						board[y2][x2].setIsOccupied(value);

						value = false;
						board[y1][x1].setIsOccupied(value);

						return true;
					}
					else
					{
						return false;
					}

				}
				else
				{
					if (board[y1 + i][x1 - i].getIsOccupied())
					{
						return false;
					}
				}
			}
		}
		else
			return false;
	}
	else if (y2 < y1 && x2 < x1)
	{
		if (abs(y2 - y1) == abs(x2 - x1))
		{
			for (int i = 1; i <= abs(y2 - y1); i++)
			{
				if (board[y1 - i][x1 - i].getIsOccupied() && y1 - i == y2 && x1 - i == x2)
				{
					if (board[y2][x2].getChessPiece()->getTeam() != team)
					{
						deletedIndex = board[y2][x2].getChessPiece()->getIndex();
						board[y2][x2].killChessPiece();

						if (team == WHITE)
						{
							shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
							numBlackPieces--;
						}
						else
						{
							shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
							numWhitePieces--;
						}

						board[y2][x2].getChessPiece() = new Queens(team);

						board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

						board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

						board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

						board[y1][x1].getChessPiece() = nullptr;

						value = true;
						board[y2][x2].setIsOccupied(value);

						value = false;
						board[y1][x1].setIsOccupied(value);

						return true;
					}
					else
					{
						return false;
					}

				}
				else
				{
					if (board[y1 - i][x1 - i].getIsOccupied())
					{
						return false;
					}
				}
			}
		}
		else
			return false;
	}
	else if (y2 < y1 && x2 > x1)
	{
		if (abs(y2 - y1) == abs(x2 - x1))
		{
			for (int i = 1; i <= abs(y2 - y1); i++)
			{
				if (board[y1 - i][x1 + i].getIsOccupied() && y1 - i == y2 && x1 + i == x2)
				{
					if (board[y2][x2].getChessPiece()->getTeam() != team)
					{
						deletedIndex = board[y2][x2].getChessPiece()->getIndex();
						board[y2][x2].killChessPiece();

						if (team == WHITE)
						{
							shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
							numBlackPieces--;
						}
						else
						{
							shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
							numWhitePieces--;
						}

						board[y2][x2].getChessPiece() = new Queens(team);

						board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

						board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

						board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

						board[y1][x1].getChessPiece() = nullptr;

						value = true;
						board[y2][x2].setIsOccupied(value);

						value = false;
						board[y1][x1].setIsOccupied(value);

						return true;
					}
					else
					{
						return false;
					}

				}
				else
				{
					if (board[y1 - i][x1 + i].getIsOccupied())
					{
						return false;
					}
				}
			}
		}
		else
			return false;
	}
	else if (x2 > x1)
	{
		for (int i = 1; i <= abs(x2 - x1); i++)
		{
			if (board[y1][x1 + i].getIsOccupied() && y1 == y2 && x1 + i == x2)
			{
				if (board[y2][x2].getChessPiece()->getTeam() != team)
				{
					deletedIndex = board[y2][x2].getChessPiece()->getIndex();
					board[y2][x2].killChessPiece();

					if (team == WHITE)
					{
						shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
						numBlackPieces--;
					}
					else
					{
						shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
						numWhitePieces--;
					}

					board[y2][x2].getChessPiece() = new Queens(team);

					board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

					board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

					board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

					board[y1][x1].getChessPiece() = nullptr;

					value = true;
					board[y2][x2].setIsOccupied(value);

					value = false;
					board[y1][x1].setIsOccupied(value);

					return true;
				}
				else
				{
					return false;
				}

			}
			else
			{
				if (board[y1][x1+i].getIsOccupied())
				{
					return false;
				}
			}
		}
	}
	else if (x2 < x1)
	{
		for (int i = 1; i <= abs(x2 - x1); i++)
		{
			if (board[y1][x1 - i].getIsOccupied() && y1 == y2 && x1 - i == x2)
			{
				if (board[y2][x2].getChessPiece()->getTeam() != team)
				{
					deletedIndex = board[y2][x2].getChessPiece()->getIndex();
					board[y2][x2].killChessPiece();

					if (team == WHITE)
					{
						shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
						numBlackPieces--;
					}
					else
					{
						shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
						numWhitePieces--;
					}

					board[y2][x2].getChessPiece() = new Queens(team);

					board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

					board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

					board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

					board[y1][x1].getChessPiece() = nullptr;

					value = true;
					board[y2][x2].setIsOccupied(value);

					value = false;
					board[y1][x1].setIsOccupied(value);

					return true;
				}
				else
				{
					return false;
				}

			}
			else
			{
				if (board[y1][x1-i].getIsOccupied())
				{
					return false;
				}
			}
		}
	}
	else if (y2 < y1)
	{
		for (int i = 1; i <= abs(y2 - y1); i++)
		{
			if (board[y1 - i][x1].getIsOccupied() && y1 - i == y2 && x1 == x2)
			{
				if (board[y2][x2].getChessPiece()->getTeam() != team)
				{
					deletedIndex = board[y2][x2].getChessPiece()->getIndex();
					board[y2][x2].killChessPiece();

					if (team == WHITE)
					{
						shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
						numBlackPieces--;
					}
					else
					{
						shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
						numWhitePieces--;
					}

					board[y2][x2].getChessPiece() = new Queens(team);

					board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

					board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

					board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

					board[y1][x1].getChessPiece() = nullptr;

					value = true;
					board[y2][x2].setIsOccupied(value);

					value = false;
					board[y1][x1].setIsOccupied(value);

					return true;
				}
				else
				{
					return false;
				}

			}
			else
			{
				if (board[y1 - i][x1].getIsOccupied())
				{
					return false;
				}
			}
		}
	}
	else if (y2 > y1)
	{
		for (int i = 1; i <= abs(y2 - y1); i++)
		{
			if (board[y1 + i][x1].getIsOccupied() && y1 + i == y2 && x1 == x2)
			{
				if (board[y2][x2].getChessPiece()->getTeam() != team)
				{
					deletedIndex = board[y2][x2].getChessPiece()->getIndex();
					board[y2][x2].killChessPiece();

					if (team == WHITE)
					{
						shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
						numBlackPieces--;
					}
					else
					{
						shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
						numWhitePieces--;
					}

					board[y2][x2].getChessPiece() = new Queens(team);

					board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

					board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

					board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

					board[y1][x1].getChessPiece() = nullptr;

					value = true;
					board[y2][x2].setIsOccupied(value);

					value = false;
					board[y1][x1].setIsOccupied(value);

					return true;
				}
				else
				{
					return false;
				}

			}
			else
			{
				if (board[y1 + i][x1].getIsOccupied())
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}

	board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

	board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

	board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

	board[y1][x1].getChessPiece() = nullptr;

	value = true;
	board[y2][x2].setIsOccupied(value);

	value = false;
	board[y1][x1].setIsOccupied(value);

	return true;
}

/*
		Function: bool moveBishop(int &x1, int &x2, int &y1, int &y2, Team team)
		Description: This function moves the Bishop from its orignal x and y coordinates to its new x and y coordinates determined by
			mouse clicks.  This function contains a series of checks that are exclusive to a Bishop, which check if the position it wants to
			go to is occupied, if the user is trying to kill an opponent's chess piece, if there are any pieces between the Bishop and the
			position it wants to move to, and if the user is not clicking a position the Bishop piece simply cannot reach.
		Parameters: int &x1, int &x2, int &y1, int &y2, Team team
		Precondition: This function will only run if the user clicked a valid chess piece to move, that is, if the user clicked one of their
			remaining chess pieces on the board, the one that corresponds to their team. The function will pass in the original x and y
			position of the chess piece with respect to the Chess Board's indexes and will pass in the position the user wants to move
			the chess piece too.  The function must also take in the team the current user is on, to determine kill moves.
		Postcondition: Returns true if the Bishop was able to move to the position which the user wanted to move to, and false if the Bishop
			could not move to the user's desired position
		Returns: bool value
	*/
bool Game::moveBishop(int &x1, int &x2, int &y1, int &y2, Team team)
{
	int tempX = x1;
	int tempY = y1;

	bool value = false;
	bool blockedPath = false;

	int deletedIndex = 0;

	if (y2 > y1 && x2 > x1)
	{
		if (abs(y2 - y1) == abs(x2 - x1))
		{
			for (int i = 1; i <= abs(y2 - y1); i++)
			{
				if (board[y1 + i][x1 + i].getIsOccupied() && y1 + i == y2 && x1 + i == x2)
				{
					if (board[y2][x2].getChessPiece()->getTeam() != team)
					{
						deletedIndex = board[y2][x2].getChessPiece()->getIndex();
						board[y2][x2].killChessPiece();

						if (team == WHITE)
						{
							shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
							numBlackPieces--;
						}
						else
						{
							shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
							numWhitePieces--;
						}

						board[y2][x2].getChessPiece() = new Bishops(team);

						board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

						board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

						board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

						board[y1][x1].getChessPiece() = nullptr;

						value = true;
						board[y2][x2].setIsOccupied(value);

						value = false;
						board[y1][x1].setIsOccupied(value);

						return true;
					}
					else
					{
						return false;
					}

				}
				else
				{
					if (board[y1 + i][x1 + i].getIsOccupied())
					{
						return false;
					}
				}
			}

		}
		else
			return false;

	}
	else if (y2 > y1 && x2 < x1)
	{
		if (abs(y2 - y1) == abs(x2 - x1))
		{
			for (int i = 1; i <= abs(y2 - y1); i++)
			{
				if (board[y1 + i][x1 - i].getIsOccupied() && y1 + i == y2 && x1 - i == x2)
				{
					if (board[y2][x2].getChessPiece()->getTeam() != team)
					{
						deletedIndex = board[y2][x2].getChessPiece()->getIndex();
						board[y2][x2].killChessPiece();

						if (team == WHITE)
						{
							shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
							numBlackPieces--;
						}
						else
						{
							shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
							numWhitePieces--;
						}

						board[y2][x2].getChessPiece() = new Bishops(team);

						board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

						board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

						board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

						board[y1][x1].getChessPiece() = nullptr;

						value = true;
						board[y2][x2].setIsOccupied(value);

						value = false;
						board[y1][x1].setIsOccupied(value);

						return true;
					}
					else
					{
						return false;
					}

				}
				else
				{
					if (board[y1 + i][x1 - i].getIsOccupied())
					{
						return false;
					}
				}
			}
		}
		else
			return false;
	}
	else if (y2 < y1 && x2 < x1)
	{
		if (abs(y2 - y1) == abs(x2 - x1))
		{
			for (int i = 1; i <= abs(y2 - y1); i++)
			{
				if (board[y1 - i][x1 - i].getIsOccupied() && y1 - i == y2 && x1 - i == x2)
				{
					if (board[y2][x2].getChessPiece()->getTeam() != team)
					{
						deletedIndex = board[y2][x2].getChessPiece()->getIndex();
						board[y2][x2].killChessPiece();

						if (team == WHITE)
						{
							shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
							numBlackPieces--;
						}
						else
						{
							shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
							numWhitePieces--;
						}

						board[y2][x2].getChessPiece() = new Bishops(team);

						board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

						board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

						board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

						board[y1][x1].getChessPiece() = nullptr;

						value = true;
						board[y2][x2].setIsOccupied(value);

						value = false;
						board[y1][x1].setIsOccupied(value);

						return true;
					}
					else
					{
						return false;
					}

				}
				else
				{
					if (board[y1 - i][x1 - i].getIsOccupied())
					{
						return false;
					}
				}
			}
		}
		else
			return false;
	}
	else if (y2 < y1 && x2 > x1)
	{
		if (abs(y2 - y1) == abs(x2 - x1))
		{
			for (int i = 1; i <= abs(y2 - y1); i++)
			{
				if (board[y1 - i][x1 + i].getIsOccupied() && y1 - i == y2 && x1 + i == x2)
				{
					if (board[y2][x2].getChessPiece()->getTeam() != team)
					{
						deletedIndex = board[y2][x2].getChessPiece()->getIndex();
						board[y2][x2].killChessPiece();

						if (team == WHITE)
						{
							shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
							numBlackPieces--;
						}
						else
						{
							shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
							numWhitePieces--;
						}

						board[y2][x2].getChessPiece() = new Bishops(team);

						board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

						board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

						board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

						board[y1][x1].getChessPiece() = nullptr;

						value = true;
						board[y2][x2].setIsOccupied(value);

						value = false;
						board[y1][x1].setIsOccupied(value);

						return true;
					}
					else
					{
						return false;
					}

				}
				else
				{
					if (board[y1 - i][x1 + i].getIsOccupied())
					{
						return false;
					}
				}
			}
		}
		else
			return false;
	}
	else
	{
		return false;
	}

	board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

	board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

	board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

	board[y1][x1].getChessPiece() = nullptr;

	value = true;
	board[y2][x2].setIsOccupied(value);

	value = false;
	board[y1][x1].setIsOccupied(value);

	return true;
}

/*
		Function: bool moveRooke(int &x1, int &x2, int &y1, int &y2, Team team)
		Description: This function moves the Rooke from its orignal x and y coordinates to its new x and y coordinates determined by
			mouse clicks.  This function contains a series of checks that are exclusive to a Rooke, which check if the position it wants to
			go to is occupied, if the user is trying to kill an opponent's chess piece, if there are any pieces between the Rooke and the
			position it wants to move to, and if the user is not clicking a position the Rooke piece simply cannot reach.
		Parameters: int &x1, int &x2, int &y1, int &y2, Team team
		Precondition: This function will only run if the user clicked a valid chess piece to move, that is, if the user clicked one of their
			remaining chess pieces on the board, the one that corresponds to their team. The function will pass in the original x and y
			position of the chess piece with respect to the Chess Board's indexes and will pass in the position the user wants to move
			the chess piece too.  The function must also take in the team the current user is on, to determine kill moves.
		Postcondition: Returns true if the Rooke was able to move to the position which the user wanted to move to, and false if the Rooke
			could not move to the user's desired position
		Returns: bool value
	*/
bool Game::moveRooke(int &x1, int &x2, int &y1, int &y2, Team team)
{
	int tempX = x1;
	int tempY = y1;

	bool value = false;
	bool blockedPath = false;

	int deletedIndex = 0;

	if (x2 > x1 && y1 == y2)
	{
		for (int i = 1; i <= abs(x2 - x1); i++)
		{
			if (board[y1][x1 + i].getIsOccupied() && y1 == y2 && x1 + i == x2)
			{
				if (board[y2][x2].getChessPiece()->getTeam() != team)
				{
					deletedIndex = board[y2][x2].getChessPiece()->getIndex();
					board[y2][x2].killChessPiece();

					if (team == WHITE)
					{
						shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
						numBlackPieces--;
					}
					else
					{
						shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
						numWhitePieces--;
					}

					board[y2][x2].getChessPiece() = new Rookes(team);

					board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

					board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

					board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

					board[y1][x1].getChessPiece() = nullptr;

					value = true;
					board[y2][x2].setIsOccupied(value);

					value = false;
					board[y1][x1].setIsOccupied(value);

					return true;
				}
				else
				{
					return false;
				}

			}
			else
			{
				if (board[y1][x1 + i].getIsOccupied())
				{
					return false;
				}
			}
		}
	}
	else if (x2 < x1 && y1 == y2)
	{
		for (int i = 1; i <= abs(x2 - x1); i++)
		{
			if (board[y1][x1 - i].getIsOccupied() && y1 == y2 && x1 - i == x2)
			{
				if (board[y2][x2].getChessPiece()->getTeam() != team)
				{
					deletedIndex = board[y2][x2].getChessPiece()->getIndex();
					board[y2][x2].killChessPiece();

					if (team == WHITE)
					{
						shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
						numBlackPieces--;
					}
					else
					{
						shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
						numWhitePieces--;
					}

					board[y2][x2].getChessPiece() = new Rookes(team);

					board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

					board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

					board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

					board[y1][x1].getChessPiece() = nullptr;

					value = true;
					board[y2][x2].setIsOccupied(value);

					value = false;
					board[y1][x1].setIsOccupied(value);

					return true;
				}
				else
				{
					return false;
				}

			}
			else
			{
				if (board[y1][x1 - i].getIsOccupied())
				{
					return false;
				}
			}
		}
	}
	else if (x2 == x1 && y2 < y1)
	{
		for (int i = 1; i <= abs(y2 - y1); i++)
		{
			if (board[y1 - i][x1].getIsOccupied() && y1 - i == y2 && x1 == x2)
			{
				if (board[y2][x2].getChessPiece()->getTeam() != team)
				{
					deletedIndex = board[y2][x2].getChessPiece()->getIndex();
					board[y2][x2].killChessPiece();

					if (team == WHITE)
					{
						shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
						numBlackPieces--;
					}
					else
					{
						shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
						numWhitePieces--;
					}

					board[y2][x2].getChessPiece() = new Rookes(team);

					board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

					board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

					board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

					board[y1][x1].getChessPiece() = nullptr;

					value = true;
					board[y2][x2].setIsOccupied(value);

					value = false;
					board[y1][x1].setIsOccupied(value);

					return true;
				}
				else
				{
					return false;
				}

			}
			else
			{
				if (board[y1 - i][x1].getIsOccupied())
				{
					return false;
				}
			}
		}
	}
	else if (x2 == x1 && y2 > y1)
	{
		for (int i = 1; i <= abs(y2 - y1); i++)
		{
			if (board[y1 + i][x1].getIsOccupied() && y1 + i == y2 && x1 == x2)
			{
				if (board[y2][x2].getChessPiece()->getTeam() != team)
				{
					deletedIndex = board[y2][x2].getChessPiece()->getIndex();
					board[y2][x2].killChessPiece();

					if (team == WHITE)
					{
						shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
						numBlackPieces--;
					}
					else
					{
						shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
						numWhitePieces--;
					}

					board[y2][x2].getChessPiece() = new Rookes(team);

					board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

					board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

					board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

					board[y1][x1].getChessPiece() = nullptr;

					value = true;
					board[y2][x2].setIsOccupied(value);

					value = false;
					board[y1][x1].setIsOccupied(value);

					return true;
				}
				else
				{ 
					return false;
				}

			}
			else
			{
				if (board[y1 + i][x1].getIsOccupied())
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}

	board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

	board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

	board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

	board[y1][x1].getChessPiece() = nullptr;

	value = true;
	board[y2][x2].setIsOccupied(value);

	value = false;
	board[y1][x1].setIsOccupied(value);

	return true;
}

/*
		Function: bool moveHorse(int &x1, int &x2, int &y1, int &y2, Team team)
		Description: This function moves the Horse from its orignal x and y coordinates to its new x and y coordinates determined by
			mouse clicks.  This function contains a series of checks that are exclusive to a Horse, which check if the position it wants to
			go to is occupied, if the user is trying to kill an opponent's chess piece, if there are any pieces between the Horse and the
			position it wants to move to, and if the user is not clicking a position the Horse piece simply cannot reach.
		Parameters: int &x1, int &x2, int &y1, int &y2, Team team
		Precondition: This function will only run if the user clicked a valid chess piece to move, that is, if the user clicked one of their
			remaining chess pieces on the board, the one that corresponds to their team. The function will pass in the original x and y
			position of the chess piece with respect to the Chess Board's indexes and will pass in the position the user wants to move
			the chess piece too.  The function must also take in the team the current user is on, to determine kill moves.
		Postcondition: Returns true if the Horse was able to move to the position which the user wanted to move to, and false if the Horse
			could not move to the user's desired position.
		Returns: bool value
*/
bool Game::moveHorse(int &x1, int &x2, int &y1, int &y2, Team team)
{
	int tempX = x1;
	int tempY = y1;

	bool value = false;
	bool blockedPath = false;

	int deletedIndex = 0;

	if ((x1 + 1 == x2 && y1 + 2 == y2) || (x1 - 1 == x2 && y1 + 2 == y2) || (x1 - 1 == x2 && y1 - 2 == y2) || (x1 + 1 == x2 && y1 - 2 == y2) || (x1 + 2 == x2 && y1 - 1 == y2) || (x1 + 2 == x2 && y1 + 1 == y2) || (x1 - 2 == x2 && y1 - 1 == y2) || (x1 - 2 == x2 && y1 + 1 == y2))
	{
		if (board[y2][x2].getIsOccupied())
		{
			if (board[y2][x2].getChessPiece()->getTeam() != team)
			{
				deletedIndex = board[y2][x2].getChessPiece()->getIndex();
				board[y2][x2].killChessPiece();

				if (team == WHITE)
				{
					shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
					numBlackPieces--;
				}
				else
				{
					shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
					numWhitePieces--;
				}

				board[y2][x2].getChessPiece() = new Horses(team);

				board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

				board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

				board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

				board[y1][x1].getChessPiece() = nullptr;

				value = true;
				board[y2][x2].setIsOccupied(value);

				value = false;
				board[y1][x1].setIsOccupied(value);

				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

			board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

			board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

			board[y1][x1].getChessPiece() = nullptr;

			value = true;
			board[y2][x2].setIsOccupied(value);

			value = false;
			board[y1][x1].setIsOccupied(value);

			return true;
		}
	}
	else
		return false;
}


/*
		Function: bool moveBlackPawn(int &x1, int &x2, int &y1, int &y2, Team team)
		Description: This function moves the Pawn from its orignal x and y coordinates to its new x and y coordinates determined by
			mouse clicks.  This function contains a series of checks that are exclusive to a Pawn, which check if the position it wants to
			go to is occupied, if the user is trying to kill an opponent's chess piece, if there are any pieces between the Pawn and the
			position it wants to move to, and if the user is not clicking a position the Pawn piece simply cannot reach.
		Parameters: int &x1, int &x2, int &y1, int &y2, Team team
		Precondition: This function will only run if the user clicked a valid chess piece to move, that is, if the user clicked one of their
			remaining chess pieces on the board, the one that corresponds to their team. The function will pass in the original x and y
			position of the chess piece with respect to the Chess Board's indexes and will pass in the position the user wants to move
			the chess piece too.  The function must also take in the team the current user is on, to determine kill moves.  Current Pawn
			must be black.
		Postcondition: Returns true if the Pawn was able to move to the position which the user wanted to move to, and false if the Pawn
			could not move to the user's desired position
		Returns: bool value
	*/
bool Game::moveBlackPawn(int &x1, int &x2, int &y1, int &y2, Team team)
{
	bool value = false;

	int deletedIndex = 0;

	if ((y1 < y2 && y2 < y1 + 2) || (board[y1][x1].getIsSpecialMoveValid() && (y1 < y2 && y2 <= y1 + 2)))
	{
		if (x1 == x2)
		{
			if (board[y2][x2].getIsOccupied())
			{
				return false;
			}
			else
			{

				if (board[y1][x1].getIsSpecialMoveValid())
					board[y1][x1].setIsSpecialMoveValid(value = false);

				board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

				board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

				board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

				board[y1][x1].getChessPiece() = nullptr;

				value = true;
				board[y2][x2].setIsOccupied(value);

				value = false;
				board[y1][x1].setIsOccupied(value);

				return true;
			}
		}
		else if ((x1 + 1 == x2 || x1 - 1 == x2) && y2 < y1 + 2)
		{
			if (board[y2][x2].getIsOccupied())
			{
				if (board[y2][x2].getChessPiece()->getTeam() != team)
				{
					deletedIndex = board[y2][x2].getChessPiece()->getIndex();
					board[y2][x2].killChessPiece();

					shiftArrayPositions(whiteTeam, deletedIndex, numWhitePieces);
					numWhitePieces--;

					board[y2][x2].getChessPiece() = new Pawns(team);

					board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

					board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

					board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

					board[y1][x1].getChessPiece() = nullptr;

					value = true;
					board[y2][x2].setIsOccupied(value);

					value = false;
					board[y1][x1].setIsOccupied(value);

					return true;
				}
				else
					return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
		return false;
}

/*
		Function: bool moveWhitePawn(int &x1, int &x2, int &y1, int &y2, Team team)
		Description: This function moves the Pawn from its orignal x and y coordinates to its new x and y coordinates determined by
			mouse clicks.  This function contains a series of checks that are exclusive to a Pawn, which check if the position it wants to
			go to is occupied, if the user is trying to kill an opponent's chess piece, if there are any pieces between the Pawn and the
			position it wants to move to, and if the user is not clicking a position the Pawn piece simply cannot reach.
		Parameters: int &x1, int &x2, int &y1, int &y2, Team team
		Precondition: This function will only run if the user clicked a valid chess piece to move, that is, if the user clicked one of their
			remaining chess pieces on the board, the one that corresponds to their team. The function will pass in the original x and y
			position of the chess piece with respect to the Chess Board's indexes and will pass in the position the user wants to move
			the chess piece too.  The function must also take in the team the current user is on, to determine kill moves.  Current Pawn
			must be white.
		Postcondition: Returns true if the Pawn was able to move to the position which the user wanted to move to, and false if the Pawn
			could not move to the user's desired position
		Returns: bool value
	*/
bool Game::moveWhitePawn(int &x1, int &x2, int &y1, int &y2, Team team)
{
	bool value = false;

	int deletedIndex = 0;

	if ((y1 > y2 && y2 > y1 - 2) || (board[y1][x1].getIsSpecialMoveValid() && (y1 > y2 && y2 >= y1 - 2)))
	{
		if (x1 == x2)
		{
			if (board[y2][x2].getIsOccupied())
			{
				return false;
			}
			else
			{
				if (board[y1][x1].getIsSpecialMoveValid())
					board[y1][x1].setIsSpecialMoveValid(value = false);
				board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

				board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

				board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

				board[y1][x1].getChessPiece() = nullptr;

				value = true;
				board[y2][x2].setIsOccupied(value);

				value = false;
				board[y1][x1].setIsOccupied(value);

				return true;
			}
		}
		else if ((x1 + 1 == x2 || x1 - 1 == x2) && y2 > y1 - 2)
		{
			if (board[y2][x2].getIsOccupied())
			{
				if (board[y2][x2].getChessPiece()->getTeam() != team)
				{
					deletedIndex = board[y2][x2].getChessPiece()->getIndex();
					board[y2][x2].killChessPiece();

					shiftArrayPositions(blackTeam, deletedIndex, numBlackPieces);
					numBlackPieces--;

					board[y2][x2].getChessPiece() = new Pawns(team);

					board[y1][x1].getChessPiece()->move(sf::Vector2i(x2, y2));

					board[y2][x2].setChessPiece(board[y1][x1].getChessPiece());

					board[y2][x2].getChessPiece()->setPosition(board[y2][x2].getPosition());

					board[y1][x1].getChessPiece() = nullptr;

					value = true;
					board[y2][x2].setIsOccupied(value);

					value = false;
					board[y1][x1].setIsOccupied(value);

					return true;
				}
				else
					return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
		return false;
}

bool Game::check(ChessPieces *&piece)
{
	if (piece->getType() == 'K')
	{
		if (piece->getX() - 1 >= 0 && piece->getY() - 1 >= 0 && board[piece->getY() - 1][piece->getX() - 1].getIsOccupied() && (board[piece->getY() - 1][piece->getX() - 1].getChessPiece()->getType() == 'K') && board[piece->getY() - 1][piece->getX() - 1].getChessPiece()->getTeam() != piece->getTeam())
		{
			cout << "Check" << endl;
			return true;
		}
		else if (piece->getY() - 1 >= 0 && piece->getX() + 1 < 8 && board[piece->getY() - 1][piece->getX() + 1].getIsOccupied() && board[piece->getY() - 1][piece->getX() + 1].getChessPiece()->getType() == 'K' && board[piece->getY() - 1][piece->getX() + 1].getChessPiece()->getTeam() != piece->getTeam())
		{
			cout << "Check" << endl;
			return true;
		}
		else if (piece->getY() + 1 < 8 && piece->getX() - 1 >= 0 && board[piece->getY() + 1][piece->getX() - 1].getIsOccupied() && (board[piece->getY() + 1][piece->getX() - 1].getChessPiece()->getType() == 'K') && board[piece->getY() + 1][piece->getX() - 1].getChessPiece()->getTeam() != piece->getTeam())
		{
			cout << "Check" << endl;
			return true;
		}
		else if (piece->getY() + 1 < 8 && piece->getX() + 1 < 8 && board[piece->getY() + 1][piece->getX() + 1].getIsOccupied() && board[piece->getY() + 1][piece->getX() + 1].getChessPiece()->getType() == 'K' && board[piece->getY() + 1][piece->getX() + 1].getChessPiece()->getTeam() != piece->getTeam())
		{
			cout << "Check" << endl;
			return true;
		}
		else if (piece->getY() + 1 < 8 && piece->getX() && board[piece->getY() + 1][piece->getX()].getIsOccupied() && (board[piece->getY() + 1][piece->getX()].getChessPiece()->getType() == 'K') && board[piece->getY() + 1][piece->getX()].getChessPiece()->getTeam() != piece->getTeam())
		{
			cout << "Check" << endl;
			return true;
		}
		else if (piece->getY() - 1 >= 0 && piece->getX() && board[piece->getY() - 1][piece->getX()].getIsOccupied() && (board[piece->getY() - 1][piece->getX()].getChessPiece()->getType() == 'K') && board[piece->getY() - 1][piece->getX()].getChessPiece()->getTeam() != piece->getTeam())
		{
			cout << "Check" << endl;
			return true;
		}
		else if (piece->getY() && piece->getX() - 1 >= 0 && board[piece->getY()][piece->getX() - 1].getIsOccupied() && (board[piece->getY()][piece->getX() - 1].getChessPiece()->getType() == 'K') && board[piece->getY()][piece->getX() - 1].getChessPiece()->getTeam() != piece->getTeam())
		{
			cout << "Check" << endl;
			return true;
		}
		else if (piece->getY() && piece->getX() + 1 < 8 && board[piece->getY()][piece->getX() + 1].getIsOccupied() && (board[piece->getY()][piece->getX() + 1].getChessPiece()->getType() == 'K') && board[piece->getY()][piece->getX() + 1].getChessPiece()->getTeam() != piece->getTeam())
		{
			cout << "Check" << endl;
			return true;
		}
		else
		{
			return false;
		}
	}

	if (piece->getType() == 'Q')
	{
		for (int i = 1; piece->getX() + i < 8 && piece->getY() + i < 8; i++)
		{
			if (board[piece->getY() + i][piece->getX() + i].getIsOccupied())
			{
				if (board[piece->getY() + i][piece->getX() + i].getChessPiece()->getType() == 'K' && board[piece->getY() + i][piece->getX() + i].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}

			}
		}
		for (int i = 1; piece->getY() - i >= 0 && piece->getX() + i < 8; i++)
		{
			if (board[piece->getY() - i][piece->getX() + i].getIsOccupied())
			{
				if (board[piece->getY() - i][piece->getX() + i].getChessPiece()->getType() == 'K' && board[piece->getY() - i][piece->getX() + i].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}
			}
		}
		for (int i = 1; piece->getY() - i >= 0 && piece->getX() - i >= 0; i++)
		{
			if (board[piece->getY() - i][piece->getX() - i].getIsOccupied())
			{
				if (board[piece->getY() - i][piece->getX() - i].getChessPiece()->getType() == 'K' && board[piece->getY() - i][piece->getX() - i].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}
			}
		}
		for (int i = 1; piece->getY() + i < 8 && piece->getX() - i >= 0; i++)
		{
			if (board[piece->getY() + i][piece->getX() - i].getIsOccupied())
			{
				if (board[piece->getY() + i][piece->getX() - i].getChessPiece()->getType() == 'K' && board[piece->getY() + i][piece->getX() - i].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}
			}
		}
		for (int i = 1; piece->getY() + i < 8; i++)
		{
			if (board[piece->getY() + i][piece->getX()].getIsOccupied())
			{
				if (board[piece->getY() + i][piece->getX()].getChessPiece()->getType() == 'K' && board[piece->getY() + i][piece->getX()].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}
			}
		}
		for (int i = 1; piece->getY() - i >= 0; i++)
		{
			if (board[piece->getY() - i][piece->getX()].getIsOccupied())
			{
				if (board[piece->getY() - i][piece->getX()].getChessPiece()->getType() == 'K' && board[piece->getY() - i][piece->getX()].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}
			}
		}
		for (int i = 1; piece->getX() + i < 8; i++)
		{
			if (board[piece->getY()][piece->getX() + i].getIsOccupied())
			{
				if (board[piece->getY()][piece->getX() + i].getChessPiece()->getType() == 'K' && board[piece->getY()][piece->getX() + i].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}
			}
		}
		for (int i = 1; piece->getX() - i >= 0; i++)
		{
			if (board[piece->getY()][piece->getX() - i].getIsOccupied())
			{
				if (board[piece->getY()][piece->getX() - i].getChessPiece()->getType() == 'K' && board[piece->getY()][piece->getX() - i].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}
			}
		}
	}

	if (piece->getType() == 'R')
	{
		for (int i = 1; piece->getX() + i < 8; i++)
		{
			if (board[piece->getY()][piece->getX() + i].getIsOccupied())
			{
				if (board[piece->getY()][piece->getX() + i].getChessPiece()->getType() == 'K' && board[piece->getY()][piece->getX() + i].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}
			}
		}
		for (int i = 1; piece->getX() - i >= 0; i++)
		{
			if (board[piece->getY()][piece->getX() - i].getIsOccupied())
			{
				if (board[piece->getY()][piece->getX() - i].getChessPiece()->getType() == 'K' && board[piece->getY()][piece->getX() - i].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}
			}
		}
		for (int i = 1; piece->getY() - i >= 0; i++)
		{
			if (board[piece->getY() - i][piece->getX()].getIsOccupied())
			{
				if (board[piece->getY() - i][piece->getX()].getChessPiece()->getType() == 'K' && board[piece->getY() - i][piece->getX()].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}
			}
		}
		for (int i = 1; piece->getY() + i < 8; i++)
		{
			if (board[piece->getY() + i][piece->getX()].getIsOccupied())
			{
				if (board[piece->getY() + i][piece->getX()].getChessPiece()->getType() == 'K' && board[piece->getY() + i][piece->getX()].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}
			}
		}
	}
	if (piece->getType() == 'B')
	{
		for (int i = 1; piece->getX() + i < 8 && piece->getY() + i < 8; i++)
		{
			if (board[piece->getY() + i][piece->getX() + i].getIsOccupied())
			{
				if (board[piece->getY() + i][piece->getX() + i].getChessPiece()->getType() == 'K' && board[piece->getY() + i][piece->getX() + i].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}

			}
		}
		for (int i = 1; piece->getY() - i >= 0 && piece->getX() + i < 8; i++)
		{
			if (board[piece->getY() - i][piece->getX() + i].getIsOccupied())
			{
				if (board[piece->getY() - i][piece->getX() + i].getChessPiece()->getType() == 'K' && board[piece->getY() - i][piece->getX() + i].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}
			}
		}
		for (int i = 1; piece->getY() - i >= 0 && piece->getX() - i >= 0; i++)
		{
			if (board[piece->getY() - i][piece->getX() - i].getIsOccupied())
			{
				if (board[piece->getY() - i][piece->getX() - i].getChessPiece()->getType() == 'K' && board[piece->getY() - i][piece->getX() - i].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}
			}
		}
		for (int i = 1; piece->getY() + i < 8 && piece->getX() - i >= 0; i++)
		{
			if (board[piece->getY() + i][piece->getX() - i].getIsOccupied())
			{
				if (board[piece->getY() + i][piece->getX() - i].getChessPiece()->getType() == 'K' && board[piece->getY() + i][piece->getX() - i].getChessPiece()->getTeam() != piece->getTeam())
				{
					cout << "Check" << endl;
					return true;
				}
				else
				{
					i = 8;
				}
			}
		}
	}
	if (piece->getType() == 'H')
	{
		if (piece->getY() + 2 < 8 && piece->getX() + 1 < 8)
		{
			if (board[piece->getY() + 2][piece->getX() + 1].getIsOccupied())
			{
				if ((board[piece->getY() + 2][piece->getX() + 1].getChessPiece()->getType() == 'K' && board[piece->getY() + 2][piece->getX() + 1].getChessPiece()->getTeam() != piece->getTeam()))
				{
					cout << "Check" << endl;
					return true;
				}
			}
		}
		if (piece->getY() + 2 < 8 && piece->getX() - 1 >= 0)
		{
			if (board[piece->getY() + 2][piece->getX() - 1].getIsOccupied())
			{
				if ((board[piece->getY() + 2][piece->getX() - 1].getChessPiece()->getType() == 'K' && board[piece->getY() + 2][piece->getX() - 1].getChessPiece()->getTeam() != piece->getTeam()))
				{
					cout << "Check" << endl;
					return true;
				}
			}
		}
		if (piece->getY() - 2 >= 0 && piece->getX() - 1 >= 0)
		{
			if (board[piece->getY() - 2][piece->getX() - 1].getIsOccupied())
			{
				if ((board[piece->getY() - 2][piece->getX() - 1].getChessPiece()->getType() == 'K' && board[piece->getY() - 2][piece->getX() - 1].getChessPiece()->getTeam() != piece->getTeam()))
				{
					cout << "Check" << endl;
					return true;
				}
			}
		}
		if (piece->getY() - 2 >= 0 && piece->getX() + 1 < 8)
		{
			if (board[piece->getY() - 2][piece->getX() + 1].getIsOccupied())
			{
				if ((board[piece->getY() - 2][piece->getX() + 1].getChessPiece()->getType() == 'K' && board[piece->getY() - 2][piece->getX() + 1].getChessPiece()->getTeam() != piece->getTeam()))
				{
					cout << "Check" << endl;
					return true;
				}
			}
		}
		if (piece->getY() - 1 >= 0 && piece->getX() + 2 < 8)
		{
			if (board[piece->getY() - 1][piece->getX() + 2].getIsOccupied())
			{
				if ((board[piece->getY() - 1][piece->getX() + 2].getChessPiece()->getType() == 'K' && board[piece->getY() - 1][piece->getX() + 2].getChessPiece()->getTeam() != piece->getTeam()))
				{
					cout << "Check" << endl;
					return true;
				}
			}
		}
		if (piece->getY() + 1 < 8 && piece->getX() + 2 < 8)
		{
			if (board[piece->getY() + 1][piece->getX() + 2].getIsOccupied())
			{
				if ((board[piece->getY() + 1][piece->getX() + 2].getChessPiece()->getType() == 'K' && board[piece->getY() + 1][piece->getX() + 2].getChessPiece()->getTeam() != piece->getTeam()))
				{
					cout << "Check" << endl;
					return true;
				}
			}
		}
		if (piece->getY() - 1 >= 0 && piece->getX() - 2 >= 0)
		{
			if (board[piece->getY() - 1][piece->getX() - 2].getIsOccupied())
			{
				if ((board[piece->getY() - 1][piece->getX() - 2].getChessPiece()->getType() == 'K' && board[piece->getY() - 1][piece->getX() - 2].getChessPiece()->getTeam() != piece->getTeam()))
				{
					cout << "Check" << endl;
					return true;
				}
			}
		}
		if (piece->getY() + 1 < 8 && piece->getX() - 2 >= 0)
		{
			if (board[piece->getY() + 1][piece->getX() - 2].getIsOccupied())
			{
				if ((board[piece->getY() + 1][piece->getX() - 2].getChessPiece()->getType() == 'K' && board[piece->getY() + 1][piece->getX() - 2].getChessPiece()->getTeam() != piece->getTeam()))
				{
					cout << "Check" << endl;
					return true;
				}
			}
		}
	}
	if (piece->getType() == 'P' && piece->getTeam() == WHITE)
	{
		if (piece->getY() - 1 >= 0 && piece->getX() - 1 >= 0 && board[piece->getY() - 1][piece->getX() - 1].getIsOccupied() && (board[piece->getY() - 1][piece->getX() - 1].getChessPiece()->getType() == 'K') && board[piece->getY() - 1][piece->getX() - 1].getChessPiece()->getTeam() != piece->getTeam())
		{
			cout << "Check" << endl;
			return true;
		}
		else if (piece->getY() - 1 >= 0 && piece->getX() + 1 < 8 && board[piece->getY() - 1][piece->getX() + 1].getIsOccupied() && board[piece->getY() - 1][piece->getX() + 1].getChessPiece()->getType() == 'K' && board[piece->getY() - 1][piece->getX() + 1].getChessPiece()->getTeam() != piece->getTeam())
		{
			cout << "Check" << endl;
			return true;
		}
		else
		{
			return false;
		}

	}
	if (piece->getType() == 'P' && piece->getTeam() == BLACK)
	{
		if (piece->getY() + 1 < 8 && piece->getX() - 1 >= 0 && board[piece->getY() + 1][piece->getX() - 1].getIsOccupied() && (board[piece->getY() + 1][piece->getX() - 1].getChessPiece()->getType() == 'K') && board[piece->getY() + 1][piece->getX() - 1].getChessPiece()->getTeam() != piece->getTeam())
		{
			cout << "Check" << endl;
			return true;
		}
		else if (piece->getY() + 1 < 8 && piece->getX() + 1 < 8 && board[piece->getY() + 1][piece->getX() + 1].getIsOccupied() && board[piece->getY() + 1][piece->getX() + 1].getChessPiece()->getType() == 'K' && board[piece->getY() + 1][piece->getX() + 1].getChessPiece()->getTeam() != piece->getTeam())
		{
			cout << "Check" << endl;
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}