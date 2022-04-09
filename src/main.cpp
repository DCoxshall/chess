#include <iostream>

#include "Board.h"

int main() {
    Board myBoard = Board();
	myBoard.loadFEN("8/1pR1Nn1p/4q3/4N1r1/6Q1/1p6/1P1Pp1K1/k2b4 w - - 0 1");
    myBoard.show();
    std::cout << myBoard.generateFEN();
    return 0;
}
