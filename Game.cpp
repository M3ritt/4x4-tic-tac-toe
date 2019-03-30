/*
*4 x 4 game of tic tac toe where you must get 4 in a row
*Game created by Joshua Meritt
*Can play against another person or against a computer created by Joshua Meritt
*/

#include "pch.h"
#include <iostream>
#include <String>
using std::string;

//varialbes of board and nextBoard which is used for computer player
string board[4][4];
string nextBoard[4][4];
//variables used for extra stuff that is printed out
int playerOneWins, playerTwoWins, draws, turns, numberOfPlayers;

//Error checking user input
int getNumberOfPlayers();
int getUserMove(int);
int getStartingPlayer();

//checks game state whether someone won
int checkGameState();
//runs game
int gameRunner();
//resets board
void resetBoard();
//prints board
void printBoard();
//checks after the game
void afterGame();

//for Computer player, I like the name Henry
int HenryTheComputer();
//checks if computer can win or lose by going in certain positions
//should try to optimize
int checkIfComputerIsGoingToLose();
//last case move position
int attacking();
//calls other methods to determine where to move
int pointSystem();
//checks if move is valid, used for checking double setup
int checkValidMove(int, char);
//prints nextBoard, not used while running - was used for testing
void printNextBoard();
//gets number from board, attempt to optimize
int getNumberFromBoard(char, char);
//2nd stage of attacking after checkIfDoubleSetup();
int secondStageAttack();
//Checks for a double setup
int checkIfDoubleSetup();

int main() {
	numberOfPlayers = getNumberOfPlayers();
	resetBoard();
}

int gameRunner() {
	int player = 1, i = -1, choice, whoStarts;
	string playAgain;
	char mark;

	whoStarts = getStartingPlayer();
	do {
		i = checkGameState();
		printBoard();
		player = (player % 2) ? 1 : 2;

		if (turns == 0 && whoStarts == 2)
			player = 2;
		if (player == 1 || numberOfPlayers == 2) {
			choice = getUserMove(player);
		}

		mark = (player == 1) ? 'X' : 'O';
		if (player != 1 && numberOfPlayers == 1)
			choice = HenryTheComputer();

		if (choice == 1 && board[0][0].find('1') != std::string::npos)
			board[0][0] = mark;
		else if (choice == 2 && board[0][1].find('2') != std::string::npos)
			board[0][1] = mark;
		else if (choice == 3 && board[0][2].find('3') != std::string::npos)
			board[0][2] = mark;
		else if (choice == 4 && board[0][3].find('4') != std::string::npos)
			board[0][3] = mark;
		else if (choice == 5 && board[1][0].find('5') != std::string::npos)
			board[1][0] = mark;
		else if (choice == 6 && board[1][1].find('6') != std::string::npos)
			board[1][1] = mark;
		else if (choice == 7 && board[1][2].find('7') != std::string::npos)
			board[1][2] = mark;
		else if (choice == 8 && board[1][3].find('8') != std::string::npos)
			board[1][3] = mark;
		else if (choice == 9 && board[2][0].find('9') != std::string::npos)
			board[2][0] = mark;
		else if (choice == 10 && board[2][1].find('10') != std::string::npos)
			board[2][1] = mark;
		else if (choice == 11 && board[2][2].find('11') != std::string::npos)
			board[2][2] = mark;
		else if (choice == 12 && board[2][3].find('12') != std::string::npos)
			board[2][3] = mark;
		else if (choice == 13 && board[3][0].find('13') != std::string::npos)
			board[3][0] = mark;
		else if (choice == 14 && board[3][1].find('14') != std::string::npos)
			board[3][1] = mark;
		else if (choice == 15 && board[3][2].find('15') != std::string::npos)
			board[3][2] = mark;
		else if (choice == 16 && board[3][3].find('16') != std::string::npos)
			board[3][3] = mark;
		else {
			std::cout << "Invalid move " << choice;
			player--;
			std::cin.ignore();
			std::cin.get();
		}
		i = checkGameState();
		if (player == 2)
			turns++;
		player++;
	} while (i == -1);
	printBoard();
	if (i == 1) {
		std::cout << "==>\aPlayer " << --player << " wins in " << turns << " turns.";
		turns = 0;
		if (player == 1)
			playerOneWins += 1;
		else
			playerTwoWins += 1;
	}
	else {
		std::cout << "==>\aGame draw";
		draws++;
		turns = 0;
	}
	std::cout << "\nWould you like to play again?";
	std::cin >> playAgain;
	if (playAgain == "yes") {
		resetBoard();
	}
	else {
		afterGame();
	}
	return 0;
}

