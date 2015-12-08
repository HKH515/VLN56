#ifndef DOMAIN_H
#define DOMAIN_H

#include "person.h"
#include "computer.h"
#include "data.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

class Domain
{
private:
    Data* data;
    vector<Person*> p_vec;
    vector<Computer*> c_vec;

    /* parses the information, to be added from the database, from the user the and puts
     * delimeter (|) between */
    string parse_add_command(vector<string> vec);
    /* Receives a vector of strings from data layer and parses the string, fills into
       the persons class and returns a vector of persons* to the presentation layer */
    void parse_query_vector(vector<string> v);
    /* Deletes all persons object from the vectors and clears the vectors before each command to be handled */
    void free_vector_memory();
    /* Handles the list command */
    void get_list(vector<string> v);
    /* Handles the add command */
    void add_entry(vector<string> v);
    /* Handles the search command */
    void search(vector<string> v);
    /* Handles the remove command */
    void remove_entry(vector<string> v);
    /* Gets all computer/computer scientists connected to certain computer scientist/computer */
    void get_connected(vector<string> v);
    /* Gets the name of the table in the database */
    string get_table(string s);
    /* Gets the name of the column in a table in the database */
    string get_column(string s, string table);
    /* Gets in which order the user wants to sort the results */
    string get_sort_method(string s);
    /* Lets the user enter specific query strings to search for type */
    string check_type_query(string v);
    /* Lets the user enter specific query string to search for sex */
    string check_sex_query(string v);

public:

    /* Constructor */
    Domain();
    ~Domain();

    /* Receives command vector and parses it and sends informations to the data layer */
    void handle_commands(vector<string> v);

    vector<Person*> get_p_vec();
    vector<Computer*> get_c_vec();
};
#endif // DOMAIN_H
