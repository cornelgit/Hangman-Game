//A hangman game with multiple difficulties and a scoring system.
//Avaialble modes (single player only).
//
//Created by: Cornel Stoica
//Date: 1/1/20
//

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

//Function prototypes
void display_menu();
int get_option();
int get_difficulty();
string open_file(ifstream &);
string get_word(ifstream &, int);
int line_count(ifstream &, string);
int random_line(int);

int main()
{
    //variables
   
    int menuOption = { 0 };
    int difficulty = { 0 };
    string file = { " " };
    string word = { " " };
    int count = { 0 };
    int randomLine = { 0 };
    
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

    //get line (word) count in file
    count = line_count(input, file);

    //get random line number from file
    randomLine = random_line(count);

    //read the random line (get word)
    word = get_word(input, randomLine);




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
        cout << "\nLives available (guesses). ";
        cout << "\n2 Lives ---> (2) ";
        cout << "\n4 Lives ---> (4) ";
        cout << "\n6 Lives ---> (6) ";
        cout << "\n8 Lives ---> (8) ";
        cout << "\n10 Lives ---> (10) ";
        cout << "\nMax (26) Lives ---> (26) ";
        cout << "\nHow many lives would like to start with? ";
        cin >> difficulty;

        if (cin.fail() && !isdigit(difficulty)) {
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
    while (!input)
    {
        cout << "\nCould not open \"" << file << "\". " << "Please try again." << endl;
        cout << "Please enter the input filename including extension: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, file);
        input.open(file); //attempt to open new filename

    }

    cout << "Succesfuly opened \"" << file << "\"." << endl << endl; //if file was valid and opened

    return file;
}

//Function to get number of words (lines) in file
int line_count(ifstream & input, string file)
{
    int count = { 0 };
    string blank = { " " };

    while (!input.eof())
    {
        input >> blank;
        ++count;
    }
    
    input.seekg(0); // rewind stream
    cout << "Count is: " << count << endl;
    return count;
}

//Function to get random file line number (word)
int random_line(const int count )
{
    int line = { 0 };
    int i = 1;
    srand(unsigned(time(NULL))); //random number generator
       
    line = 1 + (rand() % count); //get random line number from file
    
    return line;
}

//Function to get the random word based on it's line number
string get_word(ifstream & input, int randomLine)
{
    string word = { " " };
 
    //go through each line (word) until we have the one we need
    for (int i = 1; i <= randomLine; ++i) {           
        if (i == randomLine) {
            getline(input, word);
            break; //break out if word was retrieved 
        }
        else
            input.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore words we don't need
    }

    return word;
}