void afterGame() {
	std::cout << "\nPLayer 1 won " << playerOneWins << " times.\n";
	if (numberOfPlayers == 2)
		std::cout << "Player 2 won " << playerTwoWins << " times.\n";
	else
		std::cout << "Henry won " << playerTwoWins << " times.\n";
	std::cout << "Draws: " << draws;
	std::cin.ignore();
	std::cin.get();
	exit(10);
}

void resetBoard() {
	int pos = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = std::to_string(pos);
			pos++;
		}
	}
	gameRunner();
}

void printBoard() {
	//clears output
	system("cls");

	std::cout << "\n\n\tAlmost Tic Tac Toe\n\n";
	std::cout << "Player 1 (X)  -  Player 2 (O)" << std::endl << std::endl;
	std::cout << "Player 1 wins(" << playerOneWins << ") - Player 2 wins(" << playerTwoWins << ") - Draws(" << draws << ")\n";
	std::cout << std::endl;

	//1-4
	std::cout << "     |     |     |     \n" << std::endl;
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			std::cout << "  " << board[0][i] << "  |  ";
		else if (i == 3)
			std::cout << board[0][i];
		else	std::cout << board[0][i] << "  |  ";
	}
	std::cout << "\n_____|_____|_____|_____" << std::endl;
	std::cout << "\n     |     |     |     " << std::endl;

	//4-8
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			std::cout << "  " << board[1][i] << "  |  ";
		else if (i == 3)
			std::cout << board[1][i];
		else	std::cout << board[1][i] << "  |  ";
	}
	std::cout << "\n_____|_____|_____|_____" << std::endl;
	std::cout << "\n     |     |     |     " << std::endl;

	//8-12
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			std::cout << "  " << board[2][i] << "  |  ";
		else if (i == 3)
			std::cout << board[2][i];
		else 
		if (board[2][i].find('X') != std::string::npos || board[2][i].find('O') != std::string::npos)
			std::cout << board[2][i] << "  |  ";
		else
			std::cout << board[2][i] << " |  ";
	}
	std::cout << "\n_____|_____|_____|_____" << std::endl;
	std::cout << "\n     |     |     |     " << std::endl;

	//12-16
	for (int i = 0; i < 4; i++) {
		if (i == 0 && (board[3][i].find('X') != std::string::npos || board[3][i].find('O') != std::string::npos))
			std::cout << "  " << board[3][i] << "  |  ";
		else if (i == 0 && board[3][0].find('X') == std::string::npos || i == 0 && board[3][0].find('O') == std::string::npos)
			std::cout << " " << board[3][0] << "  |  ";
		else if (i == 3)
			std::cout << board[3][i];
		else if (board[3][i].find('X') != std::string::npos || board[3][i].find('O') != std::string::npos)
			std::cout << board[3][i] << "  |  ";
		else
			std::cout << board[3][i] << " |  ";
	}
	std::cout << "\n     |     |     |     " << std::endl << std::endl;
}

int checkGameState() {
	//checks rows
	for (int i = 0; i < 4; i++) {
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] == board[i][3])
			return 1;
	}
	//checks columns
	for (int i = 0; i < 4; i++) {
		if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] == board[3][i])
			return 1;
	}
	//checks diagonals
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] == board[3][3])
		return 1;
	else if (board[3][0] == board[2][1] && board[2][1] == board[1][2] && board[1][2] == board[0][3])
		return 1;
	else if (board[0][0].find('1') == std::string::npos && board[0][1].find('2') == std::string::npos &&
		board[0][2].find('3') == std::string::npos && board[0][3].find('4') == std::string::npos &&
		board[1][0].find('5') == std::string::npos && board[1][1].find('6') == std::string::npos &&
		board[1][2].find('7') == std::string::npos && board[1][3].find('8') == std::string::npos &&
		board[2][0].find('9') == std::string::npos && board[2][1].find('10') == std::string::npos &&
		board[2][2].find('11') == std::string::npos && board[2][3].find('12') == std::string::npos &&
		board[3][0].find('13') == std::string::npos && board[3][1].find('14') == std::string::npos &&
		board[3][2].find('15') == std::string::npos && board[3][3].find('16') == std::string::npos)
		return 0;
	else return -1;
}

