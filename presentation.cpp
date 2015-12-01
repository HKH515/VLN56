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
    string inputs, order_of_sort, sort_by;
    vector<string> command_vec;
    cin >> inputs;

    // Put all letter to lowercase
    for (unsigned int i = 0; i < inputs.length(); i++) {
        inputs[i] = tolower(inputs[i]);
    }

    // Infinite while loop that receives and handles commands. If the user enters exit the while
    // loop terminates.
    do
    {
        // Put the command into the first element of the vector
        command_vec.push_back(inputs);

        if(inputs == "add") {
            // parse_add() leads the user through the add process
            command_vec = parse_add();
            // send the string to be added to the database
            d->handle_commands(command_vec);
        }
        else if(inputs == "list") {
            // Ask the user what he wants to test by
            sort_msg(1);
            cin >> sort_by;
            // check if the user's choice is valid
            while ( (sort_by != "1") && (sort_by != "2") && (sort_by != "3") && (sort_by != "4") && (sort_by != "5")) {
                cout << "This is not a valid choice, please choose again: " << endl << prompt;
                cin >> sort_by;
            }
            command_vec.push_back(sort_by);

            // Ask in what order the information should be sorted
            sort_msg(2);
            cin >> order_of_sort;
            // Error checking that the user put in either "a" or "d"
            while (order_of_sort != "a" && order_of_sort != "d") {
                cout << "Invalid input! Enter a or d: "<< endl << prompt;
                cin >> order_of_sort;
            }
            command_vec.push_back(order_of_sort);

            d->handle_commands(command_vec);
            print_results(d);
        }
        else if(inputs == "search") {
            // Ask the user what he wants to test by
            string search_column;
            sort_msg(3);
            cin >> search_column;
            while (search_column != "1" && search_column != "2" && search_column != "3" && search_column!= "4" && search_column!= "5" && search_column!= "6") {
                cout << "This is not a valid choice, please choose again: " << endl << prompt;
                cin >> search_column;
            }
            command_vec.push_back(search_column);

            // Ask the user what he wants to search for
            cout << "What substring do you want to search for?" << endl << prompt;
            string search_query;
            cin.ignore();
            getline(cin, search_query);
            command_vec.push_back(search_query);

            // Ask the user what he wants to sort by
            sort_msg(1);
            cin >> sort_by;
            while ( (sort_by != "1") && (sort_by != "2") && (sort_by != "3") && (sort_by != "4") && (sort_by != "5")) {
                cout << "This is not a valid choice, please choose again: " << endl << prompt;
                cin >> sort_by;
            }
            command_vec.push_back(sort_by);

            // Ask in what order the information should be sorted
            sort_msg(2);
            cin >> order_of_sort;

            // Error checking that the user put in either "a" or "d"
            while (order_of_sort != "a" && order_of_sort != "d") {
                cout << "Invalid input! Enter a or d: "<< endl << prompt;
                cin >> order_of_sort;
            }
            command_vec.push_back(order_of_sort);

            d->handle_commands(command_vec);
            if (d->get_vec().size() == 0) {
                cout << "No results found" << endl;
            }
            print_results(d);
        }
        else if (inputs == "help") {

            cout << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "add: Add to the database" << endl;
            cout << "search: Search the list for preferred information" << endl;
            cout << "list: Display the whole list in preferred order" << endl;
            cout << "exit: Close the program" << endl;
            cout << "help: Displays this screen" << endl;
            cout << "-------------------------------------------------" << endl;
        }
        else if (inputs == "exit") {
            exit(0);
        }
        else {
            cout << "You entered an invalid command, type help for list of supported commands." << endl;
        }

        /* If we continue running the program we clear the command vector and construct a new one for
           next command */
        if (inputs != "exit") {
            command_vec.clear();
            cout << prompt;
            cin >> inputs;
        }

    }
    while(inputs != "exit");
    exit(0);
}

