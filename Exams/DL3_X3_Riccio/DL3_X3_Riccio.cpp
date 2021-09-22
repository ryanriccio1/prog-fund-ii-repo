/*
  COSC 1337 Exam 3 Lab portion
  Name: Ryan Riccio
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
using namespace std;

enum form_t { Solid = 'S', Liquid = 'L', Gas = 'G' };
enum temp_t { Frozen = 'F', Cold = 'C', Room = 'R', Hot = 'H' };

struct Food {
    string name;
    int calories;
    double price;
    form_t form;
    temp_t temp;
};

class Drink
{
private:
    string name = "";
    int calories{ 0 };
public:
    static const form_t type = Liquid;
    Drink(string name="water", int calories=0)
    {
        // if invalid, reset to default
        if (name.length() < 1 || calories < 0)
        {
            this->name = "water";
            this->calories = 0;
        }
        else
        {   // if valid, assign
            this->name = name;
            this->calories = calories;
        }
    }
    void getDrink()
    {   // display data
        cout << setw(8) << name << ' ' << setw(5)  << calories << '\n';
    }
};


void step1() {
    vector<Food> foods{
      {"corn",    8,   .18, Solid,  Room},
      {"coke",  240,   .57, Liquid, Cold},
      {"oats",   10,   .12, Solid,  Room},
      {"steak", 310, 12.34, Solid,  Frozen},
      {"milk",   80,  1.21, Liquid, Cold},
      {"soup",   95,  2.34, Liquid, Hot}
    };

    cout << "Step 1:\n";
    cout << "Contents of vector foods, already loaded:\n";
    // use const size because not using vector
    // and vector size is const
    // could use Drinks* drinks = new Drinks[food.size()]
    // if vector size was variable
    const int size = 6;
    Drink drinks[size];
    unsigned int drinkIndex{ 0 };
    for (auto& food : foods) {
        cout << setw(8) << food.name
            << "  $" << setw(5) << right << setprecision(2) << fixed << food.price
            << setw(6) << right << food.calories
            << setw(2) << (char)food.form
            << setw(2) << (char)food.temp << endl;
        // fill drinks[]
        if (food.form == Liquid && food.temp == Cold)
            drinks[drinkIndex] = Drink(food.name, food.calories);
        drinkIndex++;
    }
    cout << endl;
    cout << "Drinks in vending machine:\n";
   // print drinks
    for (Drink drink : drinks)
    {
        drink.getDrink();
    }

}

void step2() {
    cout << "\nStep 2:\n";
    // dynamically allocate with smart pointer, display
    unique_ptr<Drink> drink(new Drink("pepsi", 150));
    cout << "pepsi is at address: 0x" << drink << '\n';
    drink->getDrink();
    // ptr will be deleted here when exiting scope
}


class Fraction {
private:
    int top = 0; // numerator
    int bot = 1; // denominator
public:
    Fraction(int top = 0, int bot = 1) {
        if (bot != 0) { // guard against division by 0
            this->top = top;
            this->bot = bot;
        }
    }
    double get() const { // converts the "ratio" or "Fraction" into a double
        return top / static_cast<double>(bot);
    }
    // self explanatory overloaded operators
    Fraction operator++()
    {
        top++;
        return *this;
    }
    Fraction operator--()
    {
        top--;
        return *this;
    }
    Fraction operator*(Fraction& multiplicand)
    {
        this->top *= multiplicand.top;
        this->bot *= multiplicand.bot;
        return *this;
    }
};

void step3() {
    cout << "\nStep 3:\n";
    Fraction a=4; ++a; ++a; cout<<"a="<<a.get()<<endl; // test code, expect: 6, uncomment when ready
    Fraction b=5; --b; --b; cout<<"b="<<b.get()<<endl; // test code, expect: 3, uncomment when ready
    Fraction c=6, d=7, e=c*d;                          // test code, uncomment when ready
    cout<<"e="<<e.get()<<endl<<endl;                   // test code, expect: 42, uncomment when ready
};

// The code below is for step 4, recursion
void recurse(int times_to_call) { // a general recursive function: 5 locations to do work...
    cout << "recurse head... " << "(" << times_to_call << ") " << endl; // ALWAYS
    if (times_to_call > 1) { // decision to recursive call
        cout << "recurse before call... " << "(" << times_to_call << ") " << endl;
        recurse(times_to_call - 1); // work (problem simplification) can be done inside the parameter list!
        cout << "recurse after call... " << "(" << times_to_call << ") " << endl;
    }
    else {
        cout << "recurse else option... " << "(" << times_to_call << ") " << endl;
    }
    cout << "recurse ...tail " << "(" << times_to_call << ") " << endl; // ALWAYS
}

// Below are working iterative versions of line, left_arrow, right_arrrow, double_arrow
void line_iterative(int n) { // Provided, do not change
    for (int i = 0; i < n; ++i)
        cout << "-";
}

// For the line drawing functions, argument n is passed in; if:
//   n < 0,  output nothing
//   n == 0, output arrows only, if any
//   n > 0,  output arrows and n dashes
// See output from provided iterative versions, recursive versions should match

void left_arrow_iterative(int n) { // Provided, do not change
    if (n >= 0)
        cout << "<";
    for (int i = 0; i < n; ++i)
        cout << "=";
}

void right_arrow_iterative(int n) { // Provided, do not change
    for (int i = 0; i < n; ++i)
        cout << "~";
    if (n >= 0)
        cout << ">";
}

void double_arrow_iterative(int n) { // Provided, do not change
    if (n >= 0)
        cout << "<";
    for (int i = 0; i < n; ++i)
        cout << "+";
    if (n >= 0)
        cout << ">";
}

// Put your new recursive versions for step 4 here...
void line_recursive(int n) {
    if (n < 1)  // count down and print - for each time
        return;
    line_recursive(--n);
    cout << "-";
}

void left_arrow_recursive(int n) {
    if (n == 0) // if 0, print end cap
    {
        cout << "<";
        return;
    }
    else if (n < 0) // if negative, do not print
        return;
    left_arrow_recursive(--n);
    cout << "=";
}

void right_arrow_recursive(int n) {
    if (n == 0) // print end cap if 0
    {
        cout << ">";
        return;
    }
    else if (n < 0) // if < 0 don't print anything
        return;
    else
        cout << "~";    // if not end cap and not finished, print ~
    right_arrow_recursive(--n);
}

void double_arrow_recursive(int n, int j = 0) {
    if (n < 0)  // do not print if < 0
        return;
    else if (n >= 0 && j == 0)  // if first iteration and n is not negative
        cout << "<";
    if (n == 0) // when we reach the end of recursive loop
    {
        cout << ">";
        return;
    }
    else
        cout << '+';    // if not an end cap or return, print a +
    double_arrow_recursive(--n, ++j);
}

void step4() {
    // Below is testing code for step 4; it will be called from main. No changes needed.
    // recurse(3); // call to recurse example for experimentation, if desired
    cout << "Test provided iterative versions of line, left_arrow, right_arrow, double_arrow:\n";
    // for (int n=1; n<=5; ++n) { // test provided iterative functions
    for (int n = -5; n <= 5; ++n) { // test provided iterative functions
        cout << "n=" << setw(2) << n << ":";
        line_iterative(n); cout << ' ';
        left_arrow_iterative(n); cout << ' ';
        right_arrow_iterative(n); cout << ' ';
        double_arrow_iterative(n); cout << endl;
    }
    cout << "\nTest student's new recursive versions of line, left_arrow, right_arrow, double_arrow:\n";
    for (int n = -5; n <= 5; ++n) { // test student's new recursive functions
        cout << "n=" << setw(2) << n << ":";
        line_recursive(n); cout << ' ';
        left_arrow_recursive(n); cout << ' ';
        right_arrow_recursive(n); cout << ' ';
        double_arrow_recursive(n); cout << ' ' << endl; // EXTRA CREDIT
    }
};

void step6() { // EXTRA CREDIT
    cout << "Step 6: (optional extra credit)\n";
    int outOfBoundArray[4] = { 0, 1, 2, 3 };
    int* p = outOfBoundArray + 5;  // #1 indexing out of bounds
    
    p = nullptr;
    int a = *p; // #2 dereferencing nullptr
    
    a = 0;
    int b = 0;
    bool c = &a < &b; // #3 comparing pointers
    
    a = 32;
    b = 1 << a; // #4 overflow bits into new byte
    
    while (true)
        int* p = new int{ 10 }; // #5 fill heap
};

int main() {
    // No new code goes in main. Put all new code where designated in the steps above.
    cout << "Start...\n";
    step1();
    step2();
    step3();
    step4();
    step6();  // EXTRA CREDIT: 5 ways to possibly crash a C++ program
    cout << "\n...end.\n";
    return 0;
}

/*
Start...
Step 1:
Contents of vector foods, already loaded:
    corn  $ 0.18     8 S R
    coke  $ 0.57   240 L C
    oats  $ 0.12    10 S R
   steak  $12.34   310 S F
    milk  $ 1.21    80 L C
    soup  $ 2.34    95 L H

Drinks in vending machine:
   water     0
    coke   240
   water     0
   water     0
    milk    80
   water     0

Step 2:
pepsi is at address: 0x00C425E0
   pepsi   150

Step 3:
a=6.00
b=3.00
e=42.00

Test provided iterative versions of line, left_arrow, right_arrow, double_arrow:
n=-5:
n=-4:
n=-3:
n=-2:
n=-1:
n= 0: < > <>
n= 1:- <= ~> <+>
n= 2:-- <== ~~> <++>
n= 3:--- <=== ~~~> <+++>
n= 4:---- <==== ~~~~> <++++>
n= 5:----- <===== ~~~~~> <+++++>

Test student's new recursive versions of line, left_arrow, right_arrow, double_arrow:
n=-5:
n=-4:
n=-3:
n=-2:
n=-1:
n= 0: < > <>
n= 1:- <= ~> <+>
n= 2:-- <== ~~> <++>
n= 3:--- <=== ~~~> <+++>
n= 4:---- <==== ~~~~> <++++>
n= 5:----- <===== ~~~~~> <+++++>

...end.

C:\Users\rshar\Desktop\Projects\School\COSC-1337\Debug\DL3_X3_Riccio.exe (process 10788) exited with code 0.
Press any key to close this window . . .

*/