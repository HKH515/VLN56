#include "presentation.h"
#include <cstdlib>

presentation::presentation()
{
    d = new Domain();
}
Domain* presentation::get_domain()
{
   return d;
}

string presentation::input()
{
    string inputs;
    cin >> inputs;

    if(inputs == "help")
    {
        cout << endl;
        cout << "--------------------" << endl;
        cout << "add. Add names and other info" << endl;
        cout << "search. search the list for info" << endl;
        cout << "list. View the list and sort it" << endl;
        cout << "exit. Close the program" << endl;
        cout << "help. Print this screen" << endl;
        cout << "--------------------" << endl;
        cin >> inputs;
    }

    return inputs;
}

void presentation::choice(string inputs, Domain* d)
{
    // Put all letter to lowercase - ATH gera þegar error checka skipun?
    for (unsigned int i = 0; i < inputs.length(); i++)
    {
        inputs[i] = tolower(inputs[i]);
    }
    vector<string> command_vec;
    string order_of_sort;
    do
    {
        if(inputs == "add")
        {
            command_vec.push_back("add");
            command_vec = parse_add();
            d->handle_commands(command_vec);
        }
        else if(inputs == "list")
        {
            command_vec.push_back("list");
            cout << "Do you want the list sorted in ascending or descending order? Enter a for ascending, d for descending." << endl;
            cin >> order_of_sort;
            // Error checking that the user put in either "a" or "d"
            while (order_of_sort != "a" && order_of_sort != "d")
            {
                cout << "Invalid input! Enter a or d"<< endl;
                cin >> order_of_sort;
            }
            command_vec.push_back(order_of_sort);
            d->handle_commands(command_vec); // Ath hægt að setja þessa línu neðst?
            print_results(d);
        }
        else if(inputs == "search")
        {
            string search_column;
            command_vec.push_back("search");
            cout << "In what information do you want to search? Please choose one of the following: name, profession, description, birthyear, deathyear, sex:" << endl;
            cin >> search_column;
            // -----------------------Muna að gera tolower hér-------------------------
            while (search_column != "name" && search_column != "profession" && search_column != "description" && search_column!= "birthyear" && search_column!= "deathyear" && search_column!= "sex")
            {
                cout << "Invalid command - please choose one of the following: name, profession, description, birthyear, deathyear, sex" << endl;
                cin >> search_column;
            }
            command_vec.push_back(search_column);
            cout << "What substring do you want to search for?" << endl;
            string search_query;
            cin.ignore();
            getline(cin, search_query);
            command_vec.push_back(search_query);
            cout << "Do you want the results sorted in ascending or descending order? Enter a for ascending, d for descending." << endl;
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
    cout << "You will be asked to enter information about the person, if you want to leave out information enter '-' when asked."<< endl;
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
