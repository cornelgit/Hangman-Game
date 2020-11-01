#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
#include "hangman.h"

//Function to display menu
void display_menu()
{
    std::cout << "Welcome to Hangman. Please select an option from the menu below." << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "|To start a new game press (1)|" << std::endl;
    std::cout << "|To quit press (2)            |" << std::endl;
    std::cout << "===============================" << std::endl;
}

//Function to get menu option
int get_option()
{
    int option = { 0 };

    do {
        std::cout << "\nPlease make a selection: ";
        std::cin >> option;

        if (std::cin.fail() && !isdigit(option)) {
            std::cout << "\nNot a valid selection. Please try again." << std::endl;
            std::cin.clear();
            std::cin.ignore();
        }

    } while (option != 1 && option != 2);

    return option;
}

//Function to get difficulty setting
int get_difficulty()
{
    int difficulty = { 0 };

    do {
        std::cout << "\nLives available (guesses). ";
        std::cout << "\n2   Lives ---> (2) ";
        std::cout << "\n4   Lives ---> (4) ";
        std::cout << "\n6   Lives ---> (6) ";
        std::cout << "\n8   Lives ---> (8) ";
        std::cout << "\n10  Lives ---> (10) ";
        std::cout << "\nMax Lives ---> (26) ";
        std::cout << "\n\nHow many lives would you like to start with? ";
        std::cin >> difficulty;

        if (!isdigit(difficulty) && std::cin.fail()) {
            std::cout << "\nNot a valid selection. Please try again." << std::endl;
            std::cin.clear();
            std::cin.ignore();
        }

    } while (difficulty != 2 && difficulty != 4 && difficulty != 6 && difficulty != 8 && difficulty != 10 && difficulty != 26);

    return difficulty;
}

//Function to open file
std::string open_file(std::ifstream& input)
{
    std::string file = { "words.txt" };

    //attempt to open file containing words
    std::cout << "\nAttempting to open \"" << file << "\".";
    input.open(file);

    //check if open is succesful
    while (!input)
    {
        std::cout << "\nCould not open \"" << file << "\". " << "Please try again." << std::endl;
        std::cout << "Please manually enter the input filename including extension (absolute path is also acceptable): ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, file);
        input.open(file); //attempt to open new filename

    }

    std::cout << "\nSuccesfuly opened filename \"" << file << "\"." << std::endl << std::endl; //if file was valid and opened

    return file;
}

//Function to get number of words (lines) in file
int line_count(std::ifstream& input, std::string file)
{
    int count = { 0 };
    std::string blank = { " " };

    while (!input.eof())
    {
        input >> blank;
        ++count;
    }

    input.seekg(0); // rewind stream

    return count;
}

//Function to get random file line number (word)
int random_line(const int count)
{
    int line = { 0 };
    int i = 1;
    srand(unsigned(time(NULL))); //random number generator

    line = 1 + (rand() % count); //get random line number from file

    return line;
}

//Function to get the random word based on it's line number
std::string get_word(std::ifstream& input, int randomLine)
{
    std::string word = { " " };

    //go through each line (word) until we have the one we need
    for (int i = 1; i <= randomLine; ++i) {
        if (i == randomLine) {
            getline(input, word);
            break; //break out if word was retrieved 
        }
        else
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore words we don't need
    }

    //convert word to uppercase
    transform(word.begin(), word.end(), word.begin(), ::toupper);

    return word;
}

//Function to display word to be guessed
void display_unguessed(std::string word)
{
    //display tip
    std::cout << "\nNOTE: For each incorrect guess you are deducted a life. There is no penalty for attempting to guess full word." << std::endl;
    std::cout << "Be aware that guessing a letter you've already guessed incorrectly will result in a life deduction each time." << std::endl;

    std::cout << "The word is " << word.length() << " characters long." << std::endl;
    std::cout << "Word: ";

    for (unsigned int i = 0; i < word.length(); ++i) {
        std::cout << " _ ";
    }
}

