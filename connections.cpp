#include "connections.h"

Connections::Connections()
{

}

int Connections::get_person_id()
{
    return person_id;
}

int Connections::get_computer_id()
{
    return computer_id;
}
void Connections::set_person_id(int p)
{
    person_id = p;
}

void Connections::set_computer_id(int c)
{
    computer_id = c;
}
