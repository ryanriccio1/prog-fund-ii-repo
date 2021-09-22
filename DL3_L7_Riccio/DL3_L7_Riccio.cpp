// Author: Ryan Riccio
// Assignment Number: Lab 7: Item Class
// File Name: DL3_L7_Riccio.cpp
// Course/Section: COSC 1337 Section DL3
// Due Date: October 22nd, 2020
// Instructor: Professor Paul Thayer
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

// input template
template<typename T>
T get_input(const string& prompt, const string& err_msg, T max, T min = T{})
{
	while (true)
	{
		cout << prompt; T item{};	// create item to store
		if (cin >> item && (item >= min && item <= max)) return item;	// check for failure
		cout << err_msg; cin.clear(); cin.ignore(INT_MAX, '\n'); // handle failure
	}
}

// item class
class Item
{
private:
	// member vars
	string name;
	int id{};
	int quantity{};
	double cost{};

public:
	// to accumulate total costs
	static double accumulated_cost;
	
	// default constructor
	Item()
	{
		name = "";
		id, quantity, cost = 0.0;
	}

	// validate and set member variables
	Item(string name, int id, int quantity, double cost)
	{
		set_name(name);
		set_ID(id);
		set_quantity(quantity);
		set_cost(cost);

		// calc new accum cost
		accumulated_cost += get_total_cost();
	}

	// functions to validate and set private member vars
	void set_name(string new_name) 
	{
		name = new_name;
	};
	void set_ID(int new_id) 
	{
		if (new_id >= 0)
			id = new_id;
		else
			throw invalid_argument("An invalid ID has been given.\n");
	};
	void set_quantity(int new_quantity) 
	{
		if (new_quantity >= 0)
			quantity = new_quantity;
		else
			throw invalid_argument("Quantity cannot be negative.\n");
	};
	void set_cost(double new_cost) 
	{
		if (new_cost >= 0.00)
			cost = new_cost;
		else
			throw invalid_argument("Cost cannot be less that $0.00.\n");
	};

	// getters
	string get_name() const { return name; };
	int get_ID() const { return id; };
	int get_quantity() const { return quantity; };
	double get_cost() const { return cost; };
	double get_total_cost() const { return cost * quantity; };

	// display class data
	void display() 
	{
		cout << "Name: " << get_name() << "\nID: " << get_ID() << "\nQuantity: "  
			<< get_quantity() << fixed << setprecision(2) << "\nCost: $" << get_cost()
			<< "\nTotal Cost: $" << get_total_cost() << '\n';
	};
};

// function to read from .csv
vector<Item> ReadFromFile(const char* filename)
{
	ifstream inFile(filename);
	if (inFile)
	{
		// place to store current row, word, list of words in row
		string row, word, row_items[4];
		vector<Item> items;
		while (!inFile.eof())
		{
			// get line, and put to stringstream to allow comma separation
			getline(inFile, row);
			stringstream stream(row);
			for (int index{ 0 }; index < 4; index++)
			{
				getline(stream, word, ',');	// separation
				row_items[index] = word;
			}
			try
			{	// put in vector
				items.push_back(Item(row_items[0], stoi(row_items[1]), stoi(row_items[2]), stod(row_items[3])));
			}
			catch (invalid_argument error)
			{
				cout << "Error with item: " << row_items[0] << " - ";
				cerr << error.what();
			}
		}
		return items;
	}
	// just in case something happens, we init the default constructor
	cout << "\nERROR: Error reading file: '" << filename << "'.\n";
	vector<Item> empty_vector;
	empty_vector.push_back(Item());
	return empty_vector;
}

// to get items from user input
vector<Item> GetItemsFromInput()
{
	// get number of items user wants to enter
	int num_items = get_input("\nHow many items in inventory: ", "Not valid. Max items is 5.\n", 5, 1);
	vector<Item> items;
	for (int index{ 0 }; index < num_items; index++)
	{
		// get each item for class with validation along the way
		string name;
		cout << "\n--Item #" << index + 1 << " of #" << num_items << "--\nName: ";
		cin >> name;
		int id = get_input("ID: ", "Not a valid input.\n", INT_MAX, INT_MIN);
		int quantity = get_input("Quantity: ", "Not a valid input.\n", INT_MAX, INT_MIN);
		double cost = get_input("Cost/Item: ", "Not a valid input.\n", DBL_MAX, -DBL_MAX);
		try
		{	// add to vector
			items.push_back(Item(name, id, quantity, cost));
		}
		catch (invalid_argument error)
		{
			cerr << '\n' << error.what();
			cout << "Try again.\n\n";
			index--;
			continue;
		}
	}
	return items;
}

