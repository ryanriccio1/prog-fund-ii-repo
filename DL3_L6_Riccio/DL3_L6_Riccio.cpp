// Author: Ryan Riccio
// Assignment Number: Lab 6: Distance Calculator
// File Name: DL3_L6_Riccio.cpp
// Course/Section: COSC 1337 Section DL3
// Due Date: October 6th, 2020
// Instructor: Professor Paul Thayer
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

// enum class to store options
enum class Options { letter = 'l', number = 'n', point = 'p', quit = 'q' };

// to get option input
void GetOption(Options& option, const char* prompt)
{
	string inputString{};
	while (true)
	{
		// get input with prompt
		cout << prompt;
		cin >> inputString;
		// if more than 1 char, or char is not letter
		if (inputString.size() > 1 || !isalpha(inputString[0]))
		{
			cout << "That is not a valid input.\n";
			continue;
		}
		// if char not an option
		if (inputString[0] == 'l' ||
			inputString[0] == 'n' ||
			inputString[0] == 'p' ||
			inputString[0] == 'q')
			break;
		cout << "That is not one of the options.\n";
	}
	// cast as type option and return
	option = static_cast<Options>(inputString[0]);
}

// to get char input
char GetInput(const char* errorMessage = "That is not valid.\n")
{
	// static counter
	static int counter{ 1 };
	string inputString{};
	while (true)
	{
		// display prompt based on counter
		if (counter == 1)
			cout << "Enter first letter: ";
		if (counter == 2)
			cout << "Enter second letter: ";
		cin >> inputString;
		// if more than 1 char, or char is not letter
		if (inputString.size() > 1 || !isalpha(inputString[0]))
		{
			// clear cin flag and ignore stream buffer
			cout << errorMessage;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		break;
	}
	// reset counter and return uppercase
	if (counter == 2)
		counter = 0;
	counter++;
	return toupper(inputString[0]);
}

// to get double input
double GetInput(const int& minNum,
	const int& maxNum,
	const char* prompt = "Enter number",
	const char* errorMessage = "Not valid.")
{
	string inputString;
	while (true)
	{
		// display prompt and get input
		cout << prompt << " (" << minNum << ", " << maxNum << "): ";
		cin >> inputString;
		bool invalid = false;
		// make sure all chars are valid
		for (unsigned int index{ 0 }; index < inputString.size(); index++)
		{
			// when invalid, clear cin and break
			if (!(isdigit(inputString[index]) ||
				inputString[index] == '-' ||
				inputString[index] == '.'))
			{
				cout << errorMessage;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				invalid = true;
				break;
			}
		}
		// restart when invalid
		if (invalid)
			continue;
		// stod (string to double) the input string once verified valid
		if (stod(inputString) > maxNum || stod(inputString) < minNum)
		{
			cout << errorMessage;
			continue;
		}
		break;
	}
	// return double
	return stod(inputString);
}

// to get point input
void GetInput(int& x, int& y, const char* prompt = "Enter point")
{
	string inputString;
	// loop twice (once for x, once for y)
	for (int index{0}; index < 2; index++)
	{
		while (true)
		{
			if (index == 0) { cout << prompt << " (x): "; }
			else { cout << prompt << " (y): "; }
			cin >> inputString;
			bool invalid = false;
			// make sure all char are valid, if not clear cin stream
			for (unsigned int index{ 0 }; index < inputString.size(); index++)
			{
				if (!(isdigit(inputString[index]) ||
					inputString[index] == '-'))
				{
					cout << "That is not a valid input\n";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					invalid = true;
					break;
				}
			}
			// when invalid, restart, if not, set vars
			if (invalid)
				continue;
			break;
		}
		if (index == 0)
			x = stoi(inputString);
		else if (index == 1)
			y = stoi(inputString);
	}
}

// to display char dist
void Display(const char char1, const char char2, const char* message = "Distance between")
{
	// count total number of uses
	static int counter{ 1 };
	int distance = abs(char1 - char2);	// calc distance and display
	cout << "(#" << counter << ") " << message << " '" 
		<< char1 << "' and '" << char2 << "': " << distance << "\n\n";
	counter++;
}

// to display double dist
void Display(const double num1, const double num2, const char* message = "Distance between")
{
	// count total number of uses
	static int counter{ 1 };
	double distance = abs(num1 - num2);		// calc distance and display
	cout << "(#" << counter << ") " << message << ' '
		<< num1 << " and " << num2 << ": " << distance << "\n\n";
	counter++;
}

// to display point dist
void Display(const int x1, const int y1, 
	const int x2, const int y2, 
	const char* message = "Straight line distance between")
{
	// count number of uses
	static int counter{ 1 };
	double distance{ sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) }; // calc distance and display
	cout << fixed << setprecision(4) << "(#" << counter << ") " 
		<< message << " (" << x1 << ", " << y1 << ") and (" 
		<< x2 << ", " << y2 << "): "<< distance << "\n\n";
	counter++;
}

