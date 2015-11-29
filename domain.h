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
    //Data data;

public:
    vector<Person> vec;
    void sort_ascending(vector<Person> &v);
    //void sort_descending(vector<Person> &v);
    void parse_query_vector(vector<string> v);
    //bool greater(Person lhs, Person rhs);

    Domain()
    {

    }

};
#endif // DOMAIN_H
