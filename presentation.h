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
    VerifyInput *v;
    /* Prompt to separate input from output on the screen */
    string prompt;

    /* Constructs the string that is sent to the domain layer if adding a person*/
    vector <string> parse_add(string choice);

    /* Displays the search result or the list of all entries in the Persons table*/
    void print_results_person();
    /* Displays the search result or the list of all entries in the Computer table */
    void print_results_comp();




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
