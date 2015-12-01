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
    vector<Person> vec;

public:
    void sort_ascending(vector<Person> &v, int search_column);
    void sort_descending(vector<Person> &v, int search_column);
    void parse_query_vector(vector<string> v, int search_column, string sort_method);
    string parse_add_command(vector<string> vec);
    bool greater(Person &lhs, Person &rhs) const;
    void handle_commands(vector<string> v);
    vector<Person> get_vec();

    Domain();
};
#endif // DOMAIN_H
