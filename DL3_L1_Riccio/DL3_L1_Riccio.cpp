// Author: Ryan Riccio
// Assignment Number: Lab 1: Menu driven option loop
// File Name: DL3_L1_Riccio.cpp
// Course/Section: COSC 1337 Section DL3
// Due Date: September 10th, 2020
// Instructor: Professor Paul Thayer

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    while (true)
    {   
        // display menu
        cout << "Options: (a)dvice (b)mi (c)heck (q)uit: ";
        char option = ' ';
        cin >> option;

        // give advice
        if (option == 'a')
        {
            cout << "Order a steak. It'll make you happy :)\n" << endl;
        }

        // calculate bmi
        else if (option == 'b')
        {
            // initlize vars and give them place in RAM
            int weight{};
            int feet{};
            int inches{};
            int height{};

            // input validation loop
            while (true)
            {
                // get weight
                cout << "What is your weight (in pounds): ";
                cin >> weight;

                // if failure flag is raised
                if (cin.fail())
                {
                    cout << "You entered an invalid number." << endl;

                    // sometimes cin still has values in the stream or buffer, this gets rid of it
                    // and clears the fail flag
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    continue;
                }
                else
                {
                    // make sure number is reasonable
                    if (weight < 1 || weight > 1000)
                    {
                        cout << "I don't think you can weigh that much." << endl;

                        // clear cin/restart loop
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        continue;
                    }
                    break;
                }
            }

            // basically the same as above, except it takes height as an input
            while (true)
            {
                // init separator char to store char type (eg. '/")
                char separator;
                cout << "How tall are you (feet inches eg. 5'11\"): ";
                cin >> feet >> separator >> inches >> separator;

                // calculate total height in inches
                height = (feet * 12) + inches;

                // input validation
                if (cin.fail())
                {
                    cout << "You entered an invalid number." << endl;

                    // clear cin/restart loop
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    continue;
                }
                else
                {
                    if (inches > 11 || inches < 0)
                    {
                        cout << "Please enter a value for inches between 0 and 11." << endl;

                        // clear cin/restart loop
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        continue;
                    }
                    if (height < 10 || height > 100)
                    {
                        cout << "I don't think you can be that tall." << endl;

                        // clear cin/restart loop
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        continue;
                    }
                    // when we have height and weight
                    break;
                }
            }
            // cast height as double for math and compute BMI
            double double_height = static_cast<double>(height);
            double bmi = (static_cast<double>(weight) / (double_height * double_height)) * 703;
            cout << fixed << setprecision(2) << "Your BMI is: " << bmi << "\n" << endl;
        }

        // calculate tip
        else if (option == 'c')
        {
            // declare and populate variables
            double food_cost;
            double tip_percent;
            while (true)
            {
                cout << "What was the cost of your food: $";
                cin >> food_cost;
                if (cin.fail())
                {
                    cout << "You entered an invalid number." << endl;

                    // clear cin/restart loop
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    continue;
                }
                else
                {
                    // clear cin/leave loop
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    break;
                }

            }

            // more validation
            while (true)
            {
                cout << "What percent tip do you want to give: ";
                cin >> tip_percent;
                if (cin.fail())
                {
                    cout << "You entered an invalid number." << endl;

                    // clear cin/restart loop
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    continue;
                }
                else
                {
                    // clear cin/leave loop
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    break;
                }

            }
            // math to calculate total bill
            const double TAX_RATE{ 0.0825 };
            double tip = (tip_percent / 100) * food_cost;   // tip does not include tax
            double tax = food_cost * TAX_RATE;              // tax does not include tip
            double total_bill = food_cost + tip + tax;

            //display check
            cout << "#########################\n";
            cout << "#### RESTAURANT BILL ####\n";
            cout << "#########################" << endl;
            cout << fixed << setprecision(2) << "# Food:\t\t$" << food_cost << "\t#\n# Tip:\t\t$" << tip 
                << "\t#\n# Tax (" << (TAX_RATE * 100) << "%):\t$" << tax << "\t#\n# TOTAL:\t$" 
                << total_bill << "\t#" << endl;
            cout << "#                       #\n";
            cout << "#                       #\n";
            cout << "#########################\n" << endl;
        }

        // quit safely
        else if (option == 'q')
        {
            cout << "Thanks for using my program! Have a nice day!" << endl;
            return EXIT_SUCCESS;
        }

        // in the case someone inputs an invalid option
        else
        {
            cout << "You did not enter a valid option.\n" << endl;
            continue;
        }
        

    }
}

/*
Options: (a)dvice (b)mi (c)heck (q)uit: a
Order a steak. It'll make you happy :)

Options: (a)dvice (b)mi (c)heck (q)uit: b
What is your weight (in pounds): hu j k njkn j
You entered an invalid number.
What is your weight (in pounds): -129
I don't think you can weigh that much.
What is your weight (in pounds): 1029
I don't think you can weigh that much.
What is your weight (in pounds): 150
How tall are you (feet inches eg. 5'11"): 9'10"
I don't think you can be that tall.
How tall are you (feet inches eg. 5'11"): 5'12"
Please enter a value for inches between 0 and 11.
How tall are you (feet inches eg. 5'11"): 6'0"
Your BMI is: 20.34

Options: (a)dvice (b)mi (c)heck (q)uit: c
What was the cost of your food: $64.93
What percent tip do you want to give: 18%
#########################
#### RESTAURANT BILL ####
#########################
# Food:         $64.93  #
# Tip:          $11.69  #
# Tax (8.25%):  $5.36   #
# TOTAL:        $81.97  #
#                       #
#                       #
#########################

Options: (a)dvice (b)mi (c)heck (q)uit: h
You did not enter a valid option.

Options: (a)dvice (b)mi (c)heck (q)uit: q
Thanks for using my program! Have a nice day!

C:\Users\rshar\Desktop\Projects\School\COSC-1337\Release\DL3_L1_Riccio.exe (process 2604) exited with code 0.
Press any key to close this window . . .
*/