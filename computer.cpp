#include "computer.h"

Computer::Computer()
{
    name = "";
    construction_year = 0;
    type = "";
    built = 0;
    string description = "";
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
