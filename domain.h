#ifndef DOMAIN_H
#define DOMAIN_H

#include "person.h"
#include "Data.h"
#include <string>
#include <iostream>

class Domain
{
private:
    Data data;
    vector<Person> vec;

    //void sort_ascending(vector<Person> v);
    void parse_query_vector(vector<string> v);

public:

    Domain();

};
#endif // DOMAIN_H
