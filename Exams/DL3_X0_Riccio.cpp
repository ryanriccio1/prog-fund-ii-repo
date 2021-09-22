/*
  Name: Ryan Riccio
  COSC 1337 Section: DL3 (change the DDHH to your course designator)
  Exam 0, Programming portion
*/

#include <iostream>
using namespace std;

/* INSTRUCTIONS:
  Ask for name.  (Use data type string) Example: "Jasper"
  Ask for quest. (Use data type string) Example: "peace"
  Display (example): "I hope Jasper can find peace soon."
  
  Ask user for two numbers. (Use numeric data type of your choice.)
  Add the numbers together.
  Mulitply the numbers together.
  Display the sum and product.

  Compile, run, test, put test output at bottom, submit.
*/


int main() {
  cout << "COSC 1337 Exam 0 Lab Portion" << endl;
  // insert your new code AFTER each comment for each step

  // step 1 (1 point) Ask for and get name.
  string name;
  cout << "What is your name: ";
  cin >> name;
  
  // step 2 (1 point) Ask for and get quest.
  string quest;
  cout << "What is your quest: ";
  cin >> quest;
  
  // step 3 (1 point) Display name and quest to the user.
  cout << "Hello " << name << ". I hope you achieve your quest of: " << quest << "\n\n";

  // step 4 (1 point) Ask for and get the 1st number.
  int operand_1{};
  cout << name << ", please enter a number: ";
  cin >> operand_1;
  
  // step 5 (1 point) Ask for and get the 2nd number.
  int operand_2{};
  cout << "Please enter another number: ";
  cin >> operand_2;
  
  // step 6 (1 point) Add the numbers together.
  // step 7 (1 point) Multiply the numbers together.
  // step 8 (1 point) Display the sum and product to the user.
  cout << "\nThe sum of those numbers is: " << operand_1 + operand_2 << endl;
  cout << "The product of those numbers is: " << operand_1 * operand_2 << endl;
  
  // step 9 (2 points) Compile, test, place test output at bottom, submit

  cout << "\nGoodbye!" << endl; // this should appear as the last line of your output
  return EXIT_SUCCESS; // Use return 0 if EXIT_SUCCESS is undefined
}

/*
COSC 1337 Exam 0 Lab Portion
What is your name: Ryan
What is your quest: peace
Hello Ryan. I hope you achieve your quest of: peace

Ryan, please enter a number: 25
Please enter another number: 25

The sum of those numbers is: 50
The product of those numbers is: 625

Goodbye!

--------------------------------
Process exited after 8.752 seconds with return value 0
Press any key to continue . . .
  
*/
