#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>

class Board {
public:
	//Initialises the board to a given state
	Board(std::string initialBoardState);
	//Initialises the board to the default state
	Board();

	void show(char perspective = 'w');
	void loadFEN(std::string fenString);
private:	
	//Attributes represent fields of FEN notation.
	char board[8][8];
	char turn;
	std::string castling;
	std::string enPassantTargetSquare;
	int halfmoveClock;
	int fullmoveClock;

	//Represents FEN string of initial state. See Wikipedia.
	std::string startPositionFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
};

#endif
