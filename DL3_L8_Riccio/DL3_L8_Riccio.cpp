// Author: Ryan Riccio
// Assignment Number: Lab 8: Tic Tac Toe
// File Name: DL3_L8_Riccio.cpp
// Course/Section: COSC 1337 Section DL3
// Due Date: November 3rd, 2020
// Instructor: Professor Paul Thayer
#include <iostream>
#include <iomanip>
#include <windows.h>	// for colors
#include <cstdlib>		// for rand
#include <ctime>		// for time()
using namespace std;

// enum to store states for boxes
enum class BoxState { Empty, X, O };
// alias for array to store board state consisting of box states
using BoardState = BoxState[3][3];

// separates a row/col/diag into an array of pointers to the corresponding BoardState
struct StateTriplet
{
	using StateArray = BoxState*[3];
	StateArray states;
	StateTriplet(BoardState & stateArray, int row, int col, int rowInc, int colInc)
		:states{ &stateArray[row][col], &stateArray[row + rowInc][col + colInc], &stateArray[row + 2 * rowInc][col + 2 * colInc] }
	{}
};

// main board data
class Board
{
public:
	// color enum (not enum class because enum class does not equate numbers with enum values)
	enum Color
	{ 
		Black=0, Blue, Green, Cyan, Red, Purple, Yellow, White,
		BBlack, BBlue, BGreen, BCyan, BRed, BPurple, BYellow, BWhite
	};
	static const int boardSize{ 3 };

private:
	// new 3x3 array of box states
	BoardState boardState;

	// for direct screen addressing
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position{ 0 };

	// store player stats
	int playerXScore{ 0 };
	int playerOScore{ 0 };
	int tieGames{ 0 };
	int totalGames{ 0 };

