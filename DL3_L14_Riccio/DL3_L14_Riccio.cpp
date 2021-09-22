// Author:               Ryan Riccio
// Assignment Number:    Lab 14
// File Name:            DL3_L14_Riccio.cpp
// Course/Section:       COSC 1337 Section DL3
// Due Date:             December 10th, 2020
// Instructor:           Thayer
#include <iostream>
#include <iomanip>
using namespace std;

// given
void show_1_to_n_loop(int n)
{
    for (int i = 1; i <= n; ++i) 
        cout << i << " ";
}

void show_1_to_n_recurse(int n) 
{
    // keep increasing 1 until it is n
    if (n <= 0)
        return;
    show_1_to_n_recurse(n - 1);
    cout << n << " ";
}

// given
void show_n_to_1_loop(int n) { // looping
    for (int i = n; i >= 1; --i) cout << i << " ";
}

void show_n_to_1_recurse(int n) 
{
    // keep decreasing n until it is 1
    cout << n << " ";
    if (n == 1)
        return;
    show_n_to_1_recurse(n - 1);
}

// given
string reverse_loop(string forward) { // looping
    string backwards;
    int size = forward.size();
    for (int i = 0; i < size; ++i) {
        backwards += forward[size - 1 - i];
    }
    return backwards;
}

string reverse_recurse(string forward) 
{ 
    if (forward.length() == 0)
        return "";
    // store last char, reverse string, add last char to start of reversed
    // will keep adding last char to front until no more chars in forward
    char lastChar = forward[forward.length() - 1];
    string reversed = reverse_recurse(forward.substr(0, forward.length() - 1));
    return lastChar + reversed;
}

// given
int add2_fx(int a, int b) { // functional (for illustration only)
    return a + b;
}

// given
int add2_loop(int a, int b) { // looping
    int sum = a;
    if (b > 0)
        for (int i = 0; i < b; ++i) ++sum;
    else // b<=0
        for (int i = b; i < 0; ++i) --sum;
    return sum;
}

int add2_recurse(int a, int b) 
{
    // i have used this before in 6502 (in cases where ADC isn't the best option)
    // because it is very efficient and uses very few instructions
    // here's the explanation:                                  // ex. a = 9, b = 10
   
    // a carry int is created with a bitwise AND                // 1001(9) & 1010(10) = 1000(8)
    int carry = a & b;
    
    // a is now assigned to the bitwise XOR result of a and b   // 1001(9) ^ 1010(10) = 0011(3)
    a ^= b;

    // b is now assigned to the carry bit shifted 1             // 1000(8) << 1 = 10000(16)
    b = carry << 1;

    // so if we used the add op, we could simply do 16+3=19
    // however, we can recursively repeat these steps until the carry is 0, at which point 
    // b = 0 and a = answer
    if (b != 0)
        // carry = 16 & 3 = 0
        // a = 16 ^ 3 = 19
        // b = carry << 1 = 0
        add2_recurse(a, b); // a = 16, b = 3
    else
        return a;
    // in this example, we only have to loop twice to get the answer 
}

// given
int mult2_fx(int a, int b) { // functional (for illustration only)
    return a * b;
}

// given
int mult2_loop(int a, int b) { // looping
    int product = 0;
    if (b > 0)
        for (int i = 0; i < b; ++i) product += a;
    else // b<=0
        for (int i = b; i < 0; ++i) product -= a;
    return product;
}

int mult2_recurse(int a, int b) 
{ 
    // if either number is 0, answer will be 0
    if (a == 0 || b == 0)
        return 0;

    // if b is negative
    else if (b < 0)
        return -a + mult2_recurse(a, b + 1);

    else
        return a + mult2_recurse(a, b - 1);
}

// given
int search_loop(int array[], int size, int target) { // looping
    for (int i = 0; i < size; ++i)
        if (array[i] == target) { return i; }
    return -1;
}

