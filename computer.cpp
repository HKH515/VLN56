#include "computer.h"

Computer::Computer()
{
    name = "";
    construction_year = 0;
    type = "";
    built = 0;
    description = "";
    // id = 0; Hættulegt?
}


string Computer::get_name()
{
    return name;
}

int Computer::get_contruction_year()
{
    return construction_year;
}

string Computer::get_type()
{
    return type;
}

bool Computer::get_built()
{
    return built;
}

int Computer::get_id()
{
    return id;
}

vector<Person*> Computer::get_pers_vec()
{
    return pers_vec;
}

void Computer::set_name(string s)
{
    name = s;
}

void Computer::set_construction_year(int y)
{
    construction_year = y;
}

void Computer::set_type(string s)
{
    type = s;
}

void Computer::set_built(bool b)
{
    built = b;
}

void Computer::set_description(string s)
{
    description = s;
}

void Computer::set_id(int i)
{
    id = i;
}
