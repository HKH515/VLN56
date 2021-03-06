#include "person.h"

using namespace std;

Person::Person()
{
    name = "";
    birth_year = 0;
    death_year = 0;
    sex = "";
    description = "";
    profession = "";
    id = 0;
}

/* set functions */
void Person::set_name(string n)
{
    name = n;
}

void Person::set_birthyear(int y)
{
    birth_year = y;
}

void Person::set_deathyear(int y)
{
    death_year = y;
}

void Person::set_sex(string s)
{
    sex = s;
}

void Person::set_description(string s)
{
    description = s;
}

void Person::set_profession(string p)
{
    profession = p;
}

void Person::set_id(int i)
{
    id = i;
}

/* get functions */
string Person::get_name()
{
    return name;
}

int Person::get_birthyear()
{
    return birth_year;
}

int Person::get_deathyear()
{
    return death_year;
}

string Person::get_sex()
{
    return sex;
}

string Person::get_description()
{
    return description;
}

string Person::get_profession()
{
    return profession;
}

int Person::get_id()
{
    return id;
}

