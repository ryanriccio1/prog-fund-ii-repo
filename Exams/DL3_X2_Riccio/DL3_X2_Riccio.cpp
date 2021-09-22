/*
  Name: Ryan Riccio
  COSC 1337 Fall DL3
  Exam 2, Programming portion
*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

// main billfold class
class Billfold
{
private:
    int twenties{}, tens{}, fives{}, dollars{};
public:
    // Step 1 (5 points)
    Billfold(int newTwenties = 0, int newTens = 0, int newFives = 0, int newDollars = 0)
    {
        // Step 9 (5 points)
        // if not valid inputs, set them to 0
        if (!set(newTwenties, newTens, newFives, newDollars))
            set(0, 0, 0, 0);
    };

    // Step 3 (5 points)
    int total_value() const
    {
        return (twenties * 20) + (tens * 10) + (fives * 5) + (dollars * 1);
    }

    // Step 5 (5 points)
    bool set(int newTwenties, int newTens, int newFives, int newDollars)
    {
        // if any are less than zero, fail
        if (newTwenties >= 0 && newTens >= 0 &&
            newFives >= 0 && newDollars >= 0)
        {
            twenties = newTwenties;
            tens = newTens;
            fives = newFives;
            dollars = newDollars;
            return true;
        }
        return false;
    }

    // Step 6 (5 points)
    string show() const
    {
        // concatenate string and return
        string newString = "($20=" + to_string(twenties) + " $10=" + to_string(tens) 
            + " $5=" + to_string(fives) + " $1=" + to_string(dollars) + ")";
        return newString;
    }

    // Step 8 (5 points)
    bool modify(int twentyInc = 0, int tenInc = 0, int fiveInc = 0, int dollarInc = 0)
    {
        // as long as the final value is not negative, perform operation
        if ((twenties + twentyInc >= 0) &&
            (tens + tenInc >= 0) &&
            (fives + fiveInc >= 0) &&
            (dollars + dollarInc >= 0))
        {
            twenties += twentyInc;
            tens += tenInc;
            fives += fiveInc;
            dollars += dollarInc;
            return true;
        }
        return false;
    }
};

// Step 11 (EC)
void billfoldVectorDisplay() 
{
    // create vector
    vector<Billfold> billfoldVector =
    {
        Billfold(1, 1, 1, 1),
        Billfold(2, 4, 6, 8),
        Billfold(10, 10, 10, 10)
    };
    int counter{ 1 };
    int total{ 0 };
    cout << '\n';
    // loop through, display, add to total
    for (Billfold& billfold : billfoldVector)
    {
        cout << "Billfold " << counter << ": $" << billfold.total_value() << '\n';
        counter++;
        total += billfold.total_value();
    }
    cout << "Total: $" << total;
}

// input template
template<typename T>
T get_input(const char* prompt, const char* err_msg = "  invalid\n") 
{
    while (true) 
    {
        cout << prompt; T item{};
        if (cin >> item)
        {cin.clear(); cin.ignore(INT_MAX, '\n'); return item;}
        cout << err_msg; cin.clear(); cin.ignore(INT_MAX, '\n');
    }
}

int main() 
{
    cout << "COSC 1337 Exam 2 Billfold" << endl;

    // Step 2 (5 points)
    // Billfold empty;
    Billfold billfold(4, 3, 2, 1);

    // Step 4 (5 points)
    // cout << "Total Value: $" << billfold.total_value();  // did not use setprecision because
                                                            // it will always be a whole number

    // Step 7 (5 points)
    billfold.set(8, 7, 6, 5);
    // cout << '\n' << billfold.show();

    // Step 10 (10 points) 
    enum Options{Dollar='d', Five='f', Ten='t', Twenty='w', Quit='q'};
    while (true)
    {
        // display prompt
        cout << "$" << billfold.total_value() << ' ' << billfold.show() // did not use setprecision
            << " Modify d)ollar f)ive t)en t(w)enty q)uit: ";           // because value will always be whole
        char input = get_input<char>("", "Invalid");    // get input (will auto clear cin buffer and flags)
        switch (input) 
        {
        // self documenting case switch using enum
        case Options::Dollar:
        {
            // if the modify is invalid, tell the user and start again
            if (!billfold.modify(0, 0, 0, get_input<int>("  +/- dollar: ", "Invalid\n")))
            {
                cout << "Not a valid input (you cannot have negative bills!)\n";
                continue;
            }
            break;
        }
        case Options::Five: 
        {
            if (!billfold.modify(0, 0, get_input<int>("  +/- five: ", "Invalid\n")))
            {
                cout << "\nNot a valid input (you cannot have negative bills!";
                continue;
            }
            break;
        }
        case Options::Ten:
        {
            if (!billfold.modify(0, get_input<int>("  +/- ten: ", "Invalid\n")))
            {
                cout << "\nNot a valid input (you cannot have negative bills!";
                continue;
            }
            break;
        }
        case Options::Twenty:
        {
            if (!billfold.modify(get_input<int>("  +/- twenty: ", "Invalid\n")))
            {
                cout << "\nNot a valid input (you cannot have negative bills!";
                continue;
            }
            break;
        }
        case Options::Quit:
        {
            billfoldVectorDisplay();    // call Step 11
            cout << endl << "Goodbye!" << endl; // this should appear as the last line of your output
            return EXIT_SUCCESS; // Use return 0 if EXIT_SUCCESS is undefined
        }
        default:
            cout << "Invalid option, try again!\n";
        }
    }
}
 /*
COSC 1337 Exam 2 Billfold
$265 ($20=8 $10=7 $5=6 $1=5) Modify d)ollar f)ive t)en t(w)enty q)uit: asdfghjkl
Invalid option, try again!
$265 ($20=8 $10=7 $5=6 $1=5) Modify d)ollar f)ive t)en t(w)enty q)uit: d
  +/- dollar: gfd
Invalid
  +/- dollar: 10
$275 ($20=8 $10=7 $5=6 $1=15) Modify d)ollar f)ive t)en t(w)enty q)uit: d
  +/- dollar: -16
Not a valid input (you cannot have negative bills!)
$275 ($20=8 $10=7 $5=6 $1=15) Modify d)ollar f)ive t)en t(w)enty q)uit: d
  +/- dollar: -15
$260 ($20=8 $10=7 $5=6 $1=0) Modify d)ollar f)ive t)en t(w)enty q)uit: f
  +/- five: 5
$285 ($20=8 $10=7 $5=11 $1=0) Modify d)ollar f)ive t)en t(w)enty q)uit: t
  +/- ten: 1
$295 ($20=8 $10=8 $5=11 $1=0) Modify d)ollar f)ive t)en t(w)enty q)uit: w
  +/- twenty: -2
$255 ($20=6 $10=8 $5=11 $1=0) Modify d)ollar f)ive t)en t(w)enty q)uit: q

Billfold 1: $36
Billfold 2: $118
Billfold 3: $360
Total: $514
Goodbye!

C:\Users\rshar\Desktop\Projects\School\COSC-1337\Release\DL3_X2_Riccio.exe (process 12404) exited with code 0.
Press any key to close this window . . .

 */
