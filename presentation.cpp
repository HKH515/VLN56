#include "presentation.h"
#include <cstdlib>

presentation::presentation()
{
    d = new Domain();
    prompt = "> ";
}

presentation::~presentation()
{
   delete d;
}

Domain* presentation::get_domain()
{
   return d;
}

void presentation::choice(Domain* d)
{
    string inputs, order_of_sort, sort_by, table;
    vector<string> command_vec;
    cin >> inputs;

    /* Infinite while loop that receives and handles commands. If the user enters exit the while
    loop terminates.*/
    do
    {
        /* Put all letter to lowercase, commands are not case sensitive */
        for (unsigned int i = 0; i < inputs.length(); i++)
        {
            inputs[i] = tolower(inputs[i]);
        }

        /* Put the command into the first element of the vector */
        command_vec.push_back(inputs);

        if(inputs == "add")
        {
            table_msg(1);
            table = verify_table();
            /* parse_add() leads the user through the add process */
            command_vec = parse_add(table);
            /* send the string to be added to the database */
            d->handle_commands(command_vec);
        }
        else if(inputs == "list")
        {
            /* The user needs to choose what he wants a list of */
            table_msg(2);
            table = verify_table();
            command_vec.push_back(table);
            /* Table of Computer Scientists */
            if (table == "1")
            {
                /* Ask the user what he wants to sort by */
                sort_msg(1);
                cin >> sort_by;
                /* check if the user's choice is valid */
                sort_by = verify_sort_column_person(sort_by);
                command_vec.push_back(sort_by);
            }
            else /* Table of Computers */
            {
                sort_msg(2);
                cin >> sort_by;
                sort_by = verify_sort_column_comp(sort_by);
                command_vec.push_back(sort_by);
            }

            /* Ask in what order the information should be sorted */
            sort_msg(3);
            cin >> order_of_sort;
            order_of_sort = verify_order_of_sort(order_of_sort);
            command_vec.push_back(order_of_sort);

            d->handle_commands(command_vec);
            print_results_person(d);
        }
        else if(inputs == "search")
        {
            string search_column, search_query;
            table_msg(3);
            table = verify_table();
            /* Ask the user what he wants to search in */
            if (table == "1")
            {
                search_msg(1);
                cin >> search_column;
                search_column = verify_search_column_person(search_column);
            }
            else
            {
                search_msg(2);
                cin >> search_column;
                search_column = verify_search_column_comp(search_column);
            }
            command_vec.push_back(search_column);

            /* Ask the user what he wants to search for */
            cout << "What substring do you want to search for?" << endl << prompt;
            cin.ignore();
            getline(cin, search_query);
            command_vec.push_back(search_query);

            // Ask the user what he wants to sort by
            if (table == "1")
            {
                sort_msg(1);
                cin >> sort_by;
                sort_by = verify_sort_column_person(sort_by);
                command_vec.push_back(sort_by);
            }
            else
            {
                sort_msg(2);
                cin >> sort_by;
                sort_by = verify_sort_column_comp(sort_by);
                command_vec.push_back(sort_by);
            }

            // Ask in what order the information should be sorted
            sort_msg(3);
            cin >> order_of_sort;
            order_of_sort = verify_order_of_sort(order_of_sort);
            command_vec.push_back(order_of_sort);

            d->handle_commands(command_vec);

            if (table == "1")
            {
                if (d->get_p_vec().size() == 0)
                {
                    cout << "No results found." << endl;
                }
                else
                {
                   print_results_person(d);
                }

            }
            else
            {
                print_results_comp(d);
            }

        }
        else if (inputs == "help")
        {
            help_msg();
        }
        else if (inputs == "exit")
        {
            exit(0);
        }
        else
        {
            cout << "You entered an invalid command, type help for list of supported commands." << endl;
        }

        /* If we continue running the program we clear the command vector and construct a new one for
           next command */
        if (inputs != "exit")
        {
            command_vec.clear();
            cout << prompt;
            cin >> inputs;
        }

    }
    while(inputs != "exit");
    exit(0);
}

