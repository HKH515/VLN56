#include "compareperson.h"

ComparePerson::ComparePerson()
{
    column = 0;
    mode = "";
}

ComparePerson::ComparePerson(int col, string m)
{
    column = col;
    mode = m;
}

bool ComparePerson::operator() (Person first, Person second)
{
    if (mode == "a")
    {
        switch(column)
        {
        case 0:
            return first.get_name() < second.get_name();
            break;
        case 1:
            return first.get_birthyear() < second.get_birthyear();
            break;
        case 2:
            return first.get_deathyear() < second.get_deathyear();
            break;
        case 3:
            return first.get_sex() < second.get_sex();
            break;
        }
    }
    else if (mode == "d")
    {
        switch(column)
        {
        case 0:
            return first.get_name() > second.get_name();
            break;
        case 1:
            return first.get_birthyear() > second.get_birthyear();
            break;
        case 2:
            return first.get_deathyear() > second.get_deathyear();
            break;
        case 3:
            return first.get_sex() > second.get_sex();
            break;
        }
    }
}
