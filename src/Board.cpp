#include "Board.h"

#include <iostream>
#include <vector>
#include <ctype.h>

Board::Board(std::string initialBoardState) {
    loadFEN(initialBoardState);
}

Board::Board() {
    loadFEN(startPositionFEN);
}

void Board::loadFEN(std::string fenString) {
    // Split string into fields and place into fenFields;
    std::vector<std::string> fenFields;

    std::string delimiter = " ";
    for (int i = 0; i < 6; i++) {
        fenFields.push_back(fenString.substr(0, fenString.find(delimiter)));
        fenString.erase(0, fenString.find(delimiter) + 1);
    }

    // Handle easy attributes first.
    turn = fenFields[1][0];
    castling = fenFields[2];
    enPassantTargetSquare = fenFields[3];
    halfmoveClock = std::stoi(fenFields[4]);
    fullmoveClock = std::stoi(fenFields[5]);

    // Load the board state into the board array.
    std::string boardState = fenFields[0];
    int x = 0;
    int y = 0;
    while (boardState != "") {
        if (isalpha(boardState[0])) {  // The character is a piece
            board[y][x] = boardState[0];
            x++;
        } else if (isdigit(boardState[0])) {  // The character is a number
            for (int i = 0; i < boardState[0] - '0'; i++) {
                board[y][x] = '_';  // '_' represents an empty square
                x++;
            }
        }
        boardState.erase(0, 1);
        if (x == 8) {
            x = 0;
            y++;
        }
    }
}

// The idea is to present every field of the current FEN as compactly as
// possible.
void Board::show(char perspective) {
    std::cout << "--Start Board--" << std::endl;
    std::cout << ">>"
              << " " << turn << " " << castling << " " << enPassantTargetSquare
              << " " << halfmoveClock << " " << fullmoveClock << std::endl;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "---End Board---\n";
}