	// print border lines and board lines
	void PrintVerticalLines(int yMin, int yMax, int xPos = 0)
	{
		for (int yPos{ yMin }; yPos < yMax; yPos++)
		{
			SetCursor(xPos, yPos);
			cout << char(179); // char(179) = |
		}
	}
	void PrintHorizontalLines(int startX, int startY, int length, bool endCaps = false, 
		bool mirrored = false, bool bottom = false)
	{
		// end cap is on the left
		SetCursor(startX, startY);
		if (endCaps)
		{
			if (!mirrored)
				if (bottom)
					cout << char(192);	// |_
				else
					cout << char(218);	// |‾
			length--;	// remove end caps from total length
		}
		// fill lines
		for (int pos{ 0 }; pos < length; pos++)
			cout << char(196);	// -
		// if end cap is on the right
		if (endCaps)
			if (mirrored)
				if (bottom)
					cout << char(217);	// _|
				else
					cout << char(191);	// ‾|
	}
	void UpdateScore()
	{
		// direct screen addressing to place score
		SetCursor(5, 4);
		SetColor(Color::BBlack);
		cout << "[Score]";
		// Player X
		SetCursor(5, 6);			// Expected result:
		SetColor(Color::Red);		// [Score]
		cout << "Player X:\t";		// 
		SetColor(Color::White);		// Player X:	0
		cout << playerXScore;		// Player O:	0
		// Player O					// Tie Games:	0
		SetCursor(5, 7);			// Total:		0
		SetColor(Color::Blue);
		cout << "Player O:\t";
		SetColor(Color::White);
		cout << playerOScore;
		// Tie Games
		SetCursor(5, 8);
		SetColor(BBlack);
		cout << "Tie Games:\t";
		SetColor(Color::White);
		cout << tieGames;
		// Total
		SetCursor(5, 9);
		cout << "Total:\t" << totalGames;
	}
	bool CheckWin() const
	{
		// loop through array of split up axis
		for (int index{ 0 }; index < 8; index++)
		{
			// if 0 = 1 = 2 != Empty ie. X|X|X returns true
			if (*triplet[index].states[0] == *triplet[index].states[1] &&
				*triplet[index].states[0] == *triplet[index].states[2] &&
				*triplet[index].states[0] != BoxState::Empty)
				return true;
		}
		return false;
	};
	bool CheckTie() const
	{
		// if all of the axis have at least two different players in them, there cannot be a winner
		// but, if there are two empty spots in the same axis, or two of the same player in
		// a given axis, the game can still be won.
		bool tie = false;
		// loop through triplet array
		for (int index{ 0 }; index < 8; index++)
		{
			// if more than 2 boxes are not empty and those 2 boxes are not equal
			if (((*triplet[index].states[0] != BoxState::Empty &&	// ie. X|O|E
				*triplet[index].states[1] != BoxState::Empty) ||
				(*triplet[index].states[0] != BoxState::Empty &&	// ie. X|E|O
					*triplet[index].states[2] != BoxState::Empty) ||
				(*triplet[index].states[1] != BoxState::Empty &&	// ie. E|X|O
					*triplet[index].states[2] != BoxState::Empty)) &&
				(*triplet[index].states[0] != *triplet[index].states[1] ||		// ie. X|O|E
					*triplet[index].states[0] != *triplet[index].states[2] ||	// ie. X|E|O
					*triplet[index].states[1] != *triplet[index].states[2]))	// ie. E|X|O
				tie = true;
			else
				return false;
		}
		return tie;
	}

public:
	Board()
	{
		ClearBoard(false);
	}
	// array of each axis
	StateTriplet triplet[8] =
	{
		StateTriplet(boardState, 0, 0, 0, 1),
		StateTriplet(boardState, 1, 0, 0, 1),
		StateTriplet(boardState, 2, 0, 0, 1),
		StateTriplet(boardState, 0, 0, 1, 0),
		StateTriplet(boardState, 0, 1, 1, 0),
		StateTriplet(boardState, 0, 2, 1, 0),
		StateTriplet(boardState, 0, 0, 1, 1),
		StateTriplet(boardState, 2, 0, -1, 1)
	};
	// to simplify cursor movement
	void SetCursor(int x, int y)
	{
		position.X = x;
		position.Y = y;
		SetConsoleCursorPosition(screen, position);
	}
	// to simplify color changing
	void SetColor(Color fgColor, Color bgColor = Color::Black)
	{
		SetConsoleTextAttribute(screen, fgColor | bgColor*16);
	}
	// reset board state array
	void ClearBoard(bool newGame = true)
	{
		for (int row{ 0 }; row < boardSize; row++)
			for (int col{ 0 }; col < boardSize; col++)
				boardState[row][col] = BoxState::Empty;
		// if playing again, print the board, otherwise clear the screen
		if (newGame)
			UpdateBoard();
		else
			for (int row{ 1 }; row < 22; row++)
				for (int col{ 0 }; col < 60; col++)
				{
					SetCursor(col, row);
					cout << ' ';
				}
		SetCursor(0, 1);
	}
	void DrawScreen()
	{
		cout << endl;
		SetColor(White);
		SetCursor(0, 0);
		// prints border (char 205=double line, 201, 187, 200, 188=bends)   // _____ ___________ _____
		cout << char(201) << string(58, char(205)) << char(187) << endl;	// _____ ___________ _____
		for (int yPos{ 0 }; yPos < 18; yPos++)								// | |				   | |
			cout << char(186) << string(58, ' ') << char(186) << endl;		// | | <--58 spaces--> | | 
		cout << char(200) << string(58, char(205)) << char(188) << endl;	// | |                 | |			
		// 186 is double vertical line										// ‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾
		SetColor(BGreen);													// ‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾
		// border green accents
		PrintVerticalLines(2, 4, 2);	// top left
		PrintVerticalLines(2, 4, 57);	// top right
		PrintVerticalLines(16, 18, 2);	// bottom left
		PrintVerticalLines(16, 18, 57);	// bottom right
		// start pos, length, end caps, mirror, bottom
		PrintHorizontalLines(2, 1, 7, true, false, false);	// top left
		PrintHorizontalLines(2, 18, 7, true, false, true);	// bottom left
		PrintHorizontalLines(51, 1, 7, true, true, false);	// top right
		PrintHorizontalLines(51, 18, 7, true, true, true);	// bottom right

		// main tic tac toe board
		SetColor(BWhite);

		PrintHorizontalLines(24, 8, 3);		// beneath row 1
		PrintHorizontalLines(28, 8, 3);
		PrintHorizontalLines(32, 8, 3);

		PrintHorizontalLines(24, 10, 3);	// beneath row 2
		PrintHorizontalLines(28, 10, 3);
		PrintHorizontalLines(32, 10, 3);

		PrintVerticalLines(7, 12, 27);		// after column 1
		PrintVerticalLines(7, 12, 31);		// after column 2

		SetCursor(27, 8);	// top left
		cout << char(197);	// cross character

		SetCursor(31, 8);	// top right
		cout << char(197);	// cross char

		SetCursor(27, 10);	// bottom left
		cout << char(197);	// cross char

		SetCursor(31, 10);	// bottom right
		cout << char(197);	// cross char

		UpdateScore();		// print score sheet

		SetCursor(4, 20);	// set cursor to position for prompt
	}
	void UpdateBoard(BoxState currentPlayer = BoxState::Empty, const char* errMsg="", 
		BoxState winner = BoxState::Empty) 
	{
		// print either number or box state on board
		short int xPos = 24;
		short int yPos = 7;
		int currentCounter = 1;
		for (int row{ 0 }; row < boardSize; row++)
		{
			for (int col{ 0 }; col < boardSize; col++)
			{
				if (boardState[row][col] == BoxState::X)
				{
					SetCursor(xPos, yPos);
					SetColor(BRed, Red);
					cout << " X ";
				}
				else if (boardState[row][col] == BoxState::O)
				{
					SetCursor(xPos, yPos);
					SetColor(BCyan, Blue);
					cout << " O ";
				}
				else
				{
					SetCursor(xPos, yPos);
					SetColor(White);
					cout << ' ' << currentCounter << ' ';
				}
				currentCounter++;
				xPos += 4;
			}
			xPos -= 12;
			yPos += 2;
		}
		// print err msgs
		SetColor(Red);
		SetCursor(25, 16);
		if (errMsg != "")
			cout << errMsg;
		else   // clear err
			cout << "                   ";

		// no winner
		if (winner == BoxState::Empty)
		{
			// label
			SetCursor(22, 4);
			SetColor(BBlack);
			cout << "   [Player]   ";
			// input
			SetCursor(14, 15);
			cout << "[Enter]";
			SetColor(White);
			cout << " a position (0 - 9):         ";
			SetCursor(26, 5);
			// print current player
			if (currentPlayer == BoxState::X)
			{
				SetColor(Red);
				cout << "   X   ";
			}
			else if (currentPlayer == BoxState::O)
			{
				SetColor(Blue);
				cout << "   O   ";
			}
			else
				SetColor(White);
			SetCursor(42, 15);	// move to prompt
		}
		else
		{
			// display winner
			SetCursor(25, 4);
			SetColor(BBlack);
			cout << "[WINNER!]";
			SetCursor(26, 5);
			if (winner == BoxState::X)
			{
				SetColor(BRed, Red);
				cout << "   X   ";
			}
			else
			{
				SetColor(BCyan, Blue);
				cout << "   O   ";
			}
		}
	};
	void PrintPercents()
	{
		// do math and print table with percents once game finishes
		double xWin = playerXScore / static_cast<double>(totalGames) * 100.0;
		double oWin = playerOScore / static_cast<double>(totalGames) * 100.0;
		double tie = tieGames / static_cast<double>(totalGames) * 100.0;
		SetCursor(5, 11);
		SetColor(BBlack);
		cout << "Player X:\t" << fixed << setprecision(1) << xWin << '%';
		SetCursor(5, 12);
		cout << "Player O:\t" << fixed << setprecision(1) << oWin << '%';
		SetCursor(5, 13);
		cout << "Tied:\t" << fixed << setprecision(1) << tie << '%';
		SetColor(White);
	}
	bool Move(int selection, BoxState state) 
	{
		// convert numeric input to array index
		// if empty and in range, move and return true
		if (boardState[(selection - 1) / boardSize][(selection - 1) % boardSize] == BoxState::Empty && selection <= 9)
			boardState[(selection - 1) / boardSize][(selection - 1) % boardSize] = state;
		else
			return false;
		return true;
	};
	bool HasWon(BoxState& winner, int sleepTime = 2000)
	{
		// when win, run display functions and increase score
		if (CheckWin())
		{
			UpdateBoard(winner, "[WINNER!!]", winner);
			Sleep(sleepTime);
			ClearBoard();
			if (winner == BoxState::X)
				playerXScore++;
			else
				playerOScore++;
			totalGames++;
			winner = SwitchPlayer(winner);
			UpdateScore();
			return true;
		}
		return false;
	}
	bool HasTied(BoxState& currentPlayer, int sleepTime = 2000)
	{
		// when tie, run display functions and add to counters
		if (CheckTie())
		{
			UpdateBoard(currentPlayer, "[Tie Game]");
			Sleep(sleepTime);
			ClearBoard();
			currentPlayer = SwitchPlayer(currentPlayer);
			tieGames++;
			totalGames++;
			UpdateScore();
			return true;
		}
		return false;
	}
	// flips player
	static BoxState SwitchPlayer(BoxState boxState)
	{
		if (boxState == BoxState::X)
			return BoxState::O;
		else
			return BoxState::X;
	}
};

