#ifndef COMPAREPERSON_H
#define COMPAREPERSON_H

#include "person.h"

class ComparePerson
{
private:
    int column; // After what do you want to sort
    string mode; // ascending or descending

public:
    ComparePerson();
    ComparePerson(int col, string m);
    bool operator() (Person first, Person second);
};

#endif // COMPAREPERSON_H
