// Author: Ryan Riccio
// Assignment Number: Lab 4: Speed of Sound through a Medium
// File Name: DL3_L4_Riccio.cpp
// Course/Section: COSC 1337 Section DL3
// Due Date: September 29th, 2020
// Instructor: Professor Paul Thayer
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


// structure with medium and speed
struct MediumInfo 
{
	string name;
    int speed{};
};

// open file and parse file (store dynamically)
void ReadFile(const char* filename, vector<MediumInfo>& mediumData)
{
    // load file and handle if it does not exist
	ifstream inFile(filename);
    if (inFile) 
    {
        cout << filename << " was opened successfully.\n";

        // counts how many objects are added to vector
        int mediumCount{ 0 }; 

        // ignore first (label) line
        inFile.ignore(INT_MAX, '\n');
        while (!inFile.eof()) 
        {
            // create new MediumInfo object, store info, add to vector
            MediumInfo info;
            inFile >> info.name >> info.speed;
            // to handle extra space at end of file (if exists)
            if (info.name == "")
                break;
            mediumData.push_back(info);
            mediumCount++;
        }
        inFile.close();     // close
        cout << mediumCount << " mediums were found in the file.\n\n";
    }
    else 
        cout << "Sorry, but file: " << filename << " did not open for input.\n";
}

// make menu options using first letter (using references to existing data)
void CreatePrompt(string& prompt, const vector<MediumInfo>& mediumData)
{
    // add text to prompt
    prompt += "Choose a medium (or quit): ";
    // ranged-for creates a MediumData object per iteration of MediumData in vector
    for (const MediumInfo& info : mediumData)
    {
        // cast as string to concatenate first letter with () 
        prompt += static_cast<string>("(") + info.name[0] + ")";
        // print remaining letters
        for (size_t index = 1; index < info.name.size(); index++)
            prompt += info.name[index];
        prompt += " ";
    }
    prompt += "(Q)uit: ";
}

// get the index of an item from a selection
int GetMediumIndex(char option, const vector<MediumInfo>& mediumData)
{
    int index{ 0 };
    // if letter exists, return the index
    for (const MediumInfo& info : mediumData)
    {
        if (option == info.name[0])
            return index;
        index++;
    }
    // if it is quit, return vector.size+1
    if (option == 'Q')
        return index;
    return -1;  // if error return -1
}

// get user input
char GetMediumOption(const string& prompt)
{
    while (true)
    {
        // print prompt each time, only accept 1 character
        cout << prompt;
        string inputString{};
        cin >> inputString;
        if (inputString.size() > 1)
            cout << "\nThat is not a valid input.\n\n";
        else
            return static_cast<char>(toupper(inputString[0]));
    }
}

// get feet for calculation based off selection
string GetFeet(string name)
{
    while (true)
    {
        // validate input and store feet as string to avoid reformatting user input
        cout << "Enter the distance (feet) the sound traveled through " << name << ": ";
        string feet = "";
        cin >> feet;
        bool valid = false;
        // make sure all characters are numeric or -/.
        for (size_t index{}; index < feet.size(); index++)
        {
            if (isdigit(feet[index]))
                valid = true;
            else if (feet[index] == '.' || feet[index] == '-')
                valid = true;
            else
            {
                valid = false;
                cout << "\nThat is not a valid distance in feet.\n\n";
                break;
            }
        }
        if (valid)
        {
            // when it is found to be a valid number, convert to double and compare
            if (stod(feet) < 0.0)
            {
                cout << "\nYou cannot have a negative distance\n\n";
                continue;
            }
            return feet;    // return string, not double
        }
    }
}

// perform calculation (double not less than 0)
// display solution (4 point precision) without reformatting user input
void CalculateTime(string feet, MediumInfo& mediumData)
{
    // feet has already been validated, so convert to double
    double feet_double = stod(feet);

    // perform calculation and display results
    double time = feet_double / static_cast<double>(mediumData.speed);
    cout << fixed << setprecision(4) << "\nIt takes " << time << " seconds "
        << "for sound to travel " << feet << " feet through " << mediumData.name << ".\n\n";
}

int main()
{
    // vector of type MediumInfo
    vector<MediumInfo> mediums;

    // program initialization (read from file)
    ReadFile("DL3_L4_Riccio_In.txt", mediums);
    cout << "This program calculates the time (in seconds) it takes sound to travel"
        "\na specific distance through a specific medium.\n\n";

    // create prompt from file
    string prompt;
    CreatePrompt(prompt, mediums);
    while (true)
    {
        // get option, index of option in vector, and validate
        char input = GetMediumOption(prompt);
        int mediumIndex = GetMediumIndex(input, mediums);
        if (mediumIndex == mediums.size())
            break;
        else if (mediumIndex == -1)
        {
            cout << "\nThat is not one of the options.\n\n";
            continue;
        }
        // get feet and finish calculation
        string feet = GetFeet(mediums[mediumIndex].name);
        CalculateTime(feet, mediums[mediumIndex]);
    }
    // say goodbye!
    cout << "\n\nGoodbye! Thanks for using the program!\n";
    return EXIT_SUCCESS;
}
/*
DL3_L4_Riccio_In.txt was opened successfully.
6 mediums were found in the file.

This program calculates the time(in seconds) it takes sound to travel
a specific distance through a specific medium.

Choose a medium(or quit): (A)ir(W)ater(S)teel(C)opper(N)ylon(I)ron(Q)uit: sdfgsadfasdfa

That is not a valid input.

Choose a medium(or quit): (A)ir(W)ater(S)teel(C)opper(N)ylon(I)ron(Q)uit: v

That is not one of the options.

Choose a medium(or quit): (A)ir(W)ater(S)teel(C)opper(N)ylon(I)ron(Q)uit: a
Enter the distance(feet) the sound traveled through Air: h145b43j

That is not a valid distance in feet.

Enter the distance(feet) the sound traveled through Air: -1234.1234

You cannot have a negative distance

Enter the distance(feet) the sound traveled through Air: 5280

It takes 4.8000 seconds for sound to travel 5280 feet through Air.

Choose a medium(or quit): (A)ir(W)ater(S)teel(C)opper(N)ylon(I)ron(Q)uit: W
Enter the distance(feet) the sound traveled through Water: 15000

It takes 3.0612 seconds for sound to travel 15000 feet through Water.

Choose a medium(or quit): (A)ir(W)ater(S)teel(C)opper(N)ylon(I)ron(Q)uit: s
Enter the distance(feet) the sound traveled through Steel: 50000

It takes 3.0488 seconds for sound to travel 50000 feet through Steel.

Choose a medium(or quit): (A)ir(W)ater(S)teel(C)opper(N)ylon(I)ron(Q)uit: c
Enter the distance(feet) the sound traveled through Copper: 5231.123

It takes 0.6975 seconds for sound to travel 5231.123 feet through Copper.

Choose a medium(or quit): (A)ir(W)ater(S)teel(C)opper(N)ylon(I)ron(Q)uit: q


Goodbye! Thanks for using the program!

C : \Users\rshar\Desktop\Projects\School\COSC - 1337\Release\DL3_L4_Riccio.exe(process 13984) exited with code 0.
Press any key to close this window . . .
*/