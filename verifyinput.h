#ifndef VERIFYINPUT_H
#define VERIFYINPUT_H
#include <domain.h>

#include <string>
#include <iostream>
#include <sstream>


using namespace std;

class VerifyInput
{
private:
    string input;
    string prompt;
public:
    VerifyInput();

    /* Functions that receive input from user and verifies it */
    string verify_name();
    string verify_profession();
    string verify_birthyear();
    string verify_deathyear(string birhty);
    string verify_sex();
    string verify_built();
    string verify_table();
    string verify_sort_column_person();
    string verify_sort_column_comp();
    string verify_order_of_sort();
    string verify_search_column_person();
    string verify_search_column_comp();
    string verify_connections_column();


    /* Check if the user entered an valid name and profession (Only alphabet letters allowed) */
    bool check_if_word(string input);
    /* Check if the user enters valid year */
    bool check_if_year(string input);
};

#endif // VERIFYINPUT_H
