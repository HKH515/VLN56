#include "presentation.h"
#include <cstdlib>

presentation::presentation()
{
    d = new Domain();
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
    string inputs;
    cin >> inputs;
    vector<string> command_vec;
    string order_of_sort;
    string sort_by;

    // Put all letter to lowercase - ATH gera þegar error checka skipun?
    for (unsigned int i = 0; i < inputs.length(); i++)
    {
        inputs[i] = tolower(inputs[i]);
    }

    // Infinite while loop that receives and handles commands. If the user enters exit the while
    // loop terminates.
    do
    {
        command_vec.push_back(inputs);
        if(inputs == "add")
        {
            command_vec = parse_add();
            d->handle_commands(command_vec);
        }
        else if(inputs == "list")
        {
            sort_msg(1);
            cin >> sort_by;
            while ( (sort_by != "1") && (sort_by != "2") && (sort_by != "3") && (sort_by != "4") && (sort_by != "5")) {
                cout << "This is not a valid choice, please choose again" << endl;
                cin >> sort_by;
            }
            command_vec.push_back(sort_by);
            sort_msg(2);
            cin >> order_of_sort;
            // Error checking that the user put in either "a" or "d"
            while (order_of_sort != "a" && order_of_sort != "d")
            {
                cout << "Invalid input! Enter a or d"<< endl;
                cin >> order_of_sort;
            }
            command_vec.push_back(order_of_sort);
            cout << "Búin að pusha inn í vectorinn kalla á handle commands" << endl;

            d->handle_commands(command_vec);
            print_results(d);
        }
        else if(inputs == "search")
        {
            string search_column;
            sort_msg(3);
            cin >> search_column;
            // -----------------------Muna að gera tolower hér-------------------------
            while (search_column != "1" && search_column != "2" && search_column != "3" && search_column!= "4" && search_column!= "5" && search_column!= "6")
            {
                cout << "This is not a valid choice, please choose again" << endl;
                cin >> search_column;
            }
            command_vec.push_back(search_column);
            cout << "What substring do you want to search for?" << endl;
            string search_query;
            cin.ignore();
            getline(cin, search_query);
            command_vec.push_back(search_query);
            sort_msg(1);
            cin >> sort_by;
            while ( (sort_by != "1") && (sort_by != "2") && (sort_by != "3") && (sort_by != "4") && (sort_by != "5")) {
                cout << "This is not a valid choice, please choose again" << endl;
                cin >> sort_by;
            }
            command_vec.push_back(sort_by);
            sort_msg(2);
            cin >> order_of_sort;
            // Error checking that the user put in either "a" or "d"
            while (order_of_sort != "a" && order_of_sort != "d")
            {
                cout << "Invalid input! Enter a or d"<< endl;
                cin >> order_of_sort;
            }
            command_vec.push_back(order_of_sort);
            d->handle_commands(command_vec);
            print_results(d);
        }
        else if (inputs == "help") {

            cout << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "add: Add to the database" << endl;
            cout << "search: Search the list for prefered information" << endl;
            cout << "list: Display the whole list in prefered order" << endl;
            cout << "exit: Close the program" << endl;
            cout << "help: Open up the help menu" << endl;
            cout << "-------------------------------------------------" << endl;
        }

        if (inputs != "exit")
        {
            command_vec.clear();
            cin >> inputs;
        }
        else if(inputs == "exit")
        {
            exit(0);
        }
    }
    while(inputs != "exit");
    exit(0);

}

vector <string> presentation::parse_add()
{
    string input;
    vector<string> add_vec;
    add_vec.push_back("add");
    cout << "You will be asked to enter information about the person" << endl;
    cout << "Please write the name of the person: " << endl;
    cin.ignore();
    getline(cin, input);
    while (input.length() == 0)
    {
        cout << "Invalid input, please write the name of the person or '-'"<< endl;
        cin.ignore();
        getline(cin, input);
    }
    add_vec.push_back(input);
    cout << "Please write the profession of the person: " << endl;
    getline(cin, input);
    while (input.length() == 0)
    {
        cout << "Invalid input, please write the profession of the person or '-'"<< endl;
        cin.ignore();
        getline(cin, input);
    }
    add_vec.push_back(input);
    cout << "Please write some description of the person: " << endl;
    getline(cin, input);
    while (input.length() == 0)
    {
        cout << "Invalid input, please write the description of the person or '-'"<< endl;
        cin.ignore();
        getline(cin, input);
    }
    add_vec.push_back(input);
    cout << "Please write the year the person was born: " << endl;
    cin >> input;
    while (check_if_year(input) && input != "-")
    {
        cout << "Invalid input, please write a number > 0 or '-'" << endl;
        cin >> input;
    }
    add_vec.push_back(input);
    cout << "Please write the year the person died: " << endl;
    cin >> input;
    while (check_if_year(input) && input != "-")
    {
        cout << "Invalid input, please write a number > 0 or '-'" << endl;
        cin >> input;
    }
    add_vec.push_back(input);
    cout << "Please enter the sex of the person, m for male, f for female" << endl;
    cin >> input;
    // Check if valid input
    while (input != "m" && input != "f" && input != "-")
    {
        cout << "Invalid input, please write m, f or '-'" << endl;
        cin >> input;
    }
    add_vec.push_back(input);

    return add_vec;
}

bool presentation::check_if_year(string input)
{
    for (unsigned int i = 0; i < input.length(); i++)
    {
        // If the number is negative
        if (input[0] == '-')
        {
            return false;
        }
        if (!isdigit(stoi(&input[i])))
        {
            return false;
        }
    }

    return true;
}

void presentation::print_results(Domain *d)
{
    for (unsigned int i = 0; i < d->get_vec().size(); i++)
    {
        cout << "Name: " << d->get_vec()[i].get_name() << endl
             << "Born: " << d->get_vec()[i].get_birthyear() << endl
             << "Died: " << d->get_vec()[i].get_deathyear() << endl
             << "Sex: " << d->get_vec()[i].get_sex() << endl
             << "Profession: " << d->get_vec()[i].get_profession() << endl
             << "Description: " << d->get_vec()[i].get_description() << endl << endl;
    }

}

void presentation::sort_msg(int c) {
    if (c == 1) {
        cout << "What do you want to sort by? choose one of the following:" << endl
             <<"(1) Name" << endl
            << "(2) Profession" << endl
            << "(3) Birthyear" << endl
            << "(4) Deathyear" << endl
            << "(5) Sex" << endl;
    }
    else if (c == 2) {
        cout << "Do you want the information sorted in ascending or descending order? choose a/d" << endl;
    }
    else if (c == 3) {
        cout << "Choose what information you want to search for:" << endl
             <<"(1) Name" << endl
             <<"(2) Profession" << endl
             <<"(3) Description" << endl
             <<"(4) Birthyear" << endl
             <<"(5) Deathyear" << endl
             <<"(6) Sex" << endl;
    }
}
