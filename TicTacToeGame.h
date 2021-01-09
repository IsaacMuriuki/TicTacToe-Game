#ifndef TICTACTOE_TICTACTOEGAME_H
#define TICTACTOE_TICTACTOEGAME_H

#include <string>
#include <iostream>
#include <vector>
#include <limits>

class TicTacToeGame {
    struct move{
        int score;
        int index;
    };

public:
    const int PLAYER1_INDEX = 1;
    const int PLAYER2_INDEX = 2;
    const int AI_INDEX = 3;

    TicTacToeGame();
    void play();
    bool hasWon() const;
    bool haveTied() const;
    char getMarker(int, int) const;
    void setMarker(int, int);
    void resetMarker(int);
    int getCurrentPlayer() const;
    std::vector<int> possibleMoves();

private:
    char board[3][3];
    std::string player1_name;
    std::string player2_name;
    int currentPlayer;
    bool isMultiplayer;
    int moveCount = 0;

    void init();
    void printBoard();
    void setPlayer1Name(std::string);
    void setPlayer2Name(std::string);
    std::string getPlayer1Name() const;
    std::string getPlayer2Name() const;
    void switchCurrentPlayer();
    std::string winMessage();
    int getRow(int) const;
    int getColumn(int) const;
    bool checkMarker(int, int);

    void makeAIMove(TicTacToeGame *);
    move miniMax(TicTacToeGame, int, int, int, int);
};


#endif //TICTACTOE_TICTACTOEGAME_H
