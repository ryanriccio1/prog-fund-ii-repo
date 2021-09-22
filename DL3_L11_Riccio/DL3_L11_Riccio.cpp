// Author: Ryan Riccio
// Assignment Number: Lab 11: Date Calculator
// File Name: DL3_L11_Riccio.cpp
// Course/Section: COSC 1337 Section DL3
// Due Date: December 8th, 2020
// Instructor: Professor Paul Thayer
#include <iostream>
#include <algorithm>
using namespace std;

class Day
{
private:
	int day{ 0 };

public:
	// static vars will be init'd later
	static const int year{ 2019 };
	static const int daysInMonth[];
	static const string months[];
	static int lastDay;
	
	// constructors
	Day(int day)
	{
		// this truncates any year data
		if (day > 365)
			this->day = day % 365;
		else
			this->day = day;
	};
	Day(string month = "january", int day = 1, const string* searchResult = nullptr)
	{
		this->day = day;
		int monthIndex = distance(months, searchResult);	// gives the sub for the search result
		for (monthIndex; monthIndex >= 0; monthIndex--)
		{	// find num days leading up to current date
			this->day += daysInMonth[monthIndex - 1];	
		}
	};
	Day operator++()
	{
		// loop around and inc
		if (day == 365)
			day = 1;
		else
			day++;
		return *this;
	}
	Day operator++(int)
	{	// perform same op as before, just return a preinc version
		Day temp = *this;
		operator++();
		return temp;
	}
	Day operator--()
	{
		// loop around and dec
		if (day == 1)
			day = 365;
		else
			day--;
		return *this;
	}
	Day operator--(int)
	{	// perform same op as before, just return a predec version
		Day temp = *this;
		operator--();
		return temp;
	}
	friend ostream& operator<<(ostream& out, const Day& day);
	void print()
	{	// just use ostream overload
		cout << *this;
	}
};

ostream& operator<<(ostream& out, const Day& dayObj)
{	// print function and format to stream
	int daysCounter{ Day::daysInMonth[0] };
	for (int currentMonth{ 0 }; currentMonth < 12; currentMonth++)
	{
		if ((dayObj.day - daysCounter) > 0)
		{
			daysCounter += Day::daysInMonth[currentMonth + 1];
		}
		else
		{
			out << "  day#=[" << dayObj.day << "] " << Day::months[currentMonth] << " " << dayObj.day - (daysCounter - Day::daysInMonth[currentMonth]) << '\n';
			Day::lastDay = dayObj.day;
			break;
		}
	}
	return out;
}

