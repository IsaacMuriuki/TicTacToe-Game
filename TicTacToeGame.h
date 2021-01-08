#ifndef TICTACTOE_TICTACTOEGAME_H
#define TICTACTOE_TICTACTOEGAME_H

#include <string>
#include <iostream>

class TicTacToeGame {
public:
    TicTacToeGame();
    void play();
private:
    void init();
    void printBoard();
    void setPlayer1Name(std::string);
    void setPlayer2Name(std::string);
    std::string getPlayer1Name() const;
    std::string getPlayer2Name() const;
    int getCurrentPlayer() const;
    void switchCurrentPlayer();
    bool hasWon() const;
    std::string winMessage();
    int getRow(int) ;
    int getColumn(int) const;
    bool checkMarker(int, int);
    char getMarker(int, int) const;
    void setMarker(int, int);
    bool haveTied(int) const;
    const char PLAYER1 = 'X';
    const char PLAYER2 = 'O';
    char board[3][3];
    std::string player1_name;
    std::string player2_name;
    int currentPlayer;
};


#endif //TICTACTOE_TICTACTOEGAME_H
