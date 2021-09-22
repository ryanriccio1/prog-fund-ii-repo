// Author: Ryan Riccio
// Assignment Number: Lab 3: Math Program
// File Name: DL3_L3_Riccio.cpp
// Course/Section: COSC 1337 Section DL3
// Due Date: September 22nd, 2020
// Instructor: Professor Paul Thayer
#include <iostream>
#include <cstdlib>
#include <Windows.h>	// for color changing
#include <ctime>
using namespace std;

// random number generator (inclusive)
int GenerateRandomNumber(int MIN_VALUE, int MAX_VALUE)
{
	srand(static_cast<unsigned>(time(0)));
	return rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
}

// generate operands for addition and subtraction
void AddSubGen(int* operands)	// takes a pointer to an array as param so we don't have to copy
{
	int sum = GenerateRandomNumber(0, 100);
	int op_1 = GenerateRandomNumber(0, sum);
	int op_2 = sum - op_1;
	operands[0] = sum;
	operands[1] = op_1;
	operands[2] = op_2;
}

// generate operands for multiplication and division
void MultDivGen(int* operands)	// takes a pointer to an array as param so we don't have to copy
{
	int product{ GenerateRandomNumber(0, 100) };
	int factors[12]{1};
	int num_factors{ 0 };
	// find all factors
	for (int possible_factor = 1; possible_factor <= product; possible_factor++)
	{
		if (product % possible_factor == 0)
		{
			factors[num_factors] = possible_factor;
			num_factors++;
		}
	}
	// pick a factor and find its corresponding factor
	int op_1 = factors[GenerateRandomNumber(0, num_factors-1)];
	int op_2 = product / op_1;
	operands[0] = product;
	operands[1] = op_1;
	operands[2] = op_2;
}