// computer logic
class ComputerOpponant
{
private:
	BoxState playerState = BoxState::Empty;
	// rand num gen
	int GetRand(int MIN_VALUE, int MAX_VALUE)
	{
		return rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
	}
	// can i win or lose in 1 move
	bool CanWinOrLose(Board board)
	{
		// loop twice. once checking for win, then lose
		// if any state is true for either player, either win, or block from win
		for (int counter{ 0 }; counter < 2; counter++)
		{
			// flip 
			BoxState currentPlayer;
			if (counter == 0)
				currentPlayer = playerState;
			else if (counter == 1)
				currentPlayer = Board::SwitchPlayer(currentPlayer);

			// loop through each axis
			for (int currentTriplet{ 0 }; currentTriplet < 8; currentTriplet++)
			{
				// if 0 = 1 & 2 = E ie. X|X|E
				if ((*board.triplet[currentTriplet].states[0] == *board.triplet[currentTriplet].states[1]) &&
					(*board.triplet[currentTriplet].states[0] == currentPlayer) &&
					(*board.triplet[currentTriplet].states[2] == BoxState::Empty))
				{
					*board.triplet[currentTriplet].states[2] = playerState;
					return true;
				}
				// if 1 = 2 & 0 = E ie. E|X|X
				if ((*board.triplet[currentTriplet].states[1] == *board.triplet[currentTriplet].states[2]) &&
					(*board.triplet[currentTriplet].states[1] == currentPlayer) &&
					(*board.triplet[currentTriplet].states[0] == BoxState::Empty))
				{
					*board.triplet[currentTriplet].states[0] = playerState;
					return true;
				}
				// if 0 = 2 & 1 = E ie. X|E|X
				if ((*board.triplet[currentTriplet].states[0] == *board.triplet[currentTriplet].states[2]) &&
					(*board.triplet[currentTriplet].states[0] == currentPlayer) &&
					(*board.triplet[currentTriplet].states[1] == BoxState::Empty))
				{
					*board.triplet[currentTriplet].states[1] = playerState;
					return true;
				}
			}
		}
		return false;
	}
	// can i place next to one of mine
	bool CanAdvance(Board board)
	{
		for (int currentTriplet{ 0 }; currentTriplet < 8; currentTriplet++)
		{
			// prefer two open spots, if there are, place next to it
			// X|E|E --> X|X|E
			if (*board.triplet[currentTriplet].states[0] == playerState &&
				*board.triplet[currentTriplet].states[1] == BoxState::Empty &&
				*board.triplet[currentTriplet].states[2] == BoxState::Empty)
			{
				*board.triplet[currentTriplet].states[1] = playerState;
				return true;
			}
			// E|X|E --> X|X|E
			if (*board.triplet[currentTriplet].states[1] == playerState &&
				*board.triplet[currentTriplet].states[0] == BoxState::Empty &&
				*board.triplet[currentTriplet].states[2] == BoxState::Empty)
			{
				*board.triplet[currentTriplet].states[0] = playerState;
				return true;
			}
			// E|E|X --> E|X|X
			if (*board.triplet[currentTriplet].states[2] == playerState &&
				*board.triplet[currentTriplet].states[0] == BoxState::Empty &&
				*board.triplet[currentTriplet].states[1] == BoxState::Empty)
			{
				*board.triplet[currentTriplet].states[1] = playerState;
				return true;
			}
			// if no two open spots are available, check for 1
			// X|E|O --> X|X|O
			if (*board.triplet[currentTriplet].states[0] == playerState &&
				*board.triplet[currentTriplet].states[1] == BoxState::Empty)
			{
				*board.triplet[currentTriplet].states[1] = playerState;
				return true;
			}
			// E|X|O -- > X|X|O
			if (*board.triplet[currentTriplet].states[1] == playerState &&
				*board.triplet[currentTriplet].states[0] == BoxState::Empty)
			{
				*board.triplet[currentTriplet].states[0] = playerState;
				return true;
			}
			// O|X|E --> O|X|X
			if (*board.triplet[currentTriplet].states[1] == playerState &&
				*board.triplet[currentTriplet].states[2] == BoxState::Empty)
			{
				*board.triplet[currentTriplet].states[2] = playerState;
				return true;
			}
			// O|E|X --> O|X|X
			if (*board.triplet[currentTriplet].states[2] == playerState &&
				*board.triplet[currentTriplet].states[1] == BoxState::Empty)
			{
				*board.triplet[currentTriplet].states[1] = playerState;
				return true;
			}
		}
		return false;
	}
	// when computer cant advance, pick a random spot
	void RandomMove(Board board)
	{
		while (true)
		{
			// pick random spot, if its not empty, pick again, if it is, place
			int randTriplet = GetRand(0, 7);
			int randBox = GetRand(0, 2);
			if (*board.triplet[randTriplet].states[randBox] == BoxState::Empty)
			{
				*board.triplet[randTriplet].states[randBox] = playerState;
				return;
			}
		}
	}

public:
	ComputerOpponant(BoxState selectedState)
	{
		// set state for instance 
		playerState = selectedState;
	}
	void Move(Board& board)
	{
		// movement decision pattern
		if (!CanWinOrLose(board))
			if (!CanAdvance(board))
				RandomMove(board);
	}
};

