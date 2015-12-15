#ifndef PERSONSSERVICE_H
#define PERSONSSERVICE_H

#include "personRepository.h"
#include "person.h"
#include <sstream>

class PersonsService
{
private:
    vector<Person*> person_vec;
    PersonRepository* person_repo;
    string check_search_substring(string column, string substring);

public:
    string parse_add_command(vector<string> vec);
    /* Receives a vector of strings from data layer and parses the string, fills into
       the persons class and returns a vector of persons* to the presentation layer */
    void parse_query_vector(vector<string> v);
    /* Deletes all persons object from the vectors and clears the vectors before each command to be handled */
    void free_vector_memory();
    /* Handles the list command */
    void get_all_persons();
    /* Handles the add command */
    void add_person(vector<string> v);
    /* Handles the search command */
    void search_person(string column, string substring);
    /* Handles the remove command */
    void remove_person(int id);
    Person* find_chosen_person(string chosen_name);

    Person* find_chosen_person(string name);

    vector<Person *> get_person_vec();
    PersonsService();
    ~PersonsService();
};

#endif // PERSONSSERVICE_H