//Function to start guessing word/letters
void start_guess(std::string word, std::string& subWord, std::string& guessedChars, int difficulty)
{
    char guessChar = ' ';
    bool guessedCorrectly = false;
    bool loopFunction = false;
    char tryAgain = { ' ' };

    //display remaining lives (guesses)
    std::cout << "\tLives remaining [" << difficulty << "]" << std::endl;

    //get guessing option
    do {
        std::cout << "\nPlease enter a guessing letter or enter (1) to try and guess full word. ";
        std::cout << "\nOtherwise press (0) to quit to main menu: ";
        std::cin >> guessChar;

        if (std::cin.fail() || (!isalpha(guessChar) && guessChar != '1')) {
            std::cout << "Not a valid selection. Please try again." << std::endl;
            std::cin.clear();
            std::cin.ignore();
        }

        else if (isalpha(guessChar))
            guessChar = toupper(guessChar); //convert guess to uppercase

    } while (!isalpha(guessChar) && guessChar != '1' && guessChar != '0');

    //if user wants to go back to main menu
    if (guessChar == '0') {
        std::cout << std::endl << std::endl;
        pause();
        std::cout << "Returning to main menu." << std::endl << std::endl << std::endl;
        return; //stop current game and exit to menu
    }

    //if user wants to guess full word
    else if (guessChar == '1') {

        //keep checking and asking for word if user wishes to do so
        do {
            guessedCorrectly = check_word_guess(word);

            if (guessedCorrectly == false) {
                std::cout << "Try again? Yes (Y) or No (N): ";
                std::cin >> tryAgain;

                if (std::cin.fail() || (!isalpha(tryAgain) && tryAgain != 'Y' && tryAgain != 'N')) {
                    std::cout << "Not a valid selection. Please try again. " << std::endl;
                    std::cin.clear();
                    std::cin.ignore();
                }
            }

            tryAgain = toupper(tryAgain);

        } while (tryAgain == 'Y' && guessedCorrectly == false);
    }

    //if a valid letter was entered
    else {

        //if letter is in actual word
        if (word.find(guessChar) != std::string::npos) {
            if (guessedChars.find(guessChar) != std::string::npos)
                std::cout << "\nYou've already guessed that letter." << std::endl;

            else {
                std::cout << "\nLetter found." << std::endl;
                guessedChars.push_back(guessChar); //add guessed word to list if not already on it

                for (unsigned int i = 0; i < word.length(); ++i) {
                    if (word[i] == guessChar && subWord[i] == '_')
                        subWord[i] = guessChar;
                }
            }
        }

        //if letter is in guesses word so far
        else if (subWord.find(guessChar) != std::string::npos)
            std::cout << "\nYou've already guessed that letter." << std::endl;

        //if letter not found at all
        else {
            std::cout << "\nLetter not found." << std::endl;
            guessedChars.push_back(guessChar); //add guessed word
            --difficulty;
        }

        loopFunction = true;
    }

    //display word if guessed
    if (guessedCorrectly == true) {
        std::cout << "\nThe word is \"" << word << "\"." << std::endl << std::endl;
        pause();
        std::cout << "Returning to main menu." << std::endl << std::endl << std::endl;
        return;
    }

    else {
        //display partial word and guesses so far
        std::cout << "Word: ";
        for (unsigned int i = 0; i < word.length(); ++i) {
            std::cout << subWord[i] << " ";
        }
        std::cout << "\tGuessed so far:";
        for (unsigned int i = 0; i < guessedChars.length(); ++i) {
            std::cout << guessedChars[i] << " ";
        }
    }

    //if we want to loop through function again
    if (loopFunction == true && guessedCorrectly == false && difficulty > 0)
        start_guess(word, subWord, guessedChars, difficulty);

    //if user completed word or ran out of lives
    else {
        if (difficulty == 0) {
            std::cout << "\n\nGame over. You are out of lives. " << std::endl;
            std::cout << "\nThe word is \"" << word << "\"." << std::endl << std::endl;
            pause();
            std::cout << "Returning to main menu." << std::endl;
            return;
        }
    }
}

//Function to check full word guess
bool check_word_guess(std::string word)
{
    std::string wordGuess = { " " };
    bool guessedCorrectly = false;

    //get user guessed word
    std::cout << "\nWhat is the word? ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, wordGuess);

    //convert guessed word to uppercase
    transform(wordGuess.begin(), wordGuess.end(), wordGuess.begin(), ::toupper);

    //check if guessed word is correct and of right length
    if (wordGuess.length() < word.length())
        std::cout << "Your guess is too short. ";

    else if (wordGuess.length() > word.length())
        std::cout << "Your guess is too long. ";

    else
        if (wordGuess.length() == word.length()) {
            if (wordGuess == word) {
                guessedCorrectly = true;
                std::cout << "You guessed correctly. ";
            }
            else
                std::cout << "Sorry, that is not the correct word. ";
        }

    return guessedCorrectly;
}

//Function to add pause before going back to menu
void pause()
{
    std::string input; //variable to hold input

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Press any key to continue . . .";
    std::getline(std::cin, input);
}