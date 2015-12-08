#include "verifyinput.h"

VerifyInput::VerifyInput()
{
    input = "";
    prompt = "> ";
}

/* Name cannot be empty and can not have anything else than alphabet letters */
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

/* Profession can not be empty and can not have anything else than alphabet letters */
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

/* Birthyear needs to be a number >= 0 */
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

/* Deathyear needs to be a number >= 0 and can not be prior to birthyear */
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

/* Sex needs to be m (male), f (female) or o (other) */
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

/* Built can only be 0 (for No) or 1 (for Yes) */
string VerifyInput::verify_built()
{
    cin >> input;
    while (input != "0" && input != "1")
    {
        cout << "Invalid input, please write 0 (Not built) or 1 (Built): " << endl << prompt;
        cin >> input;
    }
    return input;
}

/* There are only three available tables in the database, 1 = Persons, 2 = Computers
 * 3 = Connections */
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

/* Possible to sort persons by any column except description */
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
/* Possible to sort Computers by any column except description */
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

/* Only allowed to sort ascending (a) or descending (d) */
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

/* Possible to search in all six columns for Persons */
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

/* Possible to search in all 5 columns for Computers */
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

/* Only allowed to choose either to enter a persons Id and get all computers connected
 * to that person (1), or a computer Id and get all persons connected to that computer (2) */
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

/* Only allowed digits */
bool VerifyInput::check_if_year(string input)
{
    for (unsigned int i = 0; i < input.length(); i++)
    {
        /* Check if each character of the string is a digit, if not return false */
        if (!isdigit(input.c_str()[i]))
        {
            return false;
        }
    }
    return true;
}

/* Only allowed alphabetic letters and spaces */
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

