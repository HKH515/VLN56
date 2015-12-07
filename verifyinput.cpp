#include "verifyinput.h"

VerifyInput::VerifyInput()
{
    input = "";
    prompt = "> ";
}

string VerifyInput::verify_name()
{
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
    cin >> input;
    while (input != "m" && input != "f" && input != "o")
    {
        cout << "Invalid input, please write m, f or o: " << endl << prompt;
        cin >> input;
    }
    return input;
}

string VerifyInput::verify_built()
{
    cin >> input;
    while (input != "0" && input != "1")
    {
        cout << "Invalid input, please write 0 (false) or 1(true): " << endl << prompt;
        cin >> input;
    }
    return input;
}

string VerifyInput::verify_table()
{
    cin >> input;

    while(input != "1" && input != "2" && input != "3")
    {
        cout << "Invalid input, please choose again" << endl;
        cin >> input;
    }
    return input;
}

string VerifyInput::verify_sort_column_person()
{
    cin >> input;
    while ( (input != "1") && (input != "2") && (input != "3") && (input != "4") && (input != "5"))
    {
        cout << "This is not a valid choice, please choose again: " << endl << prompt;
        cin >> input;
    }
    return input;
}

string VerifyInput::verify_sort_column_comp()
{
    cin >> input;
    while ( (input != "1") && (input != "2") && (input != "3") && (input != "4"))
    {
        cout << "This is not a valid choice, please choose again: " << endl << prompt;
        cin >> input;
    }
    return input;

}

string VerifyInput::verify_order_of_sort()
{
    cin >> input;
    while (input != "a" && input != "d")
    {
        cout << "Invalid input! Enter a or d: "<< endl << prompt;
        cin >> input;
    }
    return input;
}

string VerifyInput::verify_search_column_person()
{
    cin >> input;
    while (input != "1" && input != "2" && input != "3" && input != "4" && input != "5" && input != "6")
    {
        cout << "This is not a valid choice, please choose again: " << endl << prompt;
        cin >> input;
    }
    return input;
}

string VerifyInput::verify_search_column_comp()
{
    cin >> input;
    while (input != "1" && input != "2" && input != "3" && input != "4" && input != "5")
    {
        cout << "This is not a valid choice, please choose again: " << endl << prompt;
        cin >> input;
    }
    return input;
}

string VerifyInput::verify_connections_column()
{
    cin >> input;
    while (input != "1" && input != "2")
    {
        cout << "This is not a valid choice, please choose again: " << endl << prompt;
        cin >> input;
    }
    return input;
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

