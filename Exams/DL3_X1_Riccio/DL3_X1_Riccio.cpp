/*
  Name: Ryan Riccio
  COSC 1337 2020 Fall
  Exam 1, Programming portion
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;

// global enum to reference options
enum class Option { Month = 'm', Day = 'd', Year = 'y', Accept = 'a', Refuse = 'r' };
const int num_months = 12;  // num of months used globally in multiple calculations

// struct to store month info
struct MonthInfo
{
    const char* name;
    int num_days;
};

// array of structs to store all months
const MonthInfo months[num_months] =
{
    { "Jan", 31 },
    { "Feb", 28 },
    { "Mar", 31 },
    { "Apr", 30 },
    { "May", 31 },
    { "Jun", 30 },
    { "Jul", 31 },
    { "Aug", 31 },
    { "Sep", 30 },
    { "Oct", 31 },
    { "Nov", 30 },
    { "Dec", 31 },
};

// input validation function
int get_input(
    const char* prompt,
    const char* error_msg,
    int min_value=1,
    int max_value=12,
    bool range_check=false)
{
    int input{};
    while (true)
    {
        // display prompt based on if range_check is true
        cout << prompt;
        range_check ? cout << " (" << min_value << '-' << max_value << "): " : cout << ": ";
        // check for validity
        if (cin >> input)
        {
            // check if in range, otherwise start over
            if (range_check)
                if (input < min_value || input > max_value)
                {
                    cout << "That is not in the correct range.\n";
                    continue;
                }
            return input;
        }
        else
        {
            // when error, clear flags and buffer
            cout << error_msg;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }
}

// option validation function
void get_option(Option& option, const char* prompt)
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
        if (inputString[0] == 'm' ||
            inputString[0] == 'd' ||
            inputString[0] == 'y' ||
            inputString[0] == 'a' || 
            inputString[0] == 'r')
            break;
        cout << "That is not one of the options.\n";
    }
    // cast as type option and return
    option = static_cast<Option>(inputString[0]);
}

// leap year calculation function
bool is_leap_year(const int& year)
{
    // if year is divisible by 100, it is not
    // a leap year, unless it is also divisible
    // by 400. If not, then if it is divisible
    // by 4, it is a leap year
    if (year % 100 == 0 && year % 400 == 0)
        return true;
    else if (year % 100 == 0)
        return false;
    else if (year % 4 == 0)
        return true;
    else
        return false;
}

// date validation function
bool validate_date(const int month, const int day, const int year)
{
    // calculate max days for month and year
    int max_days = (is_leap_year(year) && month == 2) ? months[month - 1].num_days + 1 : months[month - 1].num_days;
    if (day > max_days)
        cout << "Not a valid date. Please enter a new date.\n";
    return day <= max_days;
}

// prize winning function
bool won_prize(const int odds)
{
    // convert odds to percent
    double percent_odds = 1.0 / odds;
    // random number mod 100 will be a number between 0 and 99
    // if it is greater than percentage value of winning, return true
    return rand() % 100 < (percent_odds * 100);
}

// main
int main() 
{
    // title and random seed
    cout << "COSC 1337 Exam 1 Lab Portion" << endl;
    srand(static_cast<unsigned>(time(0)));

    // get year and check if leap
    int year = get_input("Enter birth year", "That input is not valid\n", 1900, 2020, true);
    bool leap_year = is_leap_year(year);

    // get month and get max days for month (including if leap year)
    int month = get_input("Enter birth month", "That input is not valid\n", 1, num_months, true);
    int max_days = (leap_year && month == 2) ? months[month - 1].num_days + 1 : months[month - 1].num_days;

    // get days
    int day = get_input("Enter birth day", "That input is not valid\n", 1, max_days, true);

    // bools to control while loop entry and exit
    bool valid = true;
    bool accepted = false;
    while (!valid || !accepted)
    {
        // get option and use switch statement
        cout << '\n' << month << '/' << day << '/' << year;
        Option option{ Option::Accept };
        get_option(option, " -- CHANGE: (m)onth, (d)ay, (y)ear, (a)ccept, (r)efuse: ");
        switch (option)
        {
        case Option::Month:
            // get month and validate new date
            month = get_input("Enter birth month", "That input is not valid\n", 1, num_months, true);
            valid = validate_date(month, day, year);
            break;
        case Option::Day:
            // get max days for current month and year, get days and validate new date
            max_days = (leap_year && month == 2) ? months[month - 1].num_days + 1 : months[month - 1].num_days;
            day = get_input("Enter birth day", "That input is not valid\n", 1, max_days, true);
            valid = validate_date(month, day, year);
            break;
        case Option::Year:
            // get new year, validate, and check to see if it is a leap year
            year = get_input("Enter birth year", "That input is not valid\n", 1900, 2020, true);
            valid = validate_date(month, day, year);
            leap_year = is_leap_year(year);
            break;
        case Option::Accept:
            // double check to make sure we are valid before we exit
            valid = validate_date(month, day, year);
            if (valid)
                accepted = true;
            else
                cout << "Cannot accept.\n";
            break;
        case Option::Refuse:
            // leave program early
            cout << "\n\nGoodbye!\n";
            return EXIT_SUCCESS;
        }
    }
    // see if contestant won prize
    if (won_prize(100))
        cout << "\nYou won a prize!!!!!\n";
    else
        cout << "\nYou didn't win a prize :(\n";

    // calculate odds
    cout << "\nOf 10,000 attempts, ";
    int prizes_won{ 0 };
    for (int count{ 0 }; count < 10000; count++)
        if (won_prize(100))
            prizes_won++;
    cout << prizes_won << " won. " << fixed << setprecision(2) << prizes_won / 100.0 << "% won.\n";

    // wish them an early (or late) happy birthday and exit
    cout << "I'll be sure to send you a present on " << months[month - 1].name << ' ' << day << "\n";
    cout << "\n\nGoodbye!\n";
    return EXIT_SUCCESS;
}
/*
COSC 1337 Exam 1 Lab Portion
Enter birth year (1900-2020): 2004
Enter birth month (1-12): 5
Enter birth day (1-31): 31

5/31/2004 -- CHANGE: (m)onth, (d)ay, (y)ear, (a)ccept, (r)efuse: jhasasjk
That is not a valid input.
 -- CHANGE: (m)onth, (d)ay, (y)ear, (a)ccept, (r)efuse: m
Enter birth month (1-12): 2
Not a valid date. Please enter a new date.

2/31/2004 -- CHANGE: (m)onth, (d)ay, (y)ear, (a)ccept, (r)efuse: a
Not a valid date. Please enter a new date.
Cannot accept.

2/31/2004 -- CHANGE: (m)onth, (d)ay, (y)ear, (a)ccept, (r)efuse: d
Enter birth day (1-29): 29

2/29/2004 -- CHANGE: (m)onth, (d)ay, (y)ear, (a)ccept, (r)efuse: y
Enter birth year (1900-2020): 2003
Not a valid date. Please enter a new date.

2/29/2003 -- CHANGE: (m)onth, (d)ay, (y)ear, (a)ccept, (r)efuse: m
Enter birth month (1-12): 1

1/29/2003 -- CHANGE: (m)onth, (d)ay, (y)ear, (a)ccept, (r)efuse: y
Enter birth year (1900-2020): asdfkjasfjasdfkj
That input is not valid
Enter birth year (1900-2020): 1999

1/29/1999 -- CHANGE: (m)onth, (d)ay, (y)ear, (a)ccept, (r)efuse: a

You didn't win a prize :(

Of 10,000 attempts, 90 won. 0.90% won.
I'll be sure to send you a present on Jan 29


Goodbye!

C:\Users\rshar\Desktop\Projects\School\COSC-1337\Release\DL3_X1_Riccio.exe (process 20932) exited with code 0.
Press any key to close this window . . .

*/