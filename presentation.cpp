#include "presentation.h"

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
        cout << "list. View the list and sorts it" << endl;
        cout << "exit. Close the program" << endl;
        cout << "--------------------" << endl;
        cin >> inputs;
    }

    return inputs;
}

void presentation::choice(string inputs, Domain* d)
{
    // Put all letter to lowercase - ATH gera þegar error checka skipun
    for (unsigned int i = 0; i < inputs.length(); i++)
    {
        inputs[i] = tolower(inputs[i]);
    }
    vector<string> command_vec;
    vector<Person> result_vec;
    string input2;
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
            cin >> input2;
            // Error checking that the user put in either "a" or "d"
            while (input2 != "a" && input2 != "d")
            {
                cout << "Invalid input! Enter a or d"<< endl;
                cin >> input2;
            }
            command_vec.push_back(input2);
            result_vec = d->handle_commands(command_vec); // Ath hægt að setja þessa línu neðst?
            print_results(d);
        }
        else if(inputs == "search")
        {
            command_vec.push_back("search");
            cout << "In what information do you want to search? Please choose one of the following: name, profession, description, birthyear, deathyear, sex:" << endl;
            cin >> input2;
            // -----------------------Muna að gera tolower hér-------------------------
            while (input2 != "name" && input2 != "profession" && input2 != "description" && input2 != "birthyear" && input2 != "deathyear" && input2 != "sex")
            {
                cout << "Invalid command - please choose one of the following: name, profession, description, birthyear, deathyear, sex" << endl;
                cin >> input2;
            }
            command_vec.push_back(input2);
            cout << "What substring do you want to search for?" << endl;
            string search_query;
            cin.ignore();
            getline(cin, search_query);
            command_vec.push_back(search_query);
            cout << "Do you want the results sorted in ascending or descending order? Enter a for ascending, d for descending." << endl;
            string searching_order;
            cin >> searching_order;
            // Error checking that the user put in either "a" or "d"
            while (searching_order != "a" && searching_order != "d")
            {
                cout << "Invalid input! Enter a or d"<< endl;
                cin >> searching_order;
            }
            command_vec.push_back(searching_order);
            d->handle_commands(command_vec);
            print_results(d);
        }
        cin >> inputs;
    }
    while(inputs != "exit");

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
    cin.ignore();
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