int main()
{
	// create Options type to store option
	Options option = Options::quit;
	while (true)
	{
		// get option with prompt
		GetOption(option, "Options: (l)etter, (n)umber, (p)oint, (q)uit: ");
		// case switching based on option
		switch (option)
		{
		case Options::letter:	// get chars, and display
		{
			char firstChar = GetInput();
			char secondChar = GetInput();
			Display(firstChar, secondChar);
			break;
		}
		case Options::number:	// get nums, and display
		{
			double firstNum = GetInput(-100, 100, "Enter first number", "Not valid.\n");
			double secondNum = GetInput(-200, 200, "Enter second number", "Not valid.\n");
			Display(firstNum, secondNum);
			break;
		}
		case Options::point:	// get points, and display
			int x1, y1, x2, y2;
			GetInput(x1, y1, "Enter the first point");
			GetInput(x2, y2, "Enter the second point");
			Display(x1, y1, x2, y2);
			break;
		case Options::quit:		// exit
			cout << "\n\nThanks for using the program! Goodbye!\n";
			return EXIT_SUCCESS;
		}
	}
}
/*
Options: (l)etter, (n)umber, (p)oint, (q)uit: l
Enter first letter: a
Enter second letter: z
(#1) Distance between 'A' and 'Z': 25

Options: (l)etter, (n)umber, (p)oint, (q)uit: l
Enter first letter: hjasdfjkasdfjkasdfjkasdfjkasdf
That is not valid.
Enter first letter: A
Enter second letter: jkaf23jk23jkjk32
That is not valid.
Enter second letter: c
(#2) Distance between 'A' and 'C': 2

Options: (l)etter, (n)umber, (p)oint, (q)uit: n
Enter first number (-100, 100): -101
Not valid.
Enter first number (-100, 100): 101
Not valid.
Enter first number (-100, 100): asdfjhasdfjsadf
Not valid.
Enter first number (-100, 100): -100
Enter second number (-200, 200): sfdknsdfgn
Not valid.
Enter second number (-200, 200): 200
(#1) Distance between -100 and 200: 300

Options: (l)etter, (n)umber, (p)oint, (q)uit: n
Enter first number (-100, 100): 100.12345
Not valid.
Enter first number (-100, 100): 0
Enter second number (-200, 200): -100.12345
(#2) Distance between 0 and -100.123: 100.123

Options: (l)etter, (n)umber, (p)oint, (q)uit: p
Enter the first point (x): 0
Enter the first point (y): 0
Enter the second point (x): -3
Enter the second point (y): -4
(#1) Straight line distance between (0, 0) and (-3, -4): 5.0000

Options: (l)etter, (n)umber, (p)oint, (q)uit: p
Enter the first point (x): hui1h212,h34h
That is not a valid input
Enter the first point (x): 0
Enter the first point (y): 0
Enter the second point (x): eglksdfg
That is not a valid input
Enter the second point (x): sdfg
That is not a valid input
Enter the second point (x): 6
Enter the second point (y): -8
(#2) Straight line distance between (0, 0) and (6, -8): 10.0000

Options: (l)etter, (n)umber, (p)oint, (q)uit: ahiasdhfk
That is not a valid input.
Options: (l)etter, (n)umber, (p)oint, (q)uit: a
That is not one of the options.
Options: (l)etter, (n)umber, (p)oint, (q)uit: q


Thanks for using the program! Goodbye!

C:\Users\rshar\Desktop\Projects\School\COSC-1337\Release\DL3_L6_Riccio.exe (process 21724) exited with code 0.
Press any key to close this window . . .

*/