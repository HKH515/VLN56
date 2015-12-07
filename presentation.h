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
#include "display.h"

class presentation
{
private:
    Domain *d;
    /* Class that verifies every input that the user inserts */
    VerifyInput *v;
    /* Class that display messages to the screen */
    Display *msg;
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
    vector<int> get_ids(int c);

    string verify_id(string table, int input);

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
