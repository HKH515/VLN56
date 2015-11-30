#ifndef DOMAIN_H
#define DOMAIN_H

#include "person.h"
#include "data.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

enum column { name, profession, description, birthyear, deathyear, sex };

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
    bool greater(Person &lhs, Person &rhs) const;
    vector<Person> handle_commands(vector<string> v);

    Domain()
    {

    }

};
#endif // DOMAIN_H
