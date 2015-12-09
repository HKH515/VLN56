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
    /* Buisness layer */
    Domain *d;
    /* Class that receives and verifies every input that the user inserts */
    VerifyInput *v;
    /* Class that displays messages to the screen */
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
    /* Get all Id's in the database of either Computer Scientists or Computers */
    vector<string> get_ids(int c);
    /* Receives id from user and verifies that it is one of the Id's in the database */
    string valid_id(string table);
    /* Changes the argument from int to string */
    string int_to_string(int number);

public:
    /* Constructor */
    presentation();
    /* Destructor */
    ~presentation();
    /* Returns the domain variable */
    Domain* get_domain();
    /* Handles the commands and communicates with the domain-layer */
    void choice();

};

#endif // PRESENTATION_H