vector <string> presentation::parse_add()
{
    string input, birthyear_check;
    vector<string> add_vec;
    add_vec.push_back("add");

    cout << "You will be asked to enter information about the person" << endl;
    cout << "Please write the name of the person: " << endl << prompt;
    cin.ignore();
    getline(cin, input);
    while (input.length() == 0 || !check_if_word(input)) {
        cout << "Invalid input, please write the name of the person: "<< endl << prompt;
        cin.ignore();
        getline(cin, input);
    }
    add_vec.push_back(input);

    cout << "Please write the profession of the person: " << endl << prompt;
    getline(cin, input);
    while (input.length() == 0 || !check_if_word(input)) {
        cout << "Invalid input, please write the profession of the person: "<< endl << prompt;
        cin.ignore();
        getline(cin, input);
    }
    add_vec.push_back(input);

    cout << "Please write a description of the person, can be left blank if you desire: " << endl << prompt;
    getline(cin, input);
    add_vec.push_back(input);

    cout << "Please write the year that the person was born: " << endl << prompt;
    cin >> birthyear_check;
    while (!check_if_year(input)) {
        cout << "Invalid input, please enter a year: "<< endl << prompt;
        cin >> input;
    }
    add_vec.push_back(birthyear_check);

    cout << "Please write the year that the person died, if the person is still alive enter 0: " << endl << prompt;
    cin >> input;
    while (!check_if_year(input)) {
        cout << "Invalid input, please enter a year: " << endl << prompt;
        cin >> input;
    }
    /* It is not allowed to add year of death that is before year of birth */
    if (!(stoi(input) == 0)) {
        while (stoi(input) < stoi(birthyear_check)) {
            cout << "Year of death cannot be prior to year of birth, please enter a year (0 if still alive): " << endl << prompt;
            cin >> input;

            while (!check_if_year(input)) {
                cout << "Invalid input, please enter a year: " << endl << prompt;
                cin >> input;
            }
        }
    }
    add_vec.push_back(input);

    cout << "Enter the sex of the person: " << endl << "(m) Male\n" << "(f) Female\n" << "(o) Other" << endl << prompt;
    cin >> input;
    // Check if valid input
    while (input != "m" && input != "f" && input != "o") {
        cout << "Invalid input, please write m, f " << endl << prompt;
        cin >> input;
    }
    add_vec.push_back(input);

    return add_vec;
}

bool presentation::check_if_year(string input)
{
    for (unsigned int i = 0; i < input.length(); i++) {
        // check if each character of the string is a digit, if not return false
        if (!isdigit(input.c_str()[i])) {
            return false;
        }
    }
    return true;
}

bool presentation::check_if_word(string input) {
    for (unsigned int i = 0; i < input.length(); i++) {
        if (!isalpha(input.c_str()[i]) && !isspace(input.c_str()[i])) {
            return false;
        }
    }
    return true;
}

void presentation::print_results(Domain *d)
{
    for (unsigned int i = 0; i < d->get_vec().size(); i++) {
        cout << "Name: " << d->get_vec()[i]->get_name() << endl
             << "Born: " << d->get_vec()[i]->get_birthyear() << endl;

        // If the person is still alive the function displays NA
        if (d->get_vec()[i]->get_deathyear() == 0) {
            cout << "Died: NA" << endl;
        }
        else {
             cout << "Died: " << d->get_vec()[i]->get_deathyear() << endl;
        }

        if (d->get_vec()[i]->get_sex() == "m") {
            cout << "Sex: Male" << endl;
        }
        else if (d->get_vec()[i]->get_sex() == "f") {
            cout << "Sex: Female" << endl;
        }
        else if (d->get_vec()[i]->get_sex() == "o") {
            cout << "Sex: Other" << endl;
        }
        cout << "Profession: " << d->get_vec()[i]->get_profession() << endl
             << "Description: " << d->get_vec()[i]->get_description() << endl << endl;
    }

}

void presentation::sort_msg(int c) {
    if (c == 1) {
        cout << "What do you want to sort by? choose one of the following:" << endl
             <<"(1) Name" << endl
            << "(2) Birthyear" << endl
            << "(3) Deathyear" << endl
            << "(4) Sex" << endl
            << "(5) Profession" << endl
            << prompt;
    }
    else if (c == 2) {
        cout << "Do you want the information sorted in ascending or descending order? Choose a/d: " << endl << prompt;
    }
    else if (c == 3) {
        cout << "Choose what information you want to search for:" << endl
             << "(1) Name" << endl
             << "(2) Profession" << endl
             << "(3) Description" << endl
             << "(4) Birthyear" << endl
             << "(5) Deathyear" << endl
             << "(6) Sex" << endl
             << prompt;
    }
}
