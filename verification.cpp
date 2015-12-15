#include "verification.h"

Verification::Verification()
{

}

// Name and profession can only be letters and spaces
bool Verification::verify_name(string name_input)
{
    cout << "inni í verify name" << endl;
    if (name_input.length() == 0 || !check_if_word(name_input))
    {
        return false;
    }
    return true;
}

// Profession can only be letters and spaces
bool Verification::verify_profession(string profession_input)
{
    cout << "inni í verify profession" << endl;
    if (profession_input.length() == 0 || !check_if_word(profession_input))
    {
        return false;
    }
    return true;
}

// Can only be non negative number
bool Verification::verify_year(string year_input)
{
    cout << "inni í verify year" << endl;
    return check_if_year(year_input) && stoi(year_input) >= 0;
}

bool Verification::verify_deathyear(string birthyear_input, string deathyear_input)
{
    cout << "inni í verify death_year" << endl;
    int birthyear = stoi(birthyear_input);
    int deathyear = stoi(deathyear_input);

    if (!check_if_year(deathyear_input) || stoi(deathyear_input) < 0)
    {
        return false;
    }
    if (birthyear > deathyear)
    {
        return false;
    }
    return true;
}

// Checks if all letters are either alphabet letters or spaces
bool Verification::check_if_word(string input)
{
    cout << "inni í check if word" << endl;
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
    cout << "inni í check if yeear" << endl;
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
