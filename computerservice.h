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

public:
    ComputerService();
    ~ComputerService();

    string parse_add_command(vector<string> vec);
    /* Receives a vector of strings from data layer and parses the string, fills into
       the persons class and returns a vector of persons* to the presentation layer */
    void parse_query_vector(vector<string> v);
    /* Deletes all persons object from the vectors and clears the vectors before each command to be handled */
    void free_vector_memory();
    /* Handles the list command */
    void get_all_computers();
    /* Handles the add command */
    void add_computer(vector<string> v);
    /* Handles the search command */
    void search_computer(string column, string substring);
    /* Handles the remove command */
    void remove_computer(int id);
    Computer* find_chosen_computer(string chosen_name);

    vector<Computer*> get_computer_vec();
};

#endif // COMPUTERSERVICE_H
