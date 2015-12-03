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

    /* Constructs the string that is added into the database */
    vector <string> parse_add();
    /* Displays the search result or the list of all entries in the database */
    void print_results(Domain *d);
    /* Displays a choice menu for sorting methods */
    void sort_msg(int c);
    /* Displays messages to the user during add command*/
    void add_msg(int c);
    /* check if the user entered an valid name and profession */
    bool check_if_word(string input);
    /* Check if the user enters valid year */
    bool check_if_year(string input);

    string verify_name();
    string verify_profession();
    string verify_birthyear();
    string verify_deathyear(string birhty);
    string verify_sex();
    string verify_table();
    string verify_sort_column_person(string sort_by);
    string verify_sort_column_comp(string sort_by);
    string verify_order_of_sort(string order);

    void help_msg();
    void table_msg();

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
