//
// Created by Isaac Muriuki on 2021-01-06.
//

#include "TicTacToeGame.h"

TicTacToeGame::TicTacToeGame() {
    init();
}

// Create the board with indexes
void TicTacToeGame::init() {
    currentPlayer = 2;
    int k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++, k++) {
            board[i][j] = '0' + k;
            // printf("board[%d,%d] : [%c]\n", i, j, board[i][j]);
        }
    }
}

// Prints the board int he format of a TicTacToe game
void TicTacToeGame::printBoard() {
    std::cout << "\n";
    for (int i = 0; i < 3; i++) {
        if (i != 0) std::cout << "\n   --------------------\n";
        for (int j = 0; j < 3; j++) {
            std::cout << "\t" << board[i][j];
            if (j != 2) std::cout << "\t|";
        }
    }
    //cout << "\n-------------------------\n";
}

/*
 * need to do input validation for:
 *     - playing position (checking for string)
 */
// Handles the playing
void TicTacToeGame::play() {
    std::string welcome = "\t\t*********************************************\n\t\t*\t\tWelcome to the TicTacToe game !\t\t*\n\t\t*********************************************\n\n\n";
    int position = -1;
    char playAgain;
    int moveCount = 0;

    std::cout << welcome;

    // Initializing players
    std::cout << "Player 1, please type in your name: ";
    std::cin >> player1_name;

    setPlayer1Name(player1_name);
    std::cout << getPlayer1Name() << " will be X." << std::endl;

    std::cout << "\nPlayer 2, please type in your name: ";
    std::cin >> player2_name;
    setPlayer2Name(player2_name);
    std::cout << getPlayer2Name() << " will be O.\n" << std::endl;


    std::cout << "Starting game: \nINSTRUCTIONS: Select the number of the position where you want to play" << std::endl;

    // Play loop
    while (!hasWon()) {
        printBoard();

        // Alternate between players after evey move
        switchCurrentPlayer();

        while (true) {
            std::cin >> position;

            // Checks if input is an integer, asks for another input is not
            while (std::cin.fail()) {
                std::cout << "Invalid entry ! Enter a number between 0 and 8 inclusive: ";
                std::cin.clear();
                std::cin.ignore(256,'\n');
                std::cin >> position;
            }

            // Validation if the position is in range, request for another input if not
            while (position < 0 || position > 9) {
                std::cout << position << " is an invalid position ! Enter a position between 0 and 8 inclusive: ";
                std::cin >> position;
            }

            // Check if there's not X or O in that position already, asks for another position to if so. If not writes X/O
            if (checkMarker(getRow(position), getColumn(position))) {
                setMarker(position, position);
                break;
            } else {
                std::cout
                        << "There's already an X/O in that position. Try place it in an empty spot.\nEnter a new position: ";
            }
        }
        moveCount++;

        // Checks for a winner or a tie after every move
        if (hasWon() || haveTied(moveCount)) {
            std::cout << winMessage();

            std::cout << "\n\nDo you want to play again ? Enter y OR n: ";
            std::cin >> playAgain;
            playAgain = tolower(playAgain); // converts to lowercase

            // If there's a winner ask if user wants to play another game, stops application if not
            while (true) {
                if (playAgain != 'y' && playAgain != 'n') {
                    std::cout << playAgain << std::endl;
                    std::cout << "Invalid expression ! Enter either y OR n: ";
                    std::cin >> playAgain;
                    playAgain = tolower(playAgain); // converts to lowercase
                } else if (playAgain == 'y' || playAgain == 'n') break;
            }

            if (playAgain == 'y') {
                std::cout << "Generating a new board " << std::endl;
                init();
                moveCount = 0;
            } else if (playAgain == 'n') {
                std::cout << "\nThank you for playing the TicTacToe game !\nExiting the game.";
                break;
            }
        }
    }
}

std::string TicTacToeGame::winMessage() {
    if (getCurrentPlayer() == 1) { return "\n\n" + getPlayer1Name() + " has won !"; }
    else if (getCurrentPlayer() == 2) return "\n\n" + getPlayer2Name() + "has won !";
}

// Checks for winning conditions
bool TicTacToeGame::hasWon() const {
    for (int i = 0; i < 3; ++i) {
        // Checking horizontals
        if (getMarker(0, i) == getMarker(1, i) && getMarker(1, i) == getMarker(2, i)) {
            //cout << "horizontal alignment";
            return true;
        }

        // Chekcing verticals
        if (getMarker(i, 0) == getMarker(i, 1) && getMarker(i, 1) == getMarker(i, 2)) {
            //cout << "vertical alignment";
            return true;
        }
    }

    // Checking diagonals
    if (getMarker(0, 0) == getMarker(1, 1) && getMarker(1, 1) == getMarker(2, 2)) return true;
    if (getMarker(0, 2) == getMarker(1, 1) && getMarker(1, 1) == getMarker(2, 0)) return true;

    // If no alignment
    return false;
}

void TicTacToeGame::setPlayer1Name(std::string name) {
    player1_name = name;
}

void TicTacToeGame::setPlayer2Name(std::string name) {
    player2_name = name;
}

std::string TicTacToeGame::getPlayer1Name() const {
    return player1_name;
}

std::string TicTacToeGame::getPlayer2Name() const {
    return player2_name;
}

int TicTacToeGame::getCurrentPlayer() const {
    return currentPlayer;
}

int TicTacToeGame::getRow(int row) {
    return row / 3;
}

int TicTacToeGame::getColumn(int column) const {
    return column % 3;
}

bool TicTacToeGame::checkMarker(int row, int column) {
    if (getMarker(row, column) == 'X' || getMarker(row, column) == 'O') return false;
    return true;
}

char TicTacToeGame::getMarker(int row, int column) const {
    return board[row][column];
}

void TicTacToeGame::setMarker(int row, int column) {
    board[getRow(row)][getColumn(column)] = currentPlayer == 1 ? PLAYER1 : PLAYER2;
}

void TicTacToeGame::switchCurrentPlayer() {
    if (currentPlayer == 1) {
        currentPlayer = 2;
        std::cout << "\n\nIt's " << getPlayer2Name() << "'s turn, select the position you want to move to:";
    } else if (currentPlayer == 2) {
        currentPlayer = 1;
        std::cout << "\n\nIt's " << getPlayer1Name() << "'s turn, select the position you want to move to:";
    }
}

bool TicTacToeGame::haveTied(int moves) const {
    if (moves == 9) return true;
    return false;
}


