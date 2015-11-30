#ifndef DOMAIN_H
#define DOMAIN_H

#include "person.h"
#include "Data.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

enum column { name, profession, description, birthyear, deathyear, sex };

class Domain
{
private:
    Data* data;
    vector<Person> vec;

public:
    void sort_ascending(vector<Person> &v);
    void sort_descending(vector<Person> &v);
    void parse_query_vector(vector<string> v, string sort_method);
    string parse_add_command(vector<string> vec);
    bool greater(Person &lhs, Person &rhs) const;
    vector<Person> handle_commands(vector<string> v);
    vector<Person> get_vec();

    Domain();
};
#endif // DOMAIN_H