// input template
template<typename T>
T getInput(const char* prompt, const char* err_msg, T max, T min = T{})
{
	while (true)
	{
		cout << prompt; T item{};	// create item to store
		if (cin >> item && (item >= min && item <= max)) return item;	// check for failure
		cout << err_msg; cin.clear(); cin.ignore(INT_MAX, '\n'); // handle failure
	}
}

int main()
{
	int option = getInput("Do you want to play (1) 1v1, (2) 1vCPU, (3) CPUvCPU: ", "That is not a valid input!\n", 3, 1);
	Board board;
	srand(static_cast<unsigned>(time(0)));	// set seed
	
	// 1v1 or 1vCPU
	if (option == 1 || option == 2)
	{
		board.DrawScreen();
		BoxState currentPlayer = BoxState::X;
		ComputerOpponant computerPlayer(currentPlayer);
		while (true)
		{
			while (true)
			{
				// if its the computer's turn
				if (option == 2 && currentPlayer == BoxState::X)
				{
					// update, move, check, update, switch player
					board.UpdateBoard(currentPlayer);
					computerPlayer.Move(board);
					Sleep(450);
					if (board.HasWon(currentPlayer))
						break;
					else if (board.HasTied(currentPlayer))
						break;
					board.UpdateBoard(currentPlayer);
					currentPlayer = board.SwitchPlayer(currentPlayer);
				}
				// display current player turn
				board.UpdateBoard(currentPlayer);
				// get input, if valid continue, if not, tell player
				int sel{ 0 };
				if (cin >> sel)
				{
					// if valid move, perform checks
					if (board.Move(sel, currentPlayer))
					{
						if (board.HasWon(currentPlayer))
							break;
						else if (board.HasTied(currentPlayer))
							break;
					}
					else
					{
						// if invalid move, try again
						board.UpdateBoard(currentPlayer, "[Invalid Move]");
						Sleep(1000);
						continue;
					}
				}
				else
				{
					// when the entry is invalid, tell the play, clear buffer, try again
					board.UpdateBoard(currentPlayer, "[Invalid Entry]");
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					Sleep(1000);
					continue;
				}
				// if we reach this point, switch players
				currentPlayer = board.SwitchPlayer(currentPlayer);
			}
			// when game is over
			while (true)
			{
				board.SetCursor(14, 16);
				cout << "Play again (y/n): ";
				char input;
				cin >> input;

				// if play again, clear messages, play again
				if (tolower(input) == 'y')
				{
					board.SetCursor(14, 16);
					cout << "                     ";
					break;
				}
				// if not play again, exit and show percents
				else if (tolower(input) == 'n')
				{
					board.SetColor(Board::Color::White);
					board.PrintPercents();
					board.SetCursor(0, 22);
					cout << "Thanks for playing! Goodbye!\n";
					return EXIT_SUCCESS;
				}
				else
				{
					// if unknown, tell the player
					board.SetCursor(14, 17);
					board.SetColor(Board::Color::Red);
					cout << "Invalid";
					board.SetColor(Board::Color::White);
					Sleep(1000);
				}
				// make sure all messages are cleared, as well as buffer before trying again
				board.SetCursor(14, 16);
				cout << "                            ";
				board.SetCursor(14, 17);
				cout << "       ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
		}
	}

	if (option == 3)
	{
		// create instances and get information about simulation
		ComputerOpponant computerX(BoxState::X);
		ComputerOpponant computerO(BoxState::O);
		int maxIteration = getInput("How many iterations (1-100000): ", "That is not a valid input!\n", 100000, 1);
		int iterationTime = getInput("How many milliseconds/iteration (more time = less computer fans spinning up) (0-2000): ", 
			"That is not a valid input!\n", 2000, 0);
		int flipFlop = getInput("\nShould: \n(1) Computer X always go first \n(2) First player flip flops per game\n(1-2): ",
			"That is not a valid input!\n", 2, 1);
		unsigned int customSeed = getInput("\nEnter a custom seed (0 for default): ", "That is not a valid input!\n", INT_MAX, 0);
		if (customSeed != 0)
			srand(customSeed);
		bool flipped;
		// set flip flop info
		flipped = (flipFlop == 1) ? false : true;
		board.DrawScreen();
		BoxState currentComputer;
		// loop through number of iterations
		for (int currentIteration{ 0 }; currentIteration < maxIteration; currentIteration++)
		{
			while (true)
			{
				// because the each opponant's logic is the same, flip flopping makes
				// it more fair and balanced. This is info was reflected in 1v1 and 1vCPU

				// if no flip flop, or if previous player was computer O
				if (flipFlop == 1 || (flipFlop == 2 && !flipped))
				{
					currentComputer = BoxState::X;
					computerX.Move(board);
					flipped = true;
					if (board.HasWon(currentComputer, iterationTime))
						break;
					else if (board.HasTied(currentComputer, iterationTime))
						break;
				}

				currentComputer = BoxState::O;
				computerO.Move(board);
				flipped = false;
				if (board.HasWon(currentComputer, iterationTime))
					break;
				else if (board.HasTied(currentComputer, iterationTime))
					break;
			}
			board.ClearBoard();
		}
		board.PrintPercents();
		board.SetCursor(0, 22);
		cout << "Goodbye!\n\n";
	}
}

/*
╔══════════════════════════════════════════════════════════╗
║ ┌──────                                          ──────┐ ║
║ │                                                      │ ║
║ │                                                      │ ║
║    [Score]             [Player]                          ║
║                            X                             ║
║    Player X:  2                                          ║
║    Player O:  0        1 │ O │ X                         ║
║    Tie Games: 0       ───┼───┼───                        ║
║    Total:     2        O │ X │ O                         ║
║                       ───┼───┼───                        ║
║    Player X:  100.0%   X │ 8 │ 9                         ║
║    Player O:  0.0%                                       ║
║    Tied:      0.0%                                       ║
║                                                          ║
║             [Enter] a position (0 - 9):                  ║
║ │           Play again (y/n): n                        │ ║
║ │                                                      │ ║
║ └──────                                          ──────┘ ║
╚══════════════════════════════════════════════════════════╝


Thanks for playing! Goodbye!

C:\Users\rshar\Desktop\Projects\School\COSC-1337\Release\DL3_L8_Riccio.exe (process 17456) exited with code 0.
Press any key to close this window . . .
*/