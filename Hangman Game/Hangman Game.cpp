//A hangman game with multiple difficulties and a scoring system.
//Avaialble modes (single player only).
//
//Created by: Cornel Stoica
//Date: 1/1/20
//

#include <iostream>
#include <fstream>

//Function prototypes
void display_menu();
int get_option();


using namespace std;

int main()
{
    int menuOption = { 0 };
    
    display_menu();
    menuOption = get_option();



  

    cout << endl << endl << endl; //Extra space at the end

    return 0;
}


//Function to display menu
void display_menu()
{
    cout << "Welcome to Hangman. Please select an option from the menu below." << endl;
    cout << "==============================" << endl;
    cout << "To start a new game press (1)" << endl;
    cout << "To quit press (2)" << endl;
    cout << "==============================" << endl;
}

//Function to display menu
int get_option()
{   
    int option = { 0 };

    do {
        cout << "\nPlease make a selection now: ";
        cin >> option;

        if (cin.fail() && !isdigit(option)) {
            cout << "\nNot a valid selection. Please try again." << endl;
            cin.clear();
            cin.ignore();
        }

    } while (option != 1 && option != 2);
        
    //If user wants to exit game
    if (option == 2) {
        cout << "Thank you playing!" << endl;
        exit(0);
    }

    else
        return option;
}