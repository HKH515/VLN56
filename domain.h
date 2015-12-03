#ifndef DOMAIN_H
#define DOMAIN_H

#include "person.h"
#include "data.h"
#include "compareperson.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

class Domain
{
private:
    Data* data;
    vector<Person*> vec;

    /* Sort functions */
    void sort_ascending(vector<Person*> &v, int sort_column);
    void sort_descending(vector<Person*> &v, int sort_column);
    /* parses the information, to be added from the database, from the user the and puts
     * delimeter (|) between */
    string parse_add_command(vector<string> vec);
    bool greater(Person &lhs, Person &rhs) const;
    /* Receives a vector of strings from data layer and parses the string, fills into
       the persons class and returns a vector of persons* to the presentation layer */
    void parse_query_vector(vector<string> v, int sort_column, string sort_method);
    /* deletes all persons object from the vector and clears the vector befor each command to be handled */
    void free_vector_memory();

    void get_list(vector<string> v);
    void add_entry(vector<string> v);
    void search(vector<string> v);
    string get_table(string s);
    string get_column(string s, string table);
    string get_sort_method(string s);

public:

    /* Constructor */
    Domain();
    ~Domain();

    /* Receives command vector and parses it and sends informations to the data layer */
    void handle_commands(vector<string> v);

    vector<Person*> get_vec();
};
#endif // DOMAIN_H