// input validation
bool GetInput(int& input)
{
	// infinite loop that will be broken out of
	while (true)
	{
		cin >> input;

		// if it is a negative number (not our sentinel of -1) or it cannot be casted as int
		if (input < -1 || cin.fail())
		{
			cout << "\nThat's not a valid input.\nEnter your input again: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else   // when we have valid input leave inifinte loop
		{
			cout << '\n';
			break;
		}
	}
	// if the user wants to exit, return false and say goodbye, otherwise return true
	if (input == -1)
	{
		cout << "\nGoodbye!";
		return false;
	}
	return true;
}

// random feedback
void GiveFeedback(bool correct)	// bool determines whether to return positive or negative feedback
{
	// create console handle to change color in Windows
	HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// arrays of feedback
	const char* positive_feedback[] =
	{
		"Correct!",
		"That's Correct!",
		"That is right!",
		"Good Job :)",
		"Way to go!",
		"Keep up the good work!",
		"You got this!"
	};
	const char* negative_feedback[] =
	{
		"Incorrect :(",
		"You didn't get that one right.",
		"Keep working!",
		"Sorry, that's not correct.",
		"I know you can do better than that!",
		"That's incorrect.",
		"Try again next time."
	};

	if (correct)	// positive
	{
		// pick random response, set color, print feedback, return to white
		int random_index = GenerateRandomNumber(0, 6);
		SetConsoleTextAttribute(console_handle, 10);
		cout << positive_feedback[random_index] << "\n\n";
		SetConsoleTextAttribute(console_handle, 15);
	}
	else if (!correct)	// negative
	{
		// pick random response, set color, print feedback, return to white
		int random_index = GenerateRandomNumber(0, 6);
		SetConsoleTextAttribute(console_handle, 12);
		cout << negative_feedback[random_index] << "\n\n";
		SetConsoleTextAttribute(console_handle, 15);
	}
}

// data type to store Problem info
struct ProblemType
{
	const char* type_name;
	const char type_sign;
	bool is_add_sub;
	bool is_additive;
	int total_problems{ 0 };
	int num_correct{ 0 };
	ProblemType(const char* name, const char symbol, bool is_add_sub, bool is_additive) : 
		type_name(name),		// name of operation 
		type_sign(symbol),		// symbol for operation
		is_add_sub(is_add_sub),	// true = AddSubGen(), false = MultDivGen()
		is_additive(is_additive)// true = Add/Mult, false = Sub/Div
	{}
	int BuildProblem()
	{
		// generate random compatible numbers
		int operands[3];
		if (is_add_sub)
			AddSubGen(operands);
		else
			MultDivGen(operands);
		// assemble the output 
		if (is_additive)
		{
			cout << operands[1] << ' ' << type_sign << ' ' << operands[2] << " = ? ";
			return operands[0];
		}
		else
		{
			cout << operands[0] << ' ' << type_sign << ' ' << operands[1] << " = ? ";
			return operands[2];
		}
	}
};

// main program logic
int main()
{
	int input{};

	// array of ProblemTypes
	ProblemType Types[] =
	{
		ProblemType("Addition", '+', true, true),
		ProblemType("Subtraction", '-', true, false),
		ProblemType("Multiplication", 'x', false, true),
		ProblemType("Division", '/', false, false)
	};

	cout << "Welcome to the 3rd Grade Math Test!\n";
	cout << "How many questions would you like? (-1 to quit): ";

	// use input validation function and exit if given sentinel
	if (!GetInput(input))
		return EXIT_SUCCESS;

	// accumulator outside of for loop scope to keep track of completed problems
	int completed_problems{ 0 };

	// give problems
	for (int problem_index = 0; problem_index < input; problem_index++, completed_problems++)
	{
		// pick operation
		int option = GenerateRandomNumber(0, 3);

		// get correct answer and user answer for operation
		int correct_answer = Types[option].BuildProblem();
		int user_answer;
		if (!GetInput(user_answer))
			return EXIT_SUCCESS;
		else if (user_answer == correct_answer) // correct
		{
			GiveFeedback(true);
			Types[option].num_correct++;
		}
		else   // incorrect
			GiveFeedback(false);
		// in all cases, a problem is completed and added to the total_problems counter for this operation
		Types[option].total_problems++;
	}
	
	// give grade as long as we have completed a problem
	if (completed_problems != 0)
	{
		// accumulator of all operations
		int total_correct{ 0 };

		// keep track of worst skill
		double lowest_percent{ 1.0 };
		const char* lowest_skill{};

		// grade each operation
		for (int type_index = 0; type_index < 4; type_index++)
		{
			// add to accumulator
			total_correct += Types[type_index].num_correct;
			// only execute if we have completed a problem in this operation
			if (Types[type_index].total_problems != 0)
			{
				// calc percent for this operation
				double percent_correct = static_cast<double>(Types[type_index].num_correct) / Types[type_index].total_problems;
				// if it is the worst so far, keep track of it
				if (percent_correct < lowest_percent)
				{
					lowest_percent = percent_correct;
					lowest_skill = Types[type_index].type_name;
				}
				// display score
				cout << Types[type_index].type_name << ": " << Types[type_index].num_correct 
					<< " of " << Types[type_index].total_problems << ' ' << static_cast<int>(percent_correct * 100) 
					<< '%'<< endl;
			}	
		}
		// display total
		cout << "Total: " << total_correct << " of " << completed_problems << ' ' 
			<< static_cast<int>(static_cast<double>(total_correct) / completed_problems * 100.0) << '%' << endl;

		// if the user gets less than a C for any operation, tell them what to improve
		const double PASSING_GRADE = 0.7;
		if (lowest_percent < PASSING_GRADE)
			cout << "\nYou should work more on your " << lowest_skill << " skills." << endl;
		cout << "\nGoodbye!\n";
	}
	return EXIT_SUCCESS;
}
/*
Welcome to the 3rd Grade Math Test!
How many questions would you like ? (-1 to quit) : jhsjkdsnmfgnk

That's not a valid input.
Enter your input again : 10

36 - 20 = ? 16

That's Correct!

52 - 11 = ? 41

Correct!

72 - 71 = ? 1

Good Job : )

24 + 51 = ? 1234123

Try again next time.

17 x 5 = ? 12341234

You didn't get that one right.

94 / 94 = ? 1

Keep up the good work!

98 / 14 = ? 8

Incorrect : (

4 x 5 = ? 20

Good Job : )

23 - 17 = ? 5

You didn't get that one right.

4 x 14 = ? 56

Good Job : )

Addition: 0 of 1
Subtraction : 3 of 4
Multiplication : 2 of 3
Division : 1 of 2
Total : 6 of 10

You should work more on your Addition skills.

Goodbye!

C : \Users\rshar\Desktop\Projects\School\COSC - 1337\Release\DL3_L3_Riccio.exe(process 5428) exited with code 0.
Press any key to close this window . . .
*/