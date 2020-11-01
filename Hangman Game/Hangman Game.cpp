//A hangman game with multiple difficulties (lives).
//Available modes (single player only).
//
//Created by: Cornel Stoica
//Date: 1/1/20
//Updated: 3/26/20
//

#include <iostream>
#include <fstream>
#include <string>
#include "hangman.h"


int main()
{
    //variables 
    int menuOption = { 0 };
    int difficulty = { 0 };
    std::string file = { " " };
    std::string word = { " " };
    std::string subWord = { " " };
    std::string guessedChars = { " " };
    int count = { 0 };
    int randomLine = { 0 };
    
    //stream variables
    std::ifstream input;
    std::ofstream output;
    
    do
    {
        display_menu();
        menuOption = get_option();

        //if user wants to exit game
        if (menuOption == 2) {
            std::cout << "Thank you playing!" << std::endl;
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

        subWord.resize(word.length()); //resize subWord variable to match word length

        //reset subWord string to all underscores
        for (unsigned int i = 0; i < subWord.length(); ++i) {
            subWord[i] = '_';
        }

        //display unguessed word
        display_unguessed(word);

        //begin guessing game
        start_guess(word, subWord, guessedChars, difficulty);

    } while(true);

    std::cout << "\n\n\n"; //extra space at the end

    return 0;
}