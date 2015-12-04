#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <string>
#include <vector>
#include <ctype.h>
#include <stdio.h>

#include "domain.h"
#include "person.h"
#include "data.h"

class presentation
{
private:
    Domain *d;
    /* Prompt to separate input from output on the screen */
    string prompt;

    /* Constructs the string that is sent to the domain layer if adding a person*/
    vector <string> parse_add(string choice);
    /* Check if the user entered an valid name and profession */
    bool check_if_word(string input);
    /* Check if the user enters valid year */
    bool check_if_year(string input);
    /* Displays the search result or the list of all entries in the Persons table*/
    void print_results_person();
    /* Displays the search result or the list of all entries in the Computer table */
    void print_results_comp();


    /* Functions that error check input from user */
    string verify_name();
    string verify_profession();
    string verify_birthyear();
    string verify_deathyear(string birhty);
    string verify_sex();
    bool verify_built();
    string verify_table();
    string verify_sort_column_person(string sort_by);
    string verify_sort_column_comp(string sort_by);
    string verify_order_of_sort(string order);
    string verify_search_column_person(string column);
    string verify_search_column_comp(string column);

    string verify_person_id();
    string verify_computer_id();

    /* Displays messages to the user during add command*/
    void add_msg_person(int c);

    void add_msg_computer(int c);

    vector<string> add_connection();
    /* Displays a choice menu for sorting methods */
    void sort_msg(int c);
    /* Displays help message */
    void help_msg();
    /* Displays a choice menu for tables*/
    void table_msg(int c);
    /* Displays a choice menu for searching */
    void search_msg(int c);

    void display_valid_id(int c);
public:
    /* Constructor */
    presentation();
    /* Destructor */
    ~presentation();

    Domain* get_domain();
    /* Handles the commands and communicates with the domain-layer */
    void choice(Domain* d);

};

#endif // PRESENTATION_H