vector <string> presentation::parse_add(string choice) {
    string input;
    vector<string> add_vec;
    add_vec.push_back("add");
    if (choice == "1")
    {
        cout << "You will be asked to enter information about the person." << endl;

        add_msg_person(1);
        input = verify_name();
        add_vec.push_back(input);

        add_msg_person(2);
        input = verify_profession();
        add_vec.push_back(input);

        add_msg_person(3);
        getline(cin, input);
        add_vec.push_back(input);

        add_msg_person(4);
        input = verify_birthyear();
        add_vec.push_back(input);

        add_msg_person(5);
        input = verify_deathyear(input);
        add_vec.push_back(input);

        add_msg_person(6);
        input = verify_sex();
        add_vec.push_back(input);
    }
    else
    {
        cout << "You will be asked to enter information about the computer." << endl;

        add_msg_computer(1);
        input = verify_name();
        add_vec.push_back(input);

        add_msg_computer(2);
        input = verify_birthyear();
        add_vec.push_back(input);

        add_msg_computer(3);
        cin.ignore();
        getline(cin, input); /* Á eftir að búa til error check hér */
        add_vec.push_back(input);

        add_msg_computer(4);
        input = verify_built();
        add_vec.push_back(input);

        add_msg_computer(5);
        cin.ignore();
        getline(cin, input);
        add_vec.push_back(input);

    }

    return add_vec;
}


bool presentation::check_if_year(string input)
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

bool presentation::check_if_word(string input)
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

void presentation::print_results_person(Domain *d)
{
    for (unsigned int i = 0; i < d->get_p_vec().size(); i++)
    {
        cout << "Name: " << d->get_p_vec()[i]->get_name() << endl
             << "Born: " << d->get_p_vec()[i]->get_birthyear() << endl;

        // If the person is still alive the function displays NA
        if (d->get_p_vec()[i]->get_deathyear() == 0)
        {
            cout << "Died: NA" << endl;
        }
        else
        {
             cout << "Died: " << d->get_p_vec()[i]->get_deathyear() << endl;
        }

        if (d->get_p_vec()[i]->get_sex() == "m")
        {
            cout << "Sex: Male" << endl;
        }
        else if (d->get_p_vec()[i]->get_sex() == "f")
        {
            cout << "Sex: Female" << endl;
        }
        else if (d->get_p_vec()[i]->get_sex() == "o")
        {
            cout << "Sex: Other" << endl;
        }
        cout << "Profession: " << d->get_p_vec()[i]->get_profession() << endl
             << "Description: " << d->get_p_vec()[i]->get_description() << endl << endl;
    }

}

void presentation::print_results_comp(Domain *d)
{

}

/* Error checking functions*/

string presentation::verify_name()
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

string presentation::verify_profession()
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

string presentation::verify_birthyear()
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

string presentation::verify_deathyear(string birthy)
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

string presentation::verify_sex()
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

bool presentation::verify_built()
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

string presentation::verify_table()
{
    string table;
    cin >> table;

    while(table != "1" && table != "2")
    {
        cout << "Invalid input, please choose again" << endl;
        cin >> table;
    }
    return table;
}

string presentation::verify_sort_column_person(string sort_by)
{
    while ( (sort_by != "1") && (sort_by != "2") && (sort_by != "3") && (sort_by != "4") && (sort_by != "5"))
    {
        cout << "This is not a valid choice, please choose again: " << endl << prompt;
        cin >> sort_by;
    }
    return sort_by;
}

string presentation::verify_sort_column_comp(string sort_by)
{
    while ( (sort_by != "1") && (sort_by != "2") && (sort_by != "3") && (sort_by != "4"))
    {
        cout << "This is not a valid choice, please choose again: " << endl << prompt;
        cin >> sort_by;
    }
    return sort_by;

}

string presentation::verify_order_of_sort(string order)
{
    while (order != "a" && order != "d")
    {
        cout << "Invalid input! Enter a or d: "<< endl << prompt;
        cin >> order;
    }
    return order;
}

string presentation::verify_search_column_person(string column)
{
    while (column != "1" && column != "2" && column != "3" && column!= "4" && column!= "5" && column!= "6")
    {
        cout << "This is not a valid choice, please choose again: " << endl << prompt;
        cin >> column;
    }
    return column;
}

