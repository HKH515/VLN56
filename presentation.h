#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <string>
#include <vector>
#include <ctype.h>
#include <cstdlib>
#include <stdio.h>

#include "domain.h"
#include "person.h"
#include "data.h"
#include "verifyinput.h"

class presentation
{
private:
    Domain *d;
    /* Class that verifies every input that the user inserts */
    VerifyInput *v;
    /* Prompt to separate input from output on the screen */
    string prompt;

    /* Constructs the string that is sent to the domain layer if adding */
    vector <string> parse_add(string choice);
    /* Helping function to add a connection between a Person and a Computer */
    vector<string> add_connection();
    /* Removes chosen entry from the database */
    vector<string> remove_entry();
    /* Gets all Computer scientists or Computers */
    void get_list(string table);
    /* Displays the search result or the list of all entries in the Persons table*/
    void print_results_person();
    /* Displays the search result or the list of all entries in the Computer table */
    void print_results_comp();
    /* Displays messages to the when adding a Person */
    void add_msg_person(int c);
    /* Displays messages to the when adding a Computer */
    void add_msg_computer(int c);
    /* Displays a choice menu for sorting methods */
    void sort_msg(int c);
    /* Displays a choice menu for searching */
    void search_msg(int c);
    /* Displays a choice menu for tables in the database */
    void table_msg(int c);
    /* Displays help message */
    void help_msg();
    /* Displays every Person and its id, or Computer and its id that is in the database */
    void display_valid_id(string c);

    string verify_id(string table);

public:
    /* Constructor */
    presentation();
    /* Destructor */
    ~presentation();

    Domain* get_domain();
    /* Handles the commands and communicates with the domain-layer */
    void choice();

};

#endif // PRESENTATION_H
