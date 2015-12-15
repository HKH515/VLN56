#ifndef COMPUTERSERVICE_H
#define COMPUTERSERVICE_H

#include "computerRepository.h"
#include "computer.h"
#include <sstream>

#include <vector>
class ComputerService
{

private:
    vector<Computer*> computer_vec;
    ComputerRepository* computer_repo;

    string check_search_substring(string subst);

public:
    ComputerService();
    ~ComputerService();
    // Get functions
    vector<Computer*> get_computer_vec();
    // Deletes all computer objects from the vector and clears the vector before each command to be handled
    void free_vector_memory();
    // Makes the string with delim '|' to send to the data layer
    string parse_add_command(vector<string> vec);
    // Receives a vector of strings from data layer and parses the string, fills into
    // the persons class and returns a vector of persons* to the presentation layer
    void parse_query_vector(vector<string> v);
    // Handles the list command
    void get_all_computers();
    // Handles the add command
    void add_computer(vector<string> v);
    // Handles the search command
    void search_computer(string column, string substring);
    // Handles the remove command
    void remove_computer(int id);
    // Returns the computer with the id 'chosen_id'
    Computer* find_chosen_computer(int chosen_id);

    Computer* find_chosen_computer_by_name(string chosen_name);
};

#endif // COMPUTERSERVICE_H