string presentation::verify_search_column_comp(string column)
{
    while (column != "1" && column != "2" && column != "3" && column!= "4" && column!= "5")
    {
        cout << "This is not a valid choice, please choose again: " << endl << prompt;
        cin >> column;
    }
    return column;

}

/* Display Functions*/

void presentation::add_msg_person(int c)
{
    if (c == 1)
    {
          cout << "Please write the name of the person: " << endl << prompt;
    }
    else if (c == 2)
    {
         cout << "Please write the profession of the person: " << endl << prompt;
    }
    else if (c == 3)
    {
        cout << "Please write a description of the person, can be left blank if you desire: " << endl << prompt;
    }
    else if (c == 4)
    {
         cout << "Please write the year that the person was born: " << endl << prompt;
    }
    else if (c == 5)
    {
        cout << "Please write the year that the person died, if the person is still alive enter 0: " << endl << prompt;
    }
    else if (c == 6)
    {
        cout << "Enter the sex of the person: " << endl << "(m) Male\n" << "(f) Female\n" << "(o) Other" << endl << prompt;
    }

}

void presentation::add_msg_computer(int c)
{
    if (c == 1)
    {
        cout << "Please enter the name of the computer: " << endl;
    }
    else if (c == 2)
    {
        cout << "Please enter the construction year of the computer: " << endl;
    }
    else if (c == 3)
    {
        cout << "Please enter the type of the computer: " << endl;
    }
    else if (c == 4)
    {
        cout << "Was the computer built? (y/n)" << endl;
    }
    else if (c == 5)
    {
        cout << "Please write some description of the computer, can be left blank if desired: " << endl;
    }

}

void presentation::sort_msg(int c)
{
    if (c == 1)
    {
        cout << "What do you want to sort by? choose one of the following:" << endl
             <<"(1) Name" << endl
            << "(2) Birthyear" << endl
            << "(3) Deathyear" << endl
            << "(4) Sex" << endl
            << "(5) Profession" << endl
            << prompt;
    }
    else if (c == 2)
    {
        cout << "What do you want to sort by? choose one of the following:" << endl
             <<"(1) Name" << endl
            << "(2) Construction Year" << endl
            << "(3) Type" << endl
            << "(4) Built" << endl
            << prompt;
    }
    else if (c == 3)
    {
        cout << "Do you want the information sorted in ascending or descending order? Choose a/d: " << endl << prompt;
    }
}

void presentation::search_msg(int c)
{
    if (c == 1)
    {
        cout << "Choose what information you want to search for:" << endl
             << "(1) Name" << endl
             << "(2) Birthyear" << endl
             << "(3) Deathyear" << endl
             << "(4) Sex" << endl
             << "(5) Profession" << endl
             << "(6) Description" << endl
             << prompt;
    }
    else if (c == 2)
    {
        cout << "Choose what information you want to search for:" << endl
             << "(1) Name" << endl
             << "(2) Construction Year" << endl
             << "(3) Type" << endl
             << "(4) Built" << endl
             << "(5) Description" << endl
             << prompt;
    }

}

void presentation::table_msg(int c)
{
    if (c == 1)
    {
        cout << "Do you want to add a Computer Scientists or a Computer?" << endl
             << "(1) Computer Scientist" << endl
             << "(2) Computer" << endl;
    }
    if (c == 2)
    {
        cout << "Do you want a list of Computer Scientists or Computers?" << endl
             << "(1) Computer Scientists" << endl
             << "(2) Computers" << endl;
    }
    if (c == 3)
    {
        cout << "Do you want to search in the database of Computer Scientists or Computers?" << endl
         << "(1) Computer Scientists" << endl
         << "(2) Computers" << endl;
    }
}

void presentation::help_msg()
{
    cout << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "add: Add to the database" << endl;
    cout << "search: Search the list for preferred information" << endl;
    cout << "list: Display the whole list in preferred order" << endl;
    cout << "exit: Close the program" << endl;
    cout << "help: Displays this screen" << endl;
    cout << "-------------------------------------------------" << endl;
}
