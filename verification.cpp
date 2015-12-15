#include "verification.h"

Verification::Verification()
{

}

// Name and profession can only be letters and spaces
bool Verification::verify_name(string name_input)
{
    if (name_input.length() == 0 || !check_if_word(name_input))
    {
        return false;
    }
    return true;
}

// Profession can only be letters and spaces
bool Verification::verify_profession(string profession_input)
{
    if (profession_input.length() == 0 || !check_if_word(profession_input))
    {
        return false;
    }
    return true;
}

// Can only be non negative number
bool Verification::verify_year(string year_input)
{
    return check_if_year(year_input) && stoi(year_input) >= 0;
}


// Checks if all letters are either alphabet letters or spaces
bool Verification::check_if_word(string input)
{
    for (unsigned int i = 0; i < input.length(); i++)
    {
        if (!isalpha(input.c_str()[i]) && !isspace(input.c_str()[i]))
        {
            return false;
        }
    }
    return true;
}

//  Checks if all digits
bool Verification::check_if_year(string input)
{
    for (unsigned int i = 0; i < input.length(); i++)
    {
        // Check if each character of the string is a digit, if not return false
        if (!isdigit(input.c_str()[i]))
        {
            return false;
        }
    }
    return true;
}
