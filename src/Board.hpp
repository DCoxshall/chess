#include <stack>
#include <string>
#include <vector>

class Board {
   public:
    Board(std::string initialBoardState =
              "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    void undo();
    void show(char perspective = 'w');
    char getAt(int x, int y);
    void loadFEN(std::string fenString);
    std::string convertIntToStringMove(std::vector<int> move);

   private:
    std::vector<int> convertStringToIntMove(std::string move);
    std::string generateFEN();

    std::string castling;
    char turn;
    std::string enPassantTargetSquare;
    int halfmoveClock;
    int fullmoveClock;

    std::stack<std::string> FENstack;

    std::string startPositionFEN =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    char board[8][8];
};