int search_recurse(const int array[], int first, int last, int target) 
{
    // bubble search (recursive) almost identical to book
    // and my example in lab 9
    // very self explanatory, will keep searching until 
    // index is found, otherwise, return -1
    int middle;
    if (first > last)
        return -1;
    middle = (first + last) / 2;
    if (array[middle] == target)
        return middle;
    if (array[middle] < target)
        return search_recurse(array, middle + 1, last, target);
    else
        return search_recurse(array, first, middle - 1, target);
}

// given in lab 9 (slightly altered)
void showArray(int array[], int size, const string& msg = "") { // displays every element in array
    cout << msg;
    for (int i{}; i < size; ++i)
        cout << setw(3) << array[i]; // assumes small numbers
}

// written for lab 9
void insertionSort(int array[], int size, bool verbose = false)
{
    int index, key, leftItemIndex;
    for (index = 1; index < size; index++)
    {
        key = array[index];
        leftItemIndex = index - 1;

        // if item to the right of an item is smaller, move it down
        // until it is bigger than the item to the left
        while (leftItemIndex >= 0 && array[leftItemIndex] > key)
        {
            array[leftItemIndex + 1] = array[leftItemIndex];
            leftItemIndex--;
        }
        if (verbose)
        {
            cout << "  insertion:";
            showArray(array, size);
        }
        array[leftItemIndex + 1] = key;
    }
}

void insertionSortRecursive(int arr[], int size)
{
    if (size <= 1)
        return;
    insertionSortRecursive(arr, size - 1);


    int last = arr[size - 1];
    int shiftLocation = size - 2;

    while (shiftLocation >= 0 && arr[shiftLocation] > last)
    {
        arr[shiftLocation + 1] = arr[shiftLocation];
        shiftLocation--;
    }
    arr[shiftLocation + 1] = last;
}

// given
enum control_t { functional, looping, recursive };

// given
void show_test(int n, string s, control_t control) {
    // utility function to format test output
    // n: test number; s: "description"; control: looping or recursive
    static const string fx = "functional", sl = "looping", sr = "recursive";
    int max_len = max(fx.size(), max(sl.size(), sr.size()));
    string msg;
    switch (control) {
    case functional: msg = fx;     break;
    case looping:    msg = sl;     break;
    case recursive:  msg = sr;     break;
    default:         msg = "??";   break;
    }
    char iorr = msg[0];
    msg = " (" + msg + "): ";
    cout << "\n" << n << iorr << ") " << s << setw(max_len + 5) << left << msg;
}

// given
void infinite_recursion() {
    // try at your own risk! Error message can be interesting.
    infinite_recursion();
}

