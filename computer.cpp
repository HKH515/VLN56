#include "computer.h"

Computer::Computer()
{
    name = "";
    construction_year = 0;
    type = "";
    built = 0;
    description = "";
    id = 0;
}

string Computer::get_name()
{
    return name;
}

int Computer::get_construction_year()
{
    return construction_year;
}

string Computer::get_type()
{
    return type;
}

int Computer::get_built()
{
    return built;
}

string Computer::get_description()
{
    return description;
}

int Computer::get_id()
{
    return id;
}

vector<string> Computer::get_vec()
{
    return per_associated;
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

void Computer::set_built(int b)
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

void Computer::push_back_vec(string s)
{
    per_associated.push_back(s);
}

unsigned long Computer::get_vec_size()
{
    return per_associated.size();
}
