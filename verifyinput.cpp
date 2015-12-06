#include "verifyinput.h"

VerifyInput::VerifyInput()
{
    input = "";
    prompt = "> ";
    //d = new Domain();
}

VerifyInput::~VerifyInput()
{
    //delete d;
}

/* Error checking functions*/

string VerifyInput::verify_name()
{
    string input;
    cin.ignore();
    getline(cin, input);
    while (input.length() == 0 || !check_if_word(input))
    {
        cout << "Invalid input, please write the name of the person: "<< endl << prompt;
        cin.ignore();
        getline(cin, input);
    }
    return input;
}

string VerifyInput::verify_profession()
{
    string input;
    getline(cin, input);
    while (input.length() == 0 || !check_if_word(input))
    {
        cout << "Invalid input, please write the profession of the person: "<< endl << prompt;
        cin.ignore();
        getline(cin, input);
    }
    return input;
}

string VerifyInput::verify_birthyear()
{
    string input;
    cin >> input;
    while (!check_if_year(input))
    {
        cout << "Invalid input, please enter a year: "<< endl << prompt;
        cin >> input;
    }
    return input;
}

string VerifyInput::verify_deathyear(string birthy)
{
    string input;
    cin >> input;
    while (!check_if_year(input))
    {
        cout << "Invalid input, please enter a year: " << endl << prompt;
        cin >> input;
    }
    /* It is not allowed to add year of death that is before year of birth */

    while (stoi(input) < stoi(birthy))
    {
        while (!check_if_year(input))
        {
            cout << "Invalid input, please enter a year: " << endl << prompt;
            cin >> input;
        }

        if (!(stoi(input) == 0))
        {
            cout << "Year of death cannot be prior to year of birth, please enter a year (0 if still alive): " << endl << prompt;
            cin >> input;
        }
        else
        {
            break;
        }
    }
    return input;
}

string VerifyInput::verify_sex()
{
    string input;
    cin >> input;
    while (input != "m" && input != "f" && input != "o")
    {
        cout << "Invalid input, please write m, f or o: " << endl << prompt;
        cin >> input;
    }
    return input;
}

bool VerifyInput::verify_built()
{
    char input;
    cin >> input;
    while (input != 'y' && input != 'n')
    {
        cout << "Invalid input, please write y or n: " << endl << prompt;
        cin >> input;
    }
    if (input == 'y')
    {
        return true;
    }
    return false;
}

string VerifyInput::verify_table()
{
    string table;
    cin >> table;

    while(table != "1" && table != "2" && table != "3")
    {
        cout << "Invalid input, please choose again" << endl;
        cin >> table;
    }
    return table;
}

string VerifyInput::verify_sort_column_person(string sort_by)
{
    while ( (sort_by != "1") && (sort_by != "2") && (sort_by != "3") && (sort_by != "4") && (sort_by != "5"))
    {
        cout << "This is not a valid choice, please choose again: " << endl << prompt;
        cin >> sort_by;
    }
    return sort_by;
}

string VerifyInput::verify_sort_column_comp(string sort_by)
{
    while ( (sort_by != "1") && (sort_by != "2") && (sort_by != "3") && (sort_by != "4"))
    {
        cout << "This is not a valid choice, please choose again: " << endl << prompt;
        cin >> sort_by;
    }
    return sort_by;

}

string VerifyInput::verify_order_of_sort(string order)
{
    while (order != "a" && order != "d")
    {
        cout << "Invalid input! Enter a or d: "<< endl << prompt;
        cin >> order;
    }
    return order;
}

string VerifyInput::verify_search_column_person(string column)
{
    while (column != "1" && column != "2" && column != "3" && column!= "4" && column!= "5" && column!= "6")
    {
        cout << "This is not a valid choice, please choose again: " << endl << prompt;
        cin >> column;
    }
    return column;
}

string VerifyInput::verify_search_column_comp(string column)
{
    while (column != "1" && column != "2" && column != "3" && column!= "4" && column!= "5")
    {
        cout << "This is not a valid choice, please choose again: " << endl << prompt;
        cin >> column;
    }
    return column;

}



bool VerifyInput::check_if_year(string input)
{
    for (unsigned int i = 0; i < input.length(); i++)
    {
        // check if each character of the string is a digit, if not return false
        if (!isdigit(input.c_str()[i]))
        {
            return false;
        }
    }
    return true;
}

bool VerifyInput::check_if_word(string input)
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

