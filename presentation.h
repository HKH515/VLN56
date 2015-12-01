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
    string prompt = "> ";

    /* Constructs the string that is added into the database */
    vector <string> parse_add();
    /* Displays the search result or the list of all entries in the database */
    void print_results(Domain *d);
    /* Displays a choice menu for sorting methods */
    void sort_msg(int c);
    /* check if the user entered an valid name and profession */
    bool check_if_word(string input);
    /* Check if the user enters valid year */
    bool check_if_year(string input);

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
