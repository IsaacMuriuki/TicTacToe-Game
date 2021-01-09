#include "TicTacToeGame.h"

// Player is MINIMIZER, AI is MAXIMIZER
TicTacToeGame::move TicTacToeGame::miniMax(TicTacToeGame board, int player) {
    move current, best;
    int otherPlayer = (player == 1) ? 3 : 1;

    if (board.hasWon()){
        if(player == PLAYER1_INDEX){
            best.score = (board.possibleMoves().size() + 1);
            return best;
        } else if(player == AI_INDEX){
            best.score = -(board.possibleMoves().size() + 1);
            return best;
        }
    } else if(board.haveTied()){
        best.score = 0;
        return best;
    }

    if(player == AI_INDEX){
        best.score = -9999999;
    } else best.score = 9999999;

    std::vector<int> possibleMoves = board.possibleMoves();

    for (int i = 0; i < possibleMoves.size(); i++) {
        board.setMarker(possibleMoves[i], player);
        current = miniMax(board, otherPlayer);
        current.index = possibleMoves[i];

        if(player == AI_INDEX){
            if(current.score > best.score) {
                best = current;
            }
        } else
            if(current.score < best.score){
                best = current;
            }

        board.resetMarker(possibleMoves[i]);
    }

    //std::cout << "best index: " << best.index << " best score: " << best.score << std::endl;
    return best;
}

void TicTacToeGame::makeAIMove(TicTacToeGame *board) {
    int move = miniMax(*board, getCurrentPlayer()).index;
    setMarker(move, getCurrentPlayer());
    std::cout << "\nThe AI has moved to " << move << std::endl;
}

std::vector<int> TicTacToeGame::possibleMoves() {
    std::vector<int> possibleMoves;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if(board[i][j] != 'X' && board[i][j] != 'O'){
                possibleMoves.push_back(3 * i +j);
            }
        }
    }
    return possibleMoves;
}

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
}

// Handles the playing
void TicTacToeGame::play() {
    std::string welcome = "\t\t*********************************************\n\t\t*\t\tWelcome to the TicTacToe game !\t\t*\n\t\t*********************************************\n\n\n";
    int position = -1;
    char multiplayer;
    char playAgain;

    std::cout << welcome;

    while (true){
        std::cout << "Do you want to play multiplayer ? (y/n): ";

        std::cin >> multiplayer;
        multiplayer = tolower(multiplayer);

        // Checks if input is valid, asks for another input if not
        while (std::cin.fail() || (multiplayer != 'y' && multiplayer != 'n')) {
            std::cout << "Invalid entry ! Enter either y OR n: ";
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> multiplayer;
            multiplayer = tolower(multiplayer);
        }

        if (multiplayer == 'y') isMultiplayer = true;
        else if (multiplayer == 'n') isMultiplayer = false;
        break;
    }

    // Initializing players
        std::cout << "Player 1, please type in your name: ";
        std::cin >> player1_name;

        // Checks if input is valid, asks for another input if not
        while (std::cin.fail()) {
            std::cout << "Invalid entry ! Re-enter your name: ";
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> player1_name;
        }

        setPlayer1Name(player1_name);
        std::cout << getPlayer1Name() << " will be X." << std::endl;

        // Only initializes player 2 if it's a multiplayer game
        if (isMultiplayer){
            std::cout << "\nPlayer 2, please type in your name: ";
            std::cin >> player2_name;

            // Checks if input is valid, asks for another input if not
            while (std::cin.fail()) {
                std::cout << "Invalid entry ! Re-enter your name: ";
                std::cin.clear();
                std::cin.ignore(256, '\n');
                std::cin >> player2_name;
            }

            setPlayer2Name(player2_name);
            std::cout << getPlayer2Name() << " will be O.\n" << std::endl;
        }


    std::cout << "Starting game: \nINSTRUCTIONS: Select the number of the position where you want to play" << std::endl;

    // Play loop
    while (!hasWon()) {
        printBoard();

        // Alternate between players after evey move
        switchCurrentPlayer();
        std::cout << "\ncurrent player is " << currentPlayer << std::endl;

        // Player's move
        if (currentPlayer == PLAYER1_INDEX || currentPlayer == PLAYER2_INDEX){
            while (true) {
                std::cin >> position;

                // Checks if input is an integer, asks for another input if not
                while (std::cin.fail() || position < 0 || position > 8) {
                    std::cout << "Invalid entry ! Enter a number between 0 and 8 inclusive: ";
                    std::cin.clear();
                    std::cin.ignore(256, '\n');
                    std::cin >> position;
                }

                // Check if there's an X or O in that position already, if yes - ask for another position to if so. If no - writes X/O
                if (checkMarker(getRow(position), getColumn(position))) {
                    setMarker(position, getCurrentPlayer());
                    break;
                } else {
                    std::cout
                            << "There's already an X/O in that position. Try place it in an empty spot.\nEnter a new position: ";
                }
            }
        }
        // AI's move
        else if (currentPlayer == AI_INDEX){
            makeAIMove(this);
        }

        moveCount++;

        // Checks for a winner or a tie after every move
        if (hasWon() || haveTied()) {
            if (hasWon()) std::cout << winMessage() << std::endl;
            else if(haveTied()) std::cout << "The game is a tie !" << std::endl;

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
    else return "\n\nThe AI has won !";
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

int TicTacToeGame::getRow(int row) const{
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

void TicTacToeGame::setMarker(int position, int player) {
    board[getRow(position)][getColumn(position)] = player == 1 ? 'X' : 'O';
}

/* Switches the play either from:
 *  - PLAYER1 to PLAYER2
 *  - PLAYER 2 to PLAYER1
 *  - AI to PLAYER1
 *  - PLAYER1 to AI
 */
void TicTacToeGame::switchCurrentPlayer() {
    if (currentPlayer == PLAYER1_INDEX && !isMultiplayer){
        currentPlayer = AI_INDEX;
        std::cout << "\n\nIt's the AI's turn now" << std::endl;
    } else if (currentPlayer == PLAYER1_INDEX) {
        currentPlayer = PLAYER2_INDEX;
        std::cout << "\n\nIt's " << getPlayer2Name() << "'s turn, select the position you want to move to:";
    } else if (currentPlayer == PLAYER2_INDEX || currentPlayer == AI_INDEX) {
        currentPlayer = PLAYER1_INDEX;
        std::cout << "\n\nIt's " << getPlayer1Name() << "'s turn, select the position you want to move to:";
    }
}

bool TicTacToeGame::haveTied() const {
    if (moveCount == 9) return true;
    return false;
}

void TicTacToeGame::resetMarker(int position) {
    board[getRow(position)][getColumn(position)] = (char) position;
}


