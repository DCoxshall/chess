#include <iostream>

#include "Board.h"

int main() {
    Board myBoard = Board();
    myBoard.show();
    myBoard.FENstack.push_back("1n6/2p1P1K1/1p2r3/b7/P1p3P1/7B/2p1kNb1/R7 w - - 0 1");
    myBoard.undo();
    myBoard.show();
    return 0;
}
