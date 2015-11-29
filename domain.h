#ifndef DOMAIN_H
#define DOMAIN_H

#include "person.h"
#include "Data.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

class Domain
{
private:
    Data* data = new Data("data.dat");
    vector<Person> vec;

public:
    void sort_ascending(vector<Person> &v);
    void sort_descending(vector<Person> &v);
    void parse_query_vector(vector<string> v);
    string parse_add_command(vector<string> vec);
    bool greater(Person lhs, Person rhs);
    vector<Person> handle_commands(vector<string> v);

    Domain()
    {

    }

};
#endif // DOMAIN_H
