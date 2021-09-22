// Author: Ryan Riccio
// Assignment Number: Lab 10: Pointers
// File Name: DL3_L10_Riccio.cpp
// Course/Section: COSC 1337 Section DL3
// Due Date: December 1st, 2020
// Instructor: Professor Paul Thayer

#include <iostream>
#include <iomanip>
using namespace std;

struct Person 
{
    string name;     // name of the person
    Person* next;    // pointer to the next person in the list
    Person(string initName, Person* nextPerson = nullptr)
    {
        name = initName;
        next = nextPerson;
    }
};

// given addr macros
#define show_addr_value(var, width) \
  cout<<"address of " << setw(width)<<left<<#var<<" is: &"<<&var<<"  "     \
      <<"contents of "<<setw(width)<<left<<#var<<" is: "<<var<<endl;

#define show_addr(var, width) \
  cout<<"address of " <<setw(width)<<left<<#var<<" is: &"<<&var<<endl;

int main() {
    cout << "Output from Lab10 memory diagram on pointers:\n\n";

    // here everything is assigned according to memory map
    float price = 0;
    float* p_price = &price;
    *p_price = 19.95;

    double PI = 0;
    double* p_PI = &PI;
    double PI_div_2{ 0 };
    *p_PI = 3.141592;
    PI_div_2 = *p_PI / 2;

    int maxSize = 0;
    int* p_size = &maxSize;
    *p_size = 5028;
    int* p_amount = new int{ 1234 };

    int* pArray = new int[3]{ 11, 22, 33 };

    Person* emptyList = nullptr;
    
    Person wizard("Gandalf");

    // linked list
    Person* personList = new Person("Harry");
    personList->next = new Person("Sally");

    // this next section of code goes through and prints the values
    // and addresses of all of the pointers, and the data they point to
    show_addr_value(price, 8);
    show_addr_value(p_price, 8);
    cout << "The contents of *p_price is: " << *p_price << "\n\n";

    show_addr_value(PI, 8);
    show_addr_value(PI_div_2, 8);
    show_addr_value(p_PI, 8);
    cout << "The contents of *p_PI is:    " << *p_PI << "\n\n";

    show_addr_value(maxSize, 8);
    show_addr_value(p_size, 8);
    cout << "The contents of *p_size is: " << *p_size << "\n\n";

    show_addr_value(p_amount, 8);
    cout << "The contents of *p_amount is: " << (dec) << *p_amount << endl;
    delete p_amount;    // delete memory in heap
    cout << "After delete, the contents of p_amount is: " << p_amount << endl;
    p_amount = nullptr;
    cout << "After reset to nullptr, the contents of p_amount is: " << p_amount << "\n\n";

    show_addr_value(pArray, 8);
    show_addr_value(pArray[0], 8);
    show_addr_value(pArray[1], 8);
    show_addr_value(pArray[2], 8);
    delete[] pArray;    // delete memory in heap
    cout << "After delete [], the contents of pArray is: " << pArray << endl;
    pArray = nullptr;
    cout << "After reset to nullptr, the contents of pArray is: " << pArray << "\n\n";

    show_addr_value(emptyList, 8);
    cout << '\n';

    cout << "stack allocation (uses: Person wizard):\n";
    show_addr(wizard, 8);
    show_addr_value(wizard.name, 8);    // can use dot op because not pointer
    show_addr_value(wizard.next, 8);

    cout << "\nheap allocation (uses: personList, Person(\"Harry\"), Person(\"Sally\"):\n";
    show_addr_value(personList, 8);
    show_addr_value(personList->name, 8);   // display values from heap
    show_addr_value(personList->next, 8);
    cout << "  <follow link to next Person on personList>\n";
    show_addr_value(personList->next->name, 8); // show linked list cont.
    show_addr_value(personList->next->next, 8);
    delete personList->next;    // stop mem leak, remove from heap
    delete personList;

    return EXIT_SUCCESS;
}

/*
Output from Lab10 memory diagram on pointers:

address of price    is: &0072FC8C  contents of price    is: 19.95
address of p_price  is: &0072FC88  contents of p_price  is: 0072FC8C
The contents of *p_price is: 19.95

address of PI       is: &0072FC70  contents of PI       is: 3.14159
address of PI_div_2 is: &0072FC4C  contents of PI_div_2 is: 1.5708
address of p_PI     is: &0072FC84  contents of p_PI     is: 0072FC70
The contents of *p_PI is:    3.14159

address of maxSize  is: &0072FC80  contents of maxSize  is: 5028
address of p_size   is: &0072FC7C  contents of p_size   is: 0072FC80
The contents of *p_size is: 5028

address of p_amount is: &0072FC90  contents of p_amount is: 00A4CCA8
The contents of *p_amount is: 1234
After delete, the contents of p_amount is: 00008123
After reset to nullptr, the contents of p_amount is: 00000000

address of pArray   is: &0072FC94  contents of pArray   is: 00A4B968
address of pArray[0] is: &00A4B968  contents of pArray[0] is: 11
address of pArray[1] is: &00A4B96C  contents of pArray[1] is: 22
address of pArray[2] is: &00A4B970  contents of pArray[2] is: 33
After delete [], the contents of pArray is: 00008123
After reset to nullptr, the contents of pArray is: 00000000

address of emptyList is: &0072FC78  contents of emptyList is: 00000000

stack allocation (uses: Person wizard):
address of wizard   is: &0072FC54
address of wizard.name is: &0072FC54  contents of wizard.name is: Gandalf
address of wizard.next is: &0072FC6C  contents of wizard.next is: 00000000

heap allocation (uses: personList, Person("Harry"), Person("Sally"):
address of personList is: &0072FC98  contents of personList is: 00A48600
address of personList->name is: &00A48600  contents of personList->name is: Harry
address of personList->next is: &00A48618  contents of personList->next is: 00A45AA0
  <follow link to next Person on personList>
address of personList->next->name is: &00A45AA0  contents of personList->next->name is: Sally
address of personList->next->next is: &00A45AB8  contents of personList->next->next is: 00000000

C:\Users\rshar\Desktop\Projects\School\COSC-1337\Release\DL3_L10_Riccio.exe (process 2556) exited with code 0.
Press any key to close this window . . .
*/