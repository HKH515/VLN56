#include "computer.h"

Computer::Computer()
{
    name = "";
    construction_year = 0;
    type = "";
    built = 0;
    string description = "";
}


string get_name()
{
    return name;
}

int get_contruction_year()
{
    return construction_year;
}

string get_type()
{
    return type;
}

bool get_built()
{
    return built;
}

void set_name(string s)
{
    name = s;
}

void set_construction_year(int y)
{
    construction_year = y;
}

void set_type(string s)
{
    type = s;
}

void set_built(bool b)
{
    built = b;
}
