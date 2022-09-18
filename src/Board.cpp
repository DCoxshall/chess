#include "Board.hpp"

#include <ctype.h>

#include <iostream>
#include <vector>

Board::Board(std::string initialBoardState) { loadFEN(initialBoardState); }

// void Board::makeMove(std::string move) {
// 	std::vector<int> integerMove = convertStringToIntMove(move);
// }

// {6, 4, 4, 4} -> e2e4
std::string Board::convertIntToStringMove(std::vector<int> move) {
    std::string alphabet = "abcdefgh";
    std::string ans = "";
    char char1 = alphabet[move[1]];
    char char2 = '8' - move[0];
    char char3 = alphabet[move[3]];
    char char4 = '8' - move[2];
    return ans + char1 + char2 + char3 + char4;
}

// e2e4 -> {6, 4, 4, 4}
std::vector<int> Board::convertStringToIntMove(std::string move) {
    std::string alphabet = "abcdefgh";
    int field1 = '8' - move[1];
    int field2 = alphabet.find(move[0]);
    int field3 = '8' - move[3];
    int field4 = alphabet.find(move[2]);
    return {field1, field2, field3, field4};
}

std::string Board::generateFEN() {
    std::string newFEN;

    // Handle board state first
    for (int i = 0; i < 8; i++) {
        int currentNum = 0;
        for (int j = 0; j < 8; j++) {
            if (isalpha(board[i][j])) {
                if (currentNum > 0) {
                    newFEN.append(std::to_string(currentNum));
                    currentNum = 0;
                }
                newFEN += board[i][j];
            } else {
                currentNum += 1;
            }
        }
        if (currentNum > 0) {
            newFEN.append(std::to_string(currentNum));
        }
        newFEN += "/";
    }
    newFEN.pop_back();

    // Handle easy attributes
    newFEN += " ";
    newFEN += turn;
    newFEN += " ";

    if (castling != "") {
        newFEN += castling;
        newFEN += " ";
    }

    newFEN += enPassantTargetSquare;
    newFEN += " ";

    newFEN += std::to_string(halfmoveClock);
    newFEN += " ";

    newFEN += std::to_string(fullmoveClock);

    return newFEN;
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
    int x = 0, y = 0;
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

void Board::undo() {
    if (FENstack.size() > 0) {
        std::string previousFEN = FENstack.top();
        FENstack.pop();
        loadFEN(previousFEN);
    } else {
        std::cout << "Stack is empty, unable to load previous position.";
    }
}

// The idea is to present every field of the current FEN as compactly as
// possible.
void Board::show(char perspective) {
    std::cout << "--Start Board--" << std::endl;
    std::cout << ">>"
              << " " << turn << " " << castling << " " << enPassantTargetSquare
              << " " << halfmoveClock << " " << fullmoveClock << std::endl;

    if (perspective == 'w') {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
    } else {
        for (int i = 7; i > -1; i--) {
            for (int j = 7; j > -1; j--) {
                std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "---End Board---\n";
}

char Board::getAt(int x, int y) { return board[x][y]; }