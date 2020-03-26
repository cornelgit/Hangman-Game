#pragma once

//Function prototypes
void display_menu();
int get_option();
int get_difficulty();
std::string open_file(std::ifstream&);
std::string get_word(std::ifstream&, int);
void start_guess(std::string, std::string&, std::string&, int);
void display_unguessed(std::string);
int line_count(std::ifstream&, std::string);
int random_line(int);
bool check_word_guess(std::string word);
void pause();