// static vars init
const int Day::daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const string Day::months[] =
{
	"january",
	"february",
	"march",
	"april",
	"may",
	"june",
	"july",
	"august",
	"september",
	"october",
	"november",
	"december"
};
int Day::lastDay{ 1 };

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
void testOperators() 
{	// perform pre and post inc and dec ops
	Day lastDay(Day::lastDay);
	cout << "  using last entered date: " << lastDay << "Pre\n";
	for (int i = 0; i < 5; ++i) { cout << "--  "; (--lastDay).print(); } cout << endl;
	for (int i = 0; i < 5; ++i) { cout << "++  "; (++lastDay).print(); } cout << endl;
	cout << "Post\n";
	for (int i = 0; i < 5; ++i) { cout << "  ++"; (lastDay++).print(); } cout << endl;
	for (int i = 0; i < 5; ++i) { cout << "  --"; (lastDay--).print(); } cout << endl;
	cout << "  ended at: "; lastDay.print(); cout << endl;
}
// struct to create multi-typed 2D array
struct DayMonthStruct
{
	string month;
	int day;
};
// main function for day conversion
void dayToMonth(int day, bool userInput = true)
{
	while (true)
	{
		if (userInput)
			day = getInput("  enter day of year# (-9 to quit): ", "  ERROR: Invalid!\n", INT_MAX, -9);
		if (day == -9)
			break;
		if (day > 0)
		{	// could be dynamic or unique, but will immediately leave scope so no point
			Day dayToMonth(day);
			cout << dayToMonth;
			if (userInput)
				continue;
			else
				break;
		}
		else
		{	// just some checks
			cout << "  cannot be less than 1!\n";
			if (userInput)
				continue;
			else
				break;
		}
	}
}
// main function for month conversion
void monthToDay(string month, int day, bool userInput = true)
{
	while (true)
	{
		if (userInput)
		{
			cout << "  enter month and day of month: (stop -9 to quit): ";
			cin >> month >> day;
		}
		// perform ::tolower on each char in the string
		transform(month.begin(), month.end(), month.begin(), ::tolower);

		if (day == -9)
			break;
		else if (day <= 0)
		{
			cout << "  day cannot be less than 1\n";
			if (userInput)
				continue;
			else
				break;
		}

		// to search strings
		const string* searchResult = nullptr;
		int monthIndex{ 0 };
		// loop through all month names and search
		for (monthIndex; monthIndex < 12; monthIndex++)
		{	// will give pointer to the name
			if (Day::months[monthIndex].find(month) != string::npos)
			{
				searchResult = &Day::months[monthIndex];
				break;
			}
		}
		// if we dont find something, loop again
		if (searchResult == nullptr)
		{
			cout << "  that month cannot be found\n";
			if (userInput)
				continue;
			else
				break;
		}
		// when we find a valid date
		if (day <= Day::daysInMonth[monthIndex] && day > 0)
		{	// monthIndex can be passed, but pointer seems to work better
			// and is better practice with pointers
			// (searchResult is redundant, I just wanted more practice with pointers)
			Day monthToDays(month, day, searchResult);	// can be put on heap, but is better on stack because leaves scope quickly
			cout << monthToDays;
			if (userInput)
				continue;
			else
				break;
		}
		// if date is invalid
		else if (day >= Day::daysInMonth[monthIndex])
		{
			cout << "  that's too many days for that month\n";
			if (!userInput)
				break;
		}
	}
}
void various()
{	// some test parameters
	int numericTestCases[7] = { -1, 0, 1, 365, 366, 1000, 100000 };
	DayMonthStruct dayMonthTestCases[13] =
	{
		{"Jan", 1},
		{"jan", 31},
		{"January", 1},
		{"Jan", 32},
		{"feb", 29},
		{"may", -31},
		{"Au", 22},
		{"Augus", 1},
		{"Dec", 32},
		{"dec", 31},
		{"Foo", 30},
		{"Ma", 31},
		{"mar", 32},
	};

	// loop through given numbers 
	cout << "\n--Numeric Tests--\n\n";
	for (int testIndex{ 0 }; testIndex < 6; testIndex++)
	{
		int day = numericTestCases[testIndex];
		cout << "  day input: " << day << '\n';
		dayToMonth(day, false);
		cout << '\n';
	}

	// loop through months and days
	cout << "--Month/Day Tests--\n\n";
	for (int currentStruct{ 0 }; currentStruct < 13; currentStruct++)
	{
		cout << "  input: " << dayMonthTestCases[currentStruct].month << ' ' << dayMonthTestCases[currentStruct].day << '\n';
		monthToDay(dayMonthTestCases[currentStruct].month, dayMonthTestCases[currentStruct].day, false);
		cout << '\n';
	}
}

