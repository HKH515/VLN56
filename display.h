#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include "Domain.h"

using namespace std;

class Display
{
private:
    string prompt;

public:
    Display();
    /* Displays messages to user when adding a Person */
    void add_msg_person(int c);
    /* Displays messages to user when adding a Computer */
    void add_msg_computer(int c);
    /* Displays a choice menu for sorting methods */
    void sort_msg(int c);
    /* Displays a choice menu for searching */
    void search_msg(int c);
    /* Displays a choice menu for tables in the database */
    void table_msg(int c);
    /* Displays help message */
    void help_msg();
    /* Displays the search result or the list of all entries in the Persons table*/
    void print_results_person(Domain *d);
    /* Displays the search result or the list of all entries in the Computer table */
    void print_results_comp(Domain *d);
    /* Displays every Person and its id, or Computer and its id that is in the database */
    void display_valid_id(string c, Domain *d);

};

#endif // DISPLAY_H
