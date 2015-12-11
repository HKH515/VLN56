#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

using namespace std;

/* Class that displays messages to the user */

class Display
{
private:
    /* Prompt to separate input from output on the screen */
    string prompt;

public:
    Display();
    /* Displays messages to user when adding a Person */
    void add_msg_person(int c);
    /* Displays messages to user when adding a Computer */
    void add_msg_computer(int c);
    /* Displays messages to user when adding a Connection */
    void add_msg_connection(int c);
    /* Displays a choice menu for sorting methods */
    void sort_msg(int c);
    /* Displays a choice menu for searching */
    void search_msg(int c);
    /* Displays a choice menu for tables in the database */
    void table_msg(int c);
    /* Displays instruction for user to remove something from the database */
    void remove_msg(string c);
    /* Displays a choice menu for displaying connections */
    void connection_msg(string c);
    /* Displays help message */
    void help_msg();
    /* Displays the search result or the list of all entries in the Persons table*/
    void print_results_person(Domain *d, int c);
    /* Displays the search result or the list of all entries in the Computer table */
    void print_results_comp(Domain *d, int c);
    /* Displays list of connections */
    void print_connections_list(Domain *d);
    /* Displays every Person and its id, or Computer and its id that is in the database */
    void display_valid_id(string c, Domain *d);
};

#endif // DISPLAY_H
