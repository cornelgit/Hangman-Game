//A hangman game with multiple difficulties and a scoring system.
//Available modes (single player only).
//
//Created by: Cornel Stoica
//Date: 1/1/20
//

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

//Function prototypes
void display_menu();
int get_option();
int get_difficulty();
string open_file(ifstream &);
string get_word(ifstream &, int);
void start_guess(string, string &, string &, int);
void display_unguessed(string);
int line_count(ifstream &, string);
int random_line(int);
bool check_word_guess(string word);

int main()
{
    //variables
   
    int menuOption = { 0 };
    int difficulty = { 0 };
    string file = { " " };
    string word = { " " };
    string subWord = { " " };
    string guessedChars = { " " };
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

    //get file line (word) count
    count = line_count(input, file);

    //get random line number from file
    randomLine = random_line(count);

    //read the random line (word)
    word = get_word(input, randomLine);

    word = "CORNEL"; //for testing purposes   ////////////////////////////////////////////////////////////////////////

    subWord.resize(word.length()); //resize subWord variable to match word length

    //reset subWord string to all underscores
    for (unsigned int i = 0; i < subWord.length(); ++i) {
        subWord[i] = '_';
    }

    //display unguessed word
    display_unguessed(word);   
        
    //begin guessing game
    start_guess(word, subWord, guessedChars, difficulty);

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
    cout << "\nAttempting to open \"" << file << "\".";
    input.open(file);

    //check if open is succesful
    while (!input)
    {
        cout << "\nCould not open \"" << file << "\". " << "Please try again." << endl;
        cout << "Please manually enter the input filename including extension (absolute path is also acceptable): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, file);
        input.open(file); //attempt to open new filename

    }

    cout << "\nSuccesfuly opened filename \"" << file << "\"." << endl << endl; //if file was valid and opened

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
    
    //convert word to uppercase
    transform(word.begin(), word.end(), word.begin(), ::toupper);
  
    return word;
}

//Function to display word to be guessed
void display_unguessed(string word)
{
    //display tip
    cout << "\nNOTE: For each incorrect guess you are deducted a life. There is no penalty for attempting to guess full word." << endl;
    
    cout << "The word is " << word.length() << " characters long." << endl;
    cout << "Word: ";

    for (unsigned int i = 0; i < word.length(); ++i) {
        cout << " _ ";
    }   
}

//Function to start guessing word/letters
void start_guess(string word, string & subWord, string & guessedChars, int difficulty)
{
    char guessChar = ' ';
    bool guessedCorrectly = false;
    bool loopFunction = false;
    char tryAgain = { ' ' };
        
    //display remaining lives (guesses)
    cout << "\tLives remaining [" << difficulty << "]" << endl;

    //get guessing option
    do {
        cout << "\nPlease enter a guessing letter or enter (1) to try and guess full word. ";      
        cout << "\nOtherwise press (0) to quit to main menu: ";      
        cin >> guessChar;
                       
        if (cin.fail() || (!isalpha(guessChar) && guessChar != '1')) {
                cout << "Not a valid selection. Please try again." << endl;
                cin.clear();
                cin.ignore();            
        }

        else if (isalpha(guessChar))
            guessChar = toupper(guessChar); //convert guess to uppercase

    } while (!isalpha(guessChar) && guessChar != '1' && guessChar != '0');

    //if user wants to go back to main menu
    if (guessChar == '0') {
        cout << endl << endl;
        main(); //restart from
    }

    //if user wants to guess full word
    else if (guessChar == '1') {

        //keep checking and asking for word if user wishes to do so
        do {
            guessedCorrectly = check_word_guess(word);
            
            cout << "Try again? Yes (Y) or No (N): ";
            cin >> tryAgain;

            if (cin.fail() || (!isalpha(tryAgain) && tryAgain != 'Y' && tryAgain != 'N')) {
                cout << "Not a valid selection. Please try again. " << endl;
                cin.clear();
                cin.ignore();
            }          

            tryAgain = toupper(tryAgain);

        } while (tryAgain == 'Y' && guessedCorrectly == false);
    }

    //if a valid letter was entered
    else {
        if (word.find(guessChar) != string::npos) {                   
            if (guessedChars.find(guessChar) != string::npos)
                cout << "\nYou've already guessed that letter." << endl;

            else {
                cout << "\nLetter found." << endl;
                guessedChars.push_back(guessChar); //add guessed word to list if not already on it
              
                for (unsigned int i = 0; i < word.length(); ++i) {                   
                    if (word[i] == guessChar && subWord[i] == '_')
                            subWord[i] = guessChar;                 
                }
            }                                      
        }        
                       
        else {
            cout << "\nLetter not found." << endl;
            guessedChars.push_back(guessChar); //add guessed word
            --difficulty;                     
        }
        loopFunction = true;
    }

    //display partial word and guesses so far
    cout << "Word: ";
    for (unsigned int i = 0; i < word.length(); ++i) {
        cout << subWord[i] << " ";
    }
    cout << "\tGuessed so far:";
    for (unsigned int i = 0; i < guessedChars.length(); ++i) {
        cout << guessedChars[i] << " ";
    }

    //if we want to loop through function again
    if (loopFunction == true && guessedCorrectly == false && difficulty > 0)
        start_guess(word, subWord, guessedChars, difficulty);

    //if user completed word or ran out of lives
    else {
        if (difficulty == 0) {
            cout << "Game over. You are out of lives. " << endl;
            cout << "\nThe word is \"" << word << "\"." << endl << endl;
            cout << "Returning to main menu." << endl;
            main();
        }

        //if word is completed or guessed correctly
        else {
            cout << "\nThe word is \"" << word << "\"." << endl << endl;
            cout << "Returning to main menu." << endl << endl << endl;
            main();
        }
    }
}

//Function to check full word guess
bool check_word_guess(string word)
{
    string wordGuess = { " " };
    bool guessedCorrectly = false;
     
    //get user guessed word
    cout << "\nWhat is the word? ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, wordGuess);
    
    //convert guessed word to uppercase
    transform(wordGuess.begin(), wordGuess.end(), wordGuess.begin(), ::toupper);

    //check if guessed word is correct and of right length
    if (wordGuess.length() < word.length())
        cout << "Your guess is too short. ";
    else if (wordGuess.length() > word.length())
        cout << "Your guess is too long. ";
    else
        if (wordGuess.length() == word.length()) {
            if (wordGuess == word) {
                guessedCorrectly = true;
                cout << "You guessed correctly. ";
            }
            else
                cout << "Sorry, that is not the correct word. ";
        }
             
    return guessedCorrectly;
}