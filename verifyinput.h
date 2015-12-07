#ifndef VERIFYINPUT_H
#define VERIFYINPUT_H
#include <domain.h>

#include <string>
#include <iostream>
#include <sstream>

/* Class that receives input from user and validates it, only used in the presentation layer */

using namespace std;

class VerifyInput
{
private:
    string input;
    /* Prompt to separate input from output on the screen */
    string prompt;
public:
    VerifyInput();
    /* Functions that receive input from user and verifies it */

    /* Verifies the inputted name when adding a Person */
    string verify_name();
    /* Verfies profession when adding a Person */
    string verify_profession();
    /* Verifies the birthyear of a Person and Construction Year of a Computer when adding*/
    string verify_birthyear();
    /* Verifies the deathyear when adding a Person */
    string verify_deathyear(string birhty);
    /* Verifies the sex when adding a Person */
    string verify_sex();
    /* Verifies that user input 0 (No) or 1 (Yes) for built when adding a Computer */
    string verify_built();
    /* Verifies that user chooses one of the three available tables in the database
     * when adding or removing */
    string verify_table();
    /* Verifies that user chooses one of the columns for Person (except description) to sort by */
    string verify_sort_column_person();
    /* Verifies that user chooses one of the columns for Computer (except description) to sort by */
    string verify_sort_column_comp();
    /* Verifies that the user chooses either ascending (a) or descending (d) */
    string verify_order_of_sort();
    /* Verifies that the user chooses one of the columns in Person to search for */
    string verify_search_column_person();
    /* Verifies that the user chooses one of the columns in Computer to search for */
    string verify_search_column_comp();
    /* Verifies that the user either chooses to get all Computers connected to a certain
     * Person or to get all Persons connected to a certain Computer */
    string verify_connections_column();
    /* Check if the user entered an valid name and profession (Only alphabet letters allowed) */
    bool check_if_word(string input);
    /* Check if the user enters valid year */
    bool check_if_year(string input);
};

#endif // VERIFYINPUT_H
