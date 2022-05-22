#include <iostream>
#include <string>

#include "Board.hpp"

// void run(Board board) {
// 	while (true) {
// 		board.show();
//
// 		std::string command;
// 		std::getline(std::cin, command);
//
// 		if (command == "undo") {
// 			board.undo();
// 		}
// 	}
// }

int main() {
	Board myBoard = Board();
	myBoard.loadFEN("3Q2b1/8/R2b2r1/4q2K/4P3/1BkP4/1n6/3N4/ w - - 0 1");
	myBoard.show();
	std::cout << myBoard.convertIntToStringMove({6, 4, 4, 4});
	return 0;
}
