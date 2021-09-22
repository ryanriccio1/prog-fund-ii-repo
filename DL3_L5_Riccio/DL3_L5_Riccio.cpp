// Author: Ryan Riccio
// Assignment Number: Lab 5: Population Growth Chart
// File Name: DL3_L5_Riccio.cpp
// Course/Section: COSC 1337 Section DL3
// Due Date: October 1st, 2020
// Instructor: Professor Paul Thayer
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

// structure to store pop data
struct PopulationData
{
    int populuation{};
    int year{};
};

// function to read file, returns boolean if successful
bool ReadFile(const char* filename, vector<PopulationData>& populationVector)
{
    // read file and if it can be read
    ifstream inFile(filename);
    if (inFile)
    {
        cout << filename << " was opened successfully.\n";
        int currentYear{ 1900 };
        int popCount{ 0 };
        while (!inFile.eof())
        {
            // get pop from file and store to vector
            PopulationData populationData;
            inFile >> populationData.populuation;
            if (populationData.populuation == 0)
                break;
            populationData.year = currentYear;
            populationVector.push_back(populationData);
            currentYear += 20;
            popCount++;
        }
        inFile.close();     // close
        cout << popCount << " population counts were found in the file.\n\n";
        return true;
    }
    else
    {
        // failure
        cout << "Sorry, but file: " << filename << " did not open for input.\n";
        return false;
    }
        
}

// function to print graph from vector of pop info
void PrintGraph(vector<PopulationData>& populationVector)
{
    cout << string(7, ' ') << "HUNTINGTON BEACH POPULATION GROWTH\n^\n";
    int maxPopulation{ 0 };
    // loop through vector and find highest population
    for (PopulationData populationData : populationVector)
    {
        if (populationData.populuation > maxPopulation)
            maxPopulation = populationData.populuation;
    }
    // decrementing loop from max to 1000 to print bar graph
    const char* labelBackwards = "NOITALUPOP";
    for (int currentPopulation{ maxPopulation }; currentPopulation > 0; currentPopulation -= 1000)
    {
        // find number of digits in current y label
        int numDigits{ static_cast<int>(log10(currentPopulation)) + 1};
        int populationDigitTester{ currentPopulation };
        // print leading spaces and y label based off numDigits
        if (currentPopulation <= 10000)
        {
            cout << labelBackwards[currentPopulation / 1000 - 1];
            for (int spaceCount{ 6 - numDigits }; spaceCount > 0; spaceCount--)
                cout << ' ';
        }
        else
        {
            for (int spaceCount{ 6 - numDigits }; spaceCount > 0; spaceCount--)
                cout << "\xBA ";
        }
        cout << currentPopulation;
        // print bars one row at a time
        for (PopulationData populationData : populationVector)
        {
            // if the total population is greater than current, print bar
            if (populationData.populuation >= currentPopulation)
                cout << "  " << string(2, char(178)) << "  ";
            else
                cout << string(6, ' ');
        }
        cout << '\n';
    }
    // print years
    cout << "\xBA      ";
    for (PopulationData populationData : populationVector)
        cout << " " << populationData.year << " ";
    // print x label
    cout << "\nv" << string(5, ' ') << "<\xCD\xCDYEAR";
    for (unsigned int counter{ 1 }; counter < populationVector.size(); counter++)
        cout << string(6, char(205));
    cout << ">";
}

int main()
{
    // vector to dynamically store pop data
    vector<PopulationData> populationVector;
    const char* filename = "people.txt";
    // read file and exit if read fails
    if (!ReadFile(filename, populationVector))
    {
        cout << "\n\nGoodbye!";
        return EXIT_FAILURE;
    }
    // print graph and leave
    PrintGraph(populationVector);
    cout << "\n\nGoodbye! Thanks for using the program!";
    return EXIT_SUCCESS;
}
/*
people.txt was opened successfully.
9 population counts were found in the file.

       HUNTINGTON BEACH POPULATION GROWTH
^
║ 24000                                                  ▓▓
║ 23000                                                  ▓▓
║ 22000                                                  ▓▓
║ 21000                                                  ▓▓
║ 20000                                            ▓▓    ▓▓
║ 19000                                            ▓▓    ▓▓
║ 18000                                ▓▓          ▓▓    ▓▓
║ 17000                                ▓▓          ▓▓    ▓▓
║ 16000                                ▓▓    ▓▓    ▓▓    ▓▓
║ 15000                                ▓▓    ▓▓    ▓▓    ▓▓
║ 14000                          ▓▓    ▓▓    ▓▓    ▓▓    ▓▓
║ 13000                          ▓▓    ▓▓    ▓▓    ▓▓    ▓▓
║ 12000                          ▓▓    ▓▓    ▓▓    ▓▓    ▓▓
║ 11000                          ▓▓    ▓▓    ▓▓    ▓▓    ▓▓
P 10000                          ▓▓    ▓▓    ▓▓    ▓▓    ▓▓
O  9000                    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓
P  8000                    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓
U  7000                    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓
L  6000                    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓
A  5000              ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓
T  4000        ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓
I  3000        ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓
O  2000  ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓
N  1000  ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓
║       1900  1920  1940  1960  1980  2000  2020  2040  2060
v     <══YEAR════════════════════════════════════════════════>

Goodbye! Thanks for using the program!
C:\Users\rshar\Desktop\Projects\School\COSC-1337\Release\DL3_L5_Riccio.exe (process 12908) exited with code 0.
Press any key to close this window . . .

*/