int getNumberOfPlayers() {
	int players = -2, num;
	do {
		std::cout << "1 or 2 players?";
		std::cin >> num;
		if (std::cin.fail()) {
			std::cout << "[Error] Invalid move!\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (num >= 0 && num <= 2)
			players = num;
		else {
			std::cout << "[Error] Invalid move!\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while ((players < -1 || players > 3));
	return players;
}

int getUserMove(int player) {
	int move = -1, choice = -1;
	do {
		std::cout << "Player " << player << ", enter a number:  ";
		std::cin >> choice;
		if (choice > 0 && choice <= 16)
			move = choice;
		else {
			std::cout << "[Error] Invalid move!\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while ((move < 0 || move > 17));
	return move;
}

int getStartingPlayer() {
	int playerStarting = -1, num;
	do {
		std::cout << "Player 1 or Player 2 is starting?";
		std::cin >> num;
		if (std::cin.fail()) {
			std::cout << "[Error] Invalid move!\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (num >= 1 && num <= 2)
			playerStarting = num;
		else {
			std::cout << "[Error] Invalid move!\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while ((playerStarting < 0 || playerStarting > 3));
	return playerStarting;
}

int HenryTheComputer() {
	return pointSystem();
}

int getNumberFromBoard(char x, char y) {
	if (x == '0' && y == '0')
		return 1;
	else return 0;
}

int checkIfComputerIsGoingToLose() {
	//checks 1-4
	if (nextBoard[0][1] == nextBoard[0][2] && nextBoard[0][1] == nextBoard[0][3] && nextBoard[0][0].find('1') != std::string::npos)
		return getNumberFromBoard('0','0');
	else if (nextBoard[0][0] == nextBoard[0][2] && nextBoard[0][0] == nextBoard[0][3] && nextBoard[0][1].find('2') != std::string::npos)
		return 2;
	else if (nextBoard[0][0] == nextBoard[0][1] && nextBoard[0][0] == nextBoard[0][3] && nextBoard[0][2].find('3') != std::string::npos)
		return 3;
	else if (nextBoard[0][0] == nextBoard[0][1] && nextBoard[0][0] == nextBoard[0][2] && nextBoard[0][3].find('4') != std::string::npos)
		return 4;
		
	//checks 4-8
	else if (nextBoard[1][1] == nextBoard[1][2] && nextBoard[1][1] == nextBoard[1][3] && nextBoard[1][0].find('5') != std::string::npos)
		return 5;
	else if (nextBoard[1][0] == nextBoard[1][2] && nextBoard[1][0] == nextBoard[1][3] && nextBoard[1][1].find('6') != std::string::npos)
		return 6;
	else if (nextBoard[1][0] == nextBoard[1][1] && nextBoard[1][0] == nextBoard[1][3] && nextBoard[1][2].find('7') != std::string::npos)
		return 7;
	else if (nextBoard[1][0] == nextBoard[1][1] && nextBoard[1][0] == nextBoard[1][2] && nextBoard[1][3].find('8') != std::string::npos)
		return 8;
	//checks 9-12
	else if (nextBoard[2][1] == nextBoard[2][2] && nextBoard[2][0] == nextBoard[2][3] && nextBoard[2][0].find('9') != std::string::npos)
		return 9;
	else if (nextBoard[2][0] == nextBoard[2][2] && nextBoard[2][0] == nextBoard[2][2] && nextBoard[2][1].find('10') != std::string::npos)
		return 10;
	else if (nextBoard[2][0] == nextBoard[2][1] && nextBoard[2][0] == nextBoard[2][3] && nextBoard[2][2].find('11') != std::string::npos)
		return 11;
	else if (nextBoard[2][0] == nextBoard[2][1] && nextBoard[2][0] == nextBoard[2][2] && nextBoard[2][3].find('12') != std::string::npos)
		return 12;
	//checks 13-16
	else if (nextBoard[3][1] == nextBoard[3][2] && nextBoard[3][1] == nextBoard[3][3] && nextBoard[3][0].find('13') != std::string::npos)
		return 13;
	else if (nextBoard[3][0] == nextBoard[3][2] && nextBoard[3][0] == nextBoard[3][2] && nextBoard[3][1].find('14') != std::string::npos)
		return 14;
	else if (nextBoard[3][0] == nextBoard[3][1] && nextBoard[3][0] == nextBoard[3][3] && nextBoard[3][2].find('15') != std::string::npos)
		return 15;
	else if (nextBoard[3][0] == nextBoard[3][1] && nextBoard[3][0] == nextBoard[3][2] && nextBoard[3][3].find('16') != std::string::npos)
		return 16;
	//checks 1,5,9,13
	else if (nextBoard[1][0] == nextBoard[2][0] && nextBoard[1][0] == nextBoard[3][0] && nextBoard[0][0].find('1') != std::string::npos)
		return 1;
	else if (nextBoard[0][0] == nextBoard[2][0] && nextBoard[0][0] == nextBoard[3][0] && nextBoard[1][0].find('5') != std::string::npos)
		return 5;
	else if (nextBoard[0][0] == nextBoard[1][0] && nextBoard[0][0] == nextBoard[3][0] && nextBoard[2][0].find('9') != std::string::npos)
		return 9;
	else if (nextBoard[0][0] == nextBoard[1][0] && nextBoard[0][0] == nextBoard[2][0] && nextBoard[3][0].find('13') != std::string::npos)
		return 13;
	//checks 2,6,10,14
	else if (nextBoard[1][1] == nextBoard[2][1] && nextBoard[1][1] == nextBoard[3][1] && nextBoard[0][1].find('2') != std::string::npos)
		return 2;
	else if (nextBoard[0][1] == nextBoard[2][1] && nextBoard[0][1] == nextBoard[3][1] && nextBoard[1][1].find('6') != std::string::npos)
		return 6;
	else if (nextBoard[0][1] == nextBoard[1][1] && nextBoard[0][1] == nextBoard[3][1] && nextBoard[2][1].find('10') != std::string::npos)
		return 10;
	else if (nextBoard[0][1] == nextBoard[1][1] && nextBoard[0][1] == nextBoard[2][1] && nextBoard[3][1].find('14') != std::string::npos)
		return 14;
	//checks 3,7,11,15
	else if (nextBoard[1][2] == nextBoard[2][2] && nextBoard[1][2] == nextBoard[3][2] && nextBoard[0][2].find('3') != std::string::npos)
		return 3;
	else if (nextBoard[0][2] == nextBoard[2][2] && nextBoard[0][2] == nextBoard[3][2] && nextBoard[1][2].find('7') != std::string::npos)
		return 7;
	else if (nextBoard[0][2] == nextBoard[1][2] && nextBoard[0][2] == nextBoard[3][2] && nextBoard[2][2].find('11') != std::string::npos)
		return 11;
	else if (nextBoard[0][2] == nextBoard[1][2] && nextBoard[0][2] == nextBoard[2][2] && nextBoard[3][2].find('15') != std::string::npos)
		return 15;
	//checks 4,8,12,16
	else if (nextBoard[1][3] == nextBoard[2][3] && nextBoard[1][3] == nextBoard[3][3] && nextBoard[0][3].find('4') != std::string::npos)
		return 4;
	else if (nextBoard[0][3] == nextBoard[2][3] && nextBoard[0][3] == nextBoard[3][3] && nextBoard[1][3].find('8') != std::string::npos)
		return 8;
	else if (nextBoard[0][3] == nextBoard[1][3] && nextBoard[0][3] == nextBoard[3][3] && nextBoard[2][3].find('12') != std::string::npos)
		return 12;
	else if (nextBoard[0][3] == nextBoard[1][3] && nextBoard[0][3] == nextBoard[2][3] && nextBoard[3][3].find('16') != std::string::npos)
		return 16;
	//checks 1,6,11,16
	else if (nextBoard[1][1] == nextBoard[2][2] && nextBoard[1][1] == nextBoard[3][3] && nextBoard[0][0].find('1') != std::string::npos)
		return 1;
	else if (nextBoard[0][0] == nextBoard[2][2] && nextBoard[0][0] == nextBoard[3][3] && nextBoard[1][1].find('6') != std::string::npos)
		return 6;
	else if (nextBoard[0][0] == nextBoard[1][1] && nextBoard[0][0] == nextBoard[3][3] && nextBoard[2][2].find('11') != std::string::npos)
		return 11;
	else if (nextBoard[0][0] == nextBoard[1][1] && nextBoard[0][0] == nextBoard[2][2] && nextBoard[3][3].find('16') != std::string::npos)
		return 16;
	//checks 4.7.10,13
	else if (nextBoard[1][2] == nextBoard[2][1] && nextBoard[1][2] == nextBoard[3][0] && nextBoard[0][3].find('4') != std::string::npos)
		return 4;
	else if (nextBoard[0][3] == nextBoard[2][1] && nextBoard[0][3] == nextBoard[3][0] && nextBoard[1][2].find('7') != std::string::npos)
		return 7;
	else if (nextBoard[0][3] == nextBoard[1][2] && nextBoard[0][3] == nextBoard[3][0] && nextBoard[2][1].find('10') != std::string::npos)
		return 10;
	else if (nextBoard[0][3] == nextBoard[1][2] && nextBoard[0][3] == nextBoard[2][1] && nextBoard[3][0].find('13') != std::string::npos)
		return 13;
	else return -1;
}

int attacking() {
	if (board[1][1].find('6') != std::string::npos)
		return 6;
	else if (board[2][2].find('11') != std::string::npos)
		return 11;
	else if (board[1][2].find('7') != std::string::npos)
		return 7;
	else if (board[2][1].find('10') != std::string::npos)
		return 10;
	else if (board[0][0].find('1') != std::string::npos)
		return 1;
	else if (board[3][3].find('16') != std::string::npos)
		return 16;
	else if (board[0][3].find('4') != std::string::npos)
		return 4;
	else if (board[3][0].find('13') != std::string::npos)
		return 13;
	else if (board[0][1].find('2') != std::string::npos)
		return 2;
	else if (board[0][2].find('3') != std::string::npos)
		return 3;
	else if (board[1][0].find('5') != std::string::npos)
		return 5;
	else if (board[1][3].find('8') != std::string::npos)
		return 8;
	else if (board[2][0].find('9') != std::string::npos)
		return 9;
	else if (board[2][3].find('12') != std::string::npos)
		return 12;
	else if (board[3][1].find('14') != std::string::npos)
		return 14;
	else return 15;
}

void copyBoard() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			nextBoard[i][j] = board[i][j];
		}
	}
}

void printNextBoard() {
	std::cout << "\n";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			nextBoard[i][j] = board[i][j];
			std::cout << nextBoard[i][j] << " ";
		}
		std::cout << "\n";
	}
}

int checkValidMove(int choice, char mark) {
	if (choice == 1 && board[0][0].find('1') != std::string::npos) {
		nextBoard[0][0] = mark;
		return 1;
	} else if (choice == 2 && board[0][1].find('2') != std::string::npos){
		nextBoard[0][1] = mark;
		return 1;
	} else if (choice == 3 && board[0][2].find('3') != std::string::npos) {
		nextBoard[0][2] = mark;
		return 1;
	} else if (choice == 4 && board[0][3].find('4') != std::string::npos) {
		nextBoard[0][3] = mark;
		return 1;
	} else if (choice == 5 && board[1][0].find('5') != std::string::npos) {
		nextBoard[1][0] = mark;
		return 1;
	} else if (choice == 6 && board[1][1].find('6') != std::string::npos) {
		nextBoard[1][1] = mark;
		return 1;
	} else if (choice == 7 && board[1][2].find('7') != std::string::npos) {
		nextBoard[1][2] = mark;
		return 1;
	} else if (choice == 8 && board[1][3].find('8') != std::string::npos) {
		nextBoard[1][3] = mark;
		return 1;
	} else if (choice == 9 && board[2][0].find('9') != std::string::npos) {
		nextBoard[2][0] = mark;
		return 1;
	} else if (choice == 10 && board[2][1].find('10') != std::string::npos) {
		nextBoard[2][1] = mark;
		return 1;
	} else if (choice == 11 && board[2][2].find('11') != std::string::npos) {
		nextBoard[2][2] = mark;
		return 1;
	} else if (choice == 12 && board[2][3].find('12') != std::string::npos) {
		nextBoard[2][3] = mark;
		return 1;
	} else if (choice == 13 && board[3][0].find('13') != std::string::npos) {
		nextBoard[3][0] = mark;
		return 1;
	} else if (choice == 14 && board[3][1].find('14') != std::string::npos) {
		nextBoard[3][1] = mark;
		return 1;
	} else if (choice == 15 && board[3][2].find('15') != std::string::npos) {
		nextBoard[3][2] = mark;
		return 1;
	} else if (choice == 16 && board[3][3].find('16') != std::string::npos) {
		nextBoard[3][3] = mark;
		return 1;
	} else
		return -1;
}

//should change to check if will lose on multiple accounts or just one
int checkIfDoubleSetup() {
	int move = -1, count = 0;
	for (int i = 1; i < 17; i++) {
		if (checkValidMove(i, 'X') || checkValidMove(i, 'O')) {
			move = checkIfComputerIsGoingToLose();
			copyBoard();
			if (move != -1)
				return move;
		}
	}
	return move;
}

//Needs more setups for starting at positons like 2, 3, 5, 9
int secondStageAttack() {
	int move = 0;
	for (int i = 0; i < 4; i++) {
		//checks 1-4 and 1,5,9,13
		if (nextBoard[0][i].find('X') == std::string::npos && nextBoard[i][0] == nextBoard[0][i] && nextBoard[0][3].find('4') != std::string::npos)
			return 4;
		else if (nextBoard[0][i].find('X') == std::string::npos && nextBoard[i][0] == nextBoard[0][i] && nextBoard[3][0].find('13') != std::string::npos)
			return 13;
		else if (nextBoard[0][i].find('X') == std::string::npos && nextBoard[i][0] == nextBoard[0][i] && nextBoard[0][1].find('2') != std::string::npos)
			return 2;
		else if (nextBoard[0][i].find('X') == std::string::npos && nextBoard[i][0] == nextBoard[0][i] && nextBoard[2][0].find('9') != std::string::npos)
			return 9;
		else if ((nextBoard[0][i].find('X') == std::string::npos && nextBoard[i][0] == nextBoard[0][i] && nextBoard[0][0].find('1') != std::string::npos))
			return 1;
		//checks 1-4 and 4,8,12,16
		else if (nextBoard[0][i].find('X') == std::string::npos && nextBoard[i][3] == nextBoard[0][i] && nextBoard[0][0].find('1') != std::string::npos)
			return 1;
		else if (nextBoard[0][i].find('X') == std::string::npos && nextBoard[i][3] == nextBoard[0][i] && nextBoard[3][3].find('16') != std::string::npos)
			return 16;
		else if (nextBoard[0][i].find('X') == std::string::npos && nextBoard[i][3] == nextBoard[0][i] && nextBoard[0][1].find('2') != std::string::npos)
			return 2;
		else if (nextBoard[0][i].find('X') == std::string::npos && nextBoard[i][3] == nextBoard[0][i] && nextBoard[3][1].find('14') != std::string::npos)
			return 14;
		else if (nextBoard[0][i].find('X') == std::string::npos && nextBoard[i][3] == nextBoard[0][i] && nextBoard[0][3].find('4') != std::string::npos)
			return 4;
		//checks 4,8,12,16 and 13-16
		else if (nextBoard[i][3].find('X') == std::string::npos && nextBoard[i][3] == nextBoard[3][i] && nextBoard[0][3].find('4') != std::string::npos)
			return 4;
		else if (nextBoard[i][3].find('X') == std::string::npos && nextBoard[i][3] == nextBoard[3][i] && nextBoard[3][0].find('13') != std::string::npos)
			return 13;
		else if (nextBoard[i][3].find('X') == std::string::npos && nextBoard[i][3] == nextBoard[3][i] && nextBoard[2][3].find('12') != std::string::npos)
			return 12;
		else if (nextBoard[i][3].find('X') == std::string::npos && nextBoard[i][3] == nextBoard[3][i] && nextBoard[3][2].find('15') != std::string::npos)
			return 15;
		else if (nextBoard[i][3].find('X') == std::string::npos && nextBoard[i][3] == nextBoard[3][i] && nextBoard[3][3].find('16') != std::string::npos)
			return 16;
		//checks 1,5,9,13 and 13-16 
		else if (nextBoard[i][0].find('X') == std::string::npos && nextBoard[i][0] == nextBoard[3][i] && nextBoard[0][0].find('1') != std::string::npos)
			return 1;
		else if (nextBoard[i][0].find('X') == std::string::npos && nextBoard[i][0] == nextBoard[3][i] && nextBoard[3][3].find('16') != std::string::npos)
			return 16;
		else if (nextBoard[i][0].find('X') == std::string::npos && nextBoard[i][0] == nextBoard[3][i] && nextBoard[3][1].find('14') != std::string::npos)
			return 14;
		else if (nextBoard[i][0].find('X') == std::string::npos && nextBoard[i][0] == nextBoard[3][i] && nextBoard[2][0].find('9') != std::string::npos)
			return 9;
		else if (nextBoard[i][0].find('X') == std::string::npos && nextBoard[i][0] == nextBoard[3][i] && nextBoard[3][0].find('13') != std::string::npos)
			return 13;
	}
	return -1;
}

int pointSystem() {
	int move;
	copyBoard();
	move = checkIfComputerIsGoingToLose();
	if (move != -1)
		return move;
	move = checkIfDoubleSetup();
	if (move != -1) 
		return move;
	move = secondStageAttack();
	if (move != -1)
		return move;
	return attacking();
}