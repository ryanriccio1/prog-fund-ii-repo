// Author: Ryan Riccio
// Assignment Number: Lab 2: Diamond Patter
// File Name: DL3_L2_Riccio.cpp
// Course/Section: COSC 1337 Section DL3
// Due Date: September 15th, 2020
// Instructor: Professor Paul Thayer
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

void DisplayDiamond(int rows)
{
	// spaces = the truncated value of row/2 rounded up - 1 (eg. 7 / 2 = 3.5 -> 4 - 1 = 3)
	int spaces = static_cast<int>(ceil(rows / 2.0)) - 1;

	// start the char counter (total chars per row)
	int counter = (rows / 2) + 1;

	// are we printing the bottom half yet?
	bool bottom_rows = false;

	for (int i = rows; i > 0; i--)
	{
		// print row
		cout << string(abs(spaces), ' ') << string(counter - abs(spaces), '*') << '\n';
		// when we hit the bottom half
		if (counter >= rows && bottom_rows != true)
		{
			// set flag as true
			bottom_rows = true;
			// if it's even
			if (rows % 2 == 0)
			{
				spaces++;
				counter++;
			}
		}
		// decide whether to increment or decrement counter
		if (bottom_rows == true)
			counter--;
		else
			counter++;
		spaces--;
	}
}

// main function
int main()
{
	cout << "DIAMOND GENERATOR 3000\n" << endl;
	// initialize 
	int rows{1};
	while (rows != 0)
	{
		cout << "How many rows do you want to print (0 to exit): ";

		cin >> rows;
		// error checking
		if (cin.fail())
		{
			cout << "You did not enter a valid input, please try again.\n" << endl;
			// clear cin stream and make sure rows var is not < 0
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			rows = 1;
		}
		// exit loop when user enters 0
		else if (rows <= 0)
			continue;
		else
		{
			// run the main DisplayDiamond function
			cout << "\n";
			DisplayDiamond(rows);
			cout << endl;
		}
	}
	cout << "\nThanks for using my program! Have a nice day!" << endl;
	return EXIT_SUCCESS;
}
/*
DIAMOND GENERATOR 3000

How many rows do you want to print(0 to exit) : 1

*

How many rows do you want to print(0 to exit) : 2

**
**

How many rows do you want to print(0 to exit) : 3

 *
***
 *

How many rows do you want to print(0 to exit) : 4

 **
****
****
 **

How many rows do you want to print(0 to exit) : 5

  *
 ***
*****
 ***
  *

How many rows do you want to print(0 to exit) : 6

  **
 ****
******
******
 ****
  **

How many rows do you want to print(0 to exit) : 7

   *
  ***
 *****
*******
 *****
  ***
   *

How many rows do you want to print(0 to exit) : 8

   **
  ****
 ******
********
********
 ******
  ****
   **

How many rows do you want to print(0 to exit) : sfghsdh
You did not enter a valid input, please try again.

How many rows do you want to print(0 to exit) : 0

Thanks for using my program!Have a nice day!

C : \Users\rshar\Desktop\Projects\School\COSC - 1337\Release\DL3_L2_Riccio.exe(process 16180) exited with code 0.
Press any key to close this window . . .
*/