// given
int main() {
    cout << "start...\n";

    show_test(1, "show_1_to_n", looping);    show_1_to_n_loop(7);
    show_test(1, "show_1_to_n", recursive);  show_1_to_n_recurse(7);
    cout << endl;

    show_test(2, "show_n_to_1", looping);    show_n_to_1_loop(10);
    show_test(2, "show_n_to_1", recursive);  show_n_to_1_recurse(10);
    cout << endl;

    show_test(3, "reverse", looping);    cout << reverse_loop("stressed");
    show_test(3, "reverse", recursive);  cout << reverse_recurse("stressed");
    cout << endl;

    show_test(4, "add2", functional);
    cout << add2_fx(4, 5); cout << " ";  // correct:   9
    cout << add2_fx(-5, 15); cout << " ";  // correct:  10
    cout << add2_fx(20, -9); cout << " ";  // correct:  11
    cout << add2_fx(-7, -5); cout << " ";  // correct: -12
    show_test(4, "add2", looping);
    cout << add2_loop(4, 5); cout << " ";  // correct:   9
    cout << add2_loop(-5, 15); cout << " ";  // correct:  10
    cout << add2_loop(20, -9); cout << " ";  // correct:  11
    cout << add2_loop(-7, -5); cout << " ";  // correct: -12
    show_test(4, "add2", recursive);
    cout << add2_recurse(4, 5); cout << " ";  // correct:   9
    cout << add2_recurse(-5, 15); cout << " ";  // correct:  10
    cout << add2_recurse(20, -9); cout << " ";  // correct:  11
    cout << add2_recurse(-7, -5); cout << " ";  // correct: -12
    cout << endl;

    show_test(5, "mult2", functional);
    cout << mult2_fx(2, 5); cout << " ";  // correct:  10
    cout << mult2_fx(-4, 5); cout << " ";  // correct: -20
    cout << mult2_fx(3, -10); cout << " ";  // correct: -30
    cout << mult2_fx(10, 4); cout << " ";  // correct:  40
    show_test(5, "mult2", looping);
    cout << mult2_loop(2, 5); cout << " ";  // correct:  10
    cout << mult2_loop(-4, 5); cout << " ";  // correct: -20
    cout << mult2_loop(3, -10); cout << " ";  // correct: -30
    cout << mult2_loop(10, 4); cout << " ";  // correct:  40
    show_test(5, "mult2", recursive);
    cout << mult2_recurse(2, 5); cout << " ";  // correct:  10
    cout << mult2_recurse(-4, 5); cout << " ";  // correct: -20
    cout << mult2_recurse(3, -10); cout << " ";  // correct: -30
    cout << mult2_recurse(10, 4); cout << " ";  // correct:  40
    cout << endl;

    int primes[]{ 2, 3, 5, 7, 11, 13, 17 }; // some prime numbers to search for
    int size_primes = sizeof(primes) / sizeof(int);

    show_test(6, "search", looping);
    cout << search_loop(primes, size_primes, 2) << ", ";
    cout << search_loop(primes, size_primes, 13) << ", ";
    cout << search_loop(primes, size_primes, 10);
    show_test(6, "search", recursive);
    cout << search_recurse(primes, 0, size_primes, 2) << ", ";
    cout << search_recurse(primes, 0, size_primes, 13) << ", ";
    cout << search_recurse(primes, 0, size_primes, 10) << endl;
    // end given section

    // added insertion sort (loop/ recursive)
    int randArr1[]{ 99, 76, 69, 11, 29, 12, 33, 12, 56 };
    int sizeRand = sizeof(randArr1) / sizeof(int);
    cout << "\n7)  original array:\t\t ";
    showArray(randArr1, sizeRand);
    show_test(7, "insertion sort", looping);
    insertionSort(randArr1, sizeRand);
    showArray(randArr1, sizeRand, "");
    
    // redef array since it was just sorted
    int randArr2[]{ 99, 76, 69, 11, 29, 12, 33, 12, 56 };
    sizeRand = sizeof(randArr2) / sizeof(int);
    show_test(7, "insertion sort", recursive);
    insertionSortRecursive(randArr2, sizeRand);
    showArray(randArr2, sizeRand, "");

    cout << "\n\n...end\n";

    return EXIT_SUCCESS;
}

/*
start...

1l) show_1_to_n (looping):    1 2 3 4 5 6 7
1r) show_1_to_n (recursive):  1 2 3 4 5 6 7

2l) show_n_to_1 (looping):    10 9 8 7 6 5 4 3 2 1
2r) show_n_to_1 (recursive):  10 9 8 7 6 5 4 3 2 1

3l) reverse (looping):    desserts
3r) reverse (recursive):  desserts

4f) add2 (functional): 9 10 11 -12
4l) add2 (looping):    9 10 11 -12
4r) add2 (recursive):  9 10 11 -12

5f) mult2 (functional): 10 -20 -30 40
5l) mult2 (looping):    10 -20 -30 40
5r) mult2 (recursive):  10 -20 -30 40

6l) search (looping):    0, 5, -1
6r) search (recursive):  0, 5, -1

7)  original array:              99 76 69 11 29 12 33 12 56
7l) insertion sort (looping):    11 12 12 29 33 56 69 76 99
7r) insertion sort (recursive):  11 12 12 29 33 56 69 76 99

...end

C:\Users\rshar\Desktop\Projects\School\COSC-1337\Debug\DL3_L14_Riccio.exe (process 10348) exited with code 0.
Press any key to close this window . . .

*/