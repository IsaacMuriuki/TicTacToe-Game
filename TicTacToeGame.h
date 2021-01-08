#ifndef TICTACTOE_TICTACTOEGAME_H
#define TICTACTOE_TICTACTOEGAME_H

#include <string>
#include <iostream>

class TicTacToeGame {
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
    int getCurrentPlayer() const;

private:
    char board[3][3];
    std::string player1_name;
    std::string player2_name;
    int currentPlayer;
    bool isMultiplayer;
    int moveCount = 0;
    const char PLAYER1 = 'X';
    const char PLAYER2 = 'O';

    void init();
    void printBoard();
    void setPlayer1Name(std::string);
    void setPlayer2Name(std::string);
    std::string getPlayer1Name() const;
    std::string getPlayer2Name() const;
    void switchCurrentPlayer();
    std::string winMessage();
    int getRow(int) ;
    int getColumn(int) const;
    bool checkMarker(int, int);
};


#endif //TICTACTOE_TICTACTOEGAME_H
