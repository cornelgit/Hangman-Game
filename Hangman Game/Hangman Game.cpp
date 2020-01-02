//A hangman game with multiple difficulties and a scoring system.
//Avaialble modes (single player only).
//
//Created by: Cornel Stoica
//Date: 1/1/20
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Function prototypes
void display_menu();
int get_option();
int get_difficulty();
string open_file(ifstream & input);

int main()
{
    //variables
    int menuOption = { 0 };
    int difficulty = { 0 };
    string file = { " " };

    //stream variables
    ifstream input;
    ofstream output;
    
    display_menu();
    menuOption = get_option();

    //if user wants to exit game
    if (menuOption == 2) {
        cout << "Thank you playing!" << endl;
        exit(0);
    }

    else
        difficulty = get_difficulty(); //get difficulty setting
    
    file = open_file(input);



    cout << endl << endl << endl; //extra space at the end

    return 0;
}

//Function to display menu
void display_menu()
{
    cout << "Welcome to Hangman. Please select an option from the menu below." << endl;
    cout << "===============================" << endl;
    cout << "|To start a new game press (1)|" << endl;
    cout << "|To quit press (2)            |" << endl;
    cout << "===============================" << endl;
}

//Function to get menu option
int get_option()
{   
    int option = { 0 };

    do {
        cout << "\nPlease make a selection: ";
        cin >> option;

        if (cin.fail() && !isdigit(option)) {
            cout << "\nNot a valid selection. Please try again." << endl;
            cin.clear();
            cin.ignore();
        }

    } while (option != 1 && option != 2);
        
    return option;
}

//Function to get difficulty setting
int get_difficulty()
{
    int difficulty = { 0 };

    do {
        cout << "\nPlease choose the number of lives (guesses). ";
        cout << "\n2 Lives ---> (2) ";
        cout << "\n4 Lives ---> (4) ";
        cout << "\n6 Lives ---> (6) ";
        cout << "\n8 Lives ---> (8) ";
        cout << "\n10 Lives ---> (10) ";
        cout << "\nMax lives (26) Lives ---> (26) ";
        cin >> difficulty;

        if (cin.fail() || !isdigit(difficulty)) {
            cout << "\nNot a valid selection. Please try again." << endl;
            cin.clear();
            cin.ignore();
        }

    } while (difficulty != 2 && difficulty != 4 && difficulty != 6 && difficulty != 8 && difficulty != 10 && difficulty != 26);

    return difficulty;
}

//Function to open file
string open_file(ifstream & input)
{
    string file = { "words.txt" };

    //attempt to open file containing words
    input.open(file);

    //check if open is succesful
    while (!input.is_open())
    {
        cout << "Could not open \"" << file << "\". " << "Please try again." << endl;
        cout << "Please enter the input filename including extension: ";
        getline(cin, file);
        cout << endl;
        input.open(file); //attempt to open new filename
    }
    cout << "Succesfuly opened \"" << file << "\"." << endl << endl; //if file was valid and opened

    return file;
}