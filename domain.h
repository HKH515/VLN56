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

public:
    vector<Person> vec;
    void sort_ascending(vector<Person> &v);
    void sort_descending(vector<Person> &v);
    void parse_query_vector(vector<string> v);
    bool greater(Person lhs, Person rhs);
    vector<string> handle_commands(vector<string> vec);

    Domain()
    {

    }

};
#endif // DOMAIN_H