// before main, init static accumulator
double Item::accumulated_cost{ 0 };

int main()
{
	cout << "This program keeps track of store inventory.\n";
	
	// get option for which function to run
	char input;
	vector<Item> items;
	while (true)
	{
		input = get_input<char>("Do you want to read from (f)ile or give (i)nput: ", "Invalid.\n", CHAR_MAX);
		if (tolower(input) == 'f')
		{
			items = ReadFromFile("DL3_L7_Riccio.csv");
			break;
		}
		else if (tolower(input) == 'i')
		{
			items = GetItemsFromInput();
			break;
		}
		else
		{
			cin.ignore(INT_MAX, '\n');	// just make sure there's no junk in our buffer
			continue;
		}
	}

	// print dynamically based on number of entries
	int num_items = items.size();
	cout << "\nINVENTORY REPORT\n";
	for (int index{ 0 }; index < num_items; index++)
	{
		cout << "\n--Item #" << index + 1 << " of #" << num_items << "--\n";
		items[index].display();
	}
	cout << fixed << setprecision(2) << "\nTOTAL VALUE OF INVENTORY: $" << Item::accumulated_cost;

	cout << "\n\nThanks for using the program. Goodbye!\n\n";
	return EXIT_SUCCESS;
}

/*
RUN #1:
This program keeps track of store inventory.
Do you want to read from (f)ile or give (i)nput: asdf
Do you want to read from (f)ile or give (i)nput: f

INVENTORY REPORT

--Item #1 of #4--
Name: Apple
ID: 1
Quantity: 5
Cost: $1.21
Total Cost: $6.05

--Item #2 of #4--
Name: Orange
ID: 2
Quantity: 7
Cost: $1.78
Total Cost: $12.46

--Item #3 of #4--
Name: Banana
ID: 3
Quantity: 10
Cost: $0.21
Total Cost: $2.10

--Item #4 of #4--
Name: Melon
ID: 4
Quantity: 2
Cost: $3.99
Total Cost: $7.98

TOTAL VALUE OF INVENTORY: $28.59

Thanks for using the program. Goodbye!


C:\Users\rshar\Desktop\Projects\School\COSC-1337\Release\DL3_L7_Riccio.exe (process 18184) exited with code 0.
Press any key to close this window . . .

RUN #2:

This program keeps track of store inventory.
Do you want to read from (f)ile or give (i)nput: i

How many items in inventory: -1
Not valid. Max items is 5.

How many items in inventory: 6
Not valid. Max items is 5.

How many items in inventory: 4

--Item #1 of #4--
Name: Apple
ID: 1
Quantity: 10
Cost/Item: -1.00

Cost cannot be less that $0.00.
Try again.


--Item #1 of #4--
Name: Apple
ID: 1
Quantity: 10
Cost/Item: 1.00

--Item #2 of #4--
Name: Orange
ID: 2
Quantity: 5
Cost/Item: .75

--Item #3 of #4--
Name: Kumquat
ID: -34
Quantity: jn1234
Not a valid input.
Quantity: 34
Cost/Item: .34

An invalid ID has been given.
Try again.


--Item #3 of #4--
Name: Kumquat
ID: 3
Quantity: 25
Cost/Item: .05

--Item #4 of #4--
Name: Dragonfruit
ID: 4
Quantity: 2
Cost/Item: 0.50

INVENTORY REPORT

--Item #1 of #4--
Name: Apple
ID: 1
Quantity: 10
Cost: $1.00
Total Cost: $10.00

--Item #2 of #4--
Name: Orange
ID: 2
Quantity: 5
Cost: $0.75
Total Cost: $3.75

--Item #3 of #4--
Name: Kumquat
ID: 3
Quantity: 25
Cost: $0.05
Total Cost: $1.25

--Item #4 of #4--
Name: Dragonfruit
ID: 4
Quantity: 2
Cost: $0.50
Total Cost: $1.00

TOTAL VALUE OF INVENTORY: $16.00

Thanks for using the program. Goodbye!


C:\Users\rshar\Desktop\Projects\School\COSC-1337\Release\DL3_L7_Riccio.exe (process 18340) exited with code 0.
Press any key to close this window . . .

*/