int main()
{
	string month;
	int day{ 0 };
	char input;
	enum class Option { Day = 'd', Month = 'm', Operator = 'o', Various = 'v', Quit = 'q' };

	while (true)
	{	// main menu
		cout << "options: d)ay [#d->m,d]; m)onth+day [m d->#d]; o)perator [+/-5]; v)arious; q)uit: ";
		cin >> input;
		cin.ignore(INT_MAX, '\n');

		// simple case switching
		switch ((Option)input)
		{
		case Option::Day:
			dayToMonth(day);
			continue;
		case Option::Month:
			monthToDay(month, day);
			continue;
		case Option::Operator:
			testOperators();
			break;
		case Option::Various:
			various();
			break;
		case Option::Quit:
			cout << "\n\nGoodbye!\n";
			return EXIT_SUCCESS;
		default:
			cout << "Not a valid menu option!\n";
			break;
		}
	}
}
/*
options: d)ay [#d->m,d]; m)onth+day [m d->#d]; o)perator [+/-5]; v)arious; q)uit: d
  enter day of year# (-9 to quit): 1
  day#=[1] january 1
  enter day of year# (-9 to quit): 15
  day#=[15] january 15
  enter day of year# (-9 to quit): 31
  day#=[31] january 31
  enter day of year# (-9 to quit): 32
  day#=[32] february 1
  enter day of year# (-9 to quit): 60
  day#=[60] march 1
  enter day of year# (-9 to quit): 100
  day#=[100] april 10
  enter day of year# (-9 to quit): 200
  day#=[200] july 19
  enter day of year# (-9 to quit): 300
  day#=[300] october 27
  enter day of year# (-9 to quit): 364
  day#=[364] december 30
  enter day of year# (-9 to quit): 365
  day#=[365] december 31
  enter day of year# (-9 to quit): 366
  day#=[1] january 1
  enter day of year# (-9 to quit): 1000
  day#=[270] september 27
  enter day of year# (-9 to quit): -1000
  ERROR: Invalid!
  enter day of year# (-9 to quit): 180
  day#=[180] june 29
  enter day of year# (-9 to quit): -9
options: d)ay [#d->m,d]; m)onth+day [m d->#d]; o)perator [+/-5]; v)arious; q)uit: m
  enter month and day of month: (stop -9 to quit): jan 1
  day#=[1] january 1
  enter month and day of month: (stop -9 to quit): jan 15
  day#=[15] january 15
  enter month and day of month: (stop -9 to quit): jan 31
  day#=[31] january 31
  enter month and day of month: (stop -9 to quit): feb 1
  day#=[32] february 1
  enter month and day of month: (stop -9 to quit): feb 28
  day#=[59] february 28
  enter month and day of month: (stop -9 to quit): feb 29
  that's too many days for that month
  enter month and day of month: (stop -9 to quit): march 15
  day#=[74] march 15
  enter month and day of month: (stop -9 to quit):  march 30
  day#=[89] march 30
  enter month and day of month: (stop -9 to quit): march 31
  day#=[90] march 31
  enter month and day of month: (stop -9 to quit): march 32
  that's too many days for that month
  enter month and day of month: (stop -9 to quit): july 1
  day#=[182] july 1
  enter month and day of month: (stop -9 to quit): jul 15
  day#=[196] july 15
  enter month and day of month: (stop -9 to quit): julipe 30
  that month cannot be found
  enter month and day of month: (stop -9 to quit): aug 23
  day#=[235] august 23
  enter month and day of month: (stop -9 to quit): au 23
  day#=[235] august 23
  enter month and day of month: (stop -9 to quit): augus 23
  day#=[235] august 23
  enter month and day of month: (stop -9 to quit): december 31
  day#=[365] december 31
  enter month and day of month: (stop -9 to quit): decber 31
  that month cannot be found
  enter month and day of month: (stop -9 to quit): dec 31
  day#=[365] december 31
  enter month and day of month: (stop -9 to quit): dec 32
  that's too many days for that month
  enter month and day of month: (stop -9 to quit): dec -1
  day cannot be less than 1
  enter month and day of month: (stop -9 to quit): jan 1
  day#=[1] january 1
  enter month and day of month: (stop -9 to quit): stop -9
options: d)ay [#d->m,d]; m)onth+day [m d->#d]; o)perator [+/-5]; v)arious; q)uit: o
  using last entered date:   day#=[1] january 1
Pre
--    day#=[365] december 31
--    day#=[364] december 30
--    day#=[363] december 29
--    day#=[362] december 28
--    day#=[361] december 27

++    day#=[362] december 28
++    day#=[363] december 29
++    day#=[364] december 30
++    day#=[365] december 31
++    day#=[1] january 1

Post
  ++  day#=[1] january 1
  ++  day#=[2] january 2
  ++  day#=[3] january 3
  ++  day#=[4] january 4
  ++  day#=[5] january 5

  --  day#=[6] january 6
  --  day#=[5] january 5
  --  day#=[4] january 4
  --  day#=[3] january 3
  --  day#=[2] january 2

  ended at:   day#=[1] january 1

options: d)ay [#d->m,d]; m)onth+day [m d->#d]; o)perator [+/-5]; v)arious; q)uit: v

--Numeric Tests--

  day input: -1
  cannot be less than 1!

  day input: 0
  cannot be less than 1!

  day input: 1
  day#=[1] january 1

  day input: 365
  day#=[365] december 31

  day input: 366
  day#=[1] january 1

  day input: 1000
  day#=[270] september 27

--Month/Day Tests--

  input: Jan 1
  day#=[1] january 1

  input: jan 31
  day#=[31] january 31

  input: January 1
  day#=[1] january 1

  input: Jan 32
  that's too many days for that month

  input: feb 29
  that's too many days for that month

  input: may -31
  day cannot be less than 1

  input: Au 22
  day#=[234] august 22

  input: Augus 1
  day#=[213] august 1

  input: Dec 32
  that's too many days for that month

  input: dec 31
  day#=[365] december 31

  input: Foo 30
  that month cannot be found

  input: Ma 31
  day#=[90] march 31

  input: mar 32
  that's too many days for that month

options: d)ay [#d->m,d]; m)onth+day [m d->#d]; o)perator [+/-5]; v)arious; q)uit: asdfasdf
Not a valid menu option!
options: d)ay [#d->m,d]; m)onth+day [m d->#d]; o)perator [+/-5]; v)arious; q)uit: q


Goodbye!

C:\Users\rshar\Desktop\Projects\School\COSC-1337\Debug\DL3_L11_Riccio.exe (process 5740) exited with code 0.
Press any key to close this window . . .

*/