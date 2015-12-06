#include "presentation.h"



presentation::presentation()
{
    d = new Domain();
    v = new VerifyInput();
    prompt = "> ";
}

presentation::~presentation()
{
    delete d;
    delete v;
}

Domain* presentation::get_domain()
{
    return d;
}

void presentation::choice()
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
            table = v->verify_table();
            /* parse_add() leads the user through the add process */
            command_vec = parse_add(table);
            /* send the string to be added to the database */
            d->handle_commands(command_vec);
        }
        else if(inputs == "list")
        {
            /* The user needs to choose what he wants a list of */
            table_msg(2);
            table = v->verify_table();
            command_vec.push_back(table);
            /* Table of Computer Scientists */
            if (table == "1")
            {
                /* Ask the user what he wants to sort by */
                sort_msg(1);
                cin >> sort_by;
                /* check if the user's choice is valid */
                sort_by = v->verify_sort_column_person(sort_by);
                command_vec.push_back(sort_by);
            }
            else /* Table of Computers */
            {
                sort_msg(2);
                cin >> sort_by;
                sort_by = v->verify_sort_column_comp(sort_by);
                command_vec.push_back(sort_by);
            }
            
            /* Ask in what order the information should be sorted */
            sort_msg(3);
            cin >> order_of_sort;
            order_of_sort = v->verify_order_of_sort(order_of_sort);
            command_vec.push_back(order_of_sort);
            
            d->handle_commands(command_vec);
            print_results_person();
        }
        else if(inputs == "search")
        {
            string search_column, search_query;
            table_msg(3);
            table = v->verify_table();
            /* Ask the user what he wants to search in */
            if (table == "1")
            {
                search_msg(1);
                cin >> search_column;
                search_column = v->verify_search_column_person(search_column);
            }
            else
            {
                search_msg(2);
                cin >> search_column;
                search_column = v->verify_search_column_comp(search_column);
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
                sort_by = v->verify_sort_column_person(sort_by);
                command_vec.push_back(sort_by);
            }
            else
            {
                sort_msg(2);
                cin >> sort_by;
                sort_by = v->verify_sort_column_comp(sort_by);
                command_vec.push_back(sort_by);
            }
            
            // Ask in what order the information should be sorted
            sort_msg(3);
            cin >> order_of_sort;
            order_of_sort = v->verify_order_of_sort(order_of_sort);
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
                    print_results_person();
                }
            }
            else
            {
                print_results_comp();
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
        add_vec.push_back("1");
        cout << "You will be asked to enter information about the person." << endl;
        
        add_msg_person(1);
        input = v->verify_name();
        add_vec.push_back(input);
        
        add_msg_person(2);
        input = v->verify_profession();
        add_vec.push_back(input);
        
        add_msg_person(3);
        getline(cin, input);
        add_vec.push_back(input);
        
        add_msg_person(4);
        input = v->verify_birthyear();
        add_vec.push_back(input);
        
        add_msg_person(5);
        input = v->verify_deathyear(input);
        add_vec.push_back(input);
        
        add_msg_person(6);
        input = v->verify_sex();
        add_vec.push_back(input);
    }
    else if (choice == "2")
    {
        add_vec.push_back("2");
        cout << "You will be asked to enter information about the computer." << endl;
        
        add_msg_computer(1);
        input = v->verify_name();
        add_vec.push_back(input);
        
        add_msg_computer(2);
        input = v->verify_birthyear();
        add_vec.push_back(input);
        
        add_msg_computer(3);
        cin.ignore();
        getline(cin, input); /* Á eftir að búa til error check hér */
        add_vec.push_back(input);
        
        add_msg_computer(4);
        input = v->verify_built();
        add_vec.push_back(input);
        
        add_msg_computer(5);
        cin.ignore();
        getline(cin, input);
        add_vec.push_back(input);
        
    }
    else /* If the user wants to add a connection between a Scientist and a Computer */
    {
        add_vec = add_connection();
        
    }
    
    for (unsigned int i = 0; i < add_vec.size(); i++)
    {
        cout << "add_vec[" << i << "] : " << add_vec[i] << endl;
    }
    return add_vec;
}




void presentation::print_results_person()
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

void presentation::print_results_comp()
{
    for (unsigned int i = 0; i < d->get_c_vec().size(); i++)
    {
        cout << "Name: " << d->get_c_vec()[i]->get_name() << endl;

        if (d->get_c_vec()[i]->get_construction_year() == 0) // eða NULL?
        {
            cout << "Building Year: Not known" << endl;
        }
        else
        {
            cout << " Building Year: " << d->get_c_vec()[i]->get_construction_year() << endl;
        }

        cout << "Type: " << d->get_c_vec()[i]->get_type() << endl;

        if (d->get_c_vec()[i]->get_built() == 1)
        {
            cout << "Built: Yes" << endl;
        }
        else
        {
            cout << "Built: No" << endl;
        }
    }
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

vector<string> presentation::add_connection()
{
    cout << "Below is a list of all Scientist in the database"
         << ",please choose the id of the Scientist you want to connect to a computer." << endl;

    /* Get list of all the scientist in the database, ordered after id in ascending order */
    vector<string> list_vec;
    list_vec.push_back("list");
    list_vec.push_back("1"); /* Table of persons */
    list_vec.push_back("7"); /* Sort after id */
    list_vec.push_back("a"); /* Ascending order */
    d->handle_commands(list_vec);
    display_valid_id(1); /*Display valid persons and their id */
    string p_id = verify_person_id(); /* Verify that the input id is valid */
    list_vec.clear();
    list_vec.push_back("list");
    list_vec.push_back("2"); /* Table of computers */
    list_vec.push_back("5"); /* Sort after id */
    list_vec.push_back("a"); /* Ascending order */
    d->handle_commands(list_vec);
    display_valid_id(2);
    string c_id = verify_computer_id(); /* Verify that the input id is valid */
    list_vec.clear();
    list_vec.push_back("add");
    list_vec.push_back("3");
    list_vec.push_back(p_id);
    list_vec.push_back(c_id);
    return list_vec;

}

void presentation::display_valid_id(int c)
{
    if (c == 1)
    {
        for (unsigned int i = 0; i < d->get_p_vec().size(); i++)
        {
            cout << "Id: " << d->get_p_vec()[i]->get_id() << endl
                 << "Name: " << d->get_p_vec()[i]->get_name() << endl;
        }
    }
    else
    {
        for (unsigned int i = 0; i < d->get_c_vec().size(); i++)
        {
            cout << "Id: " << d->get_c_vec()[i]->get_id() << endl
                 << "Name: " << d->get_c_vec()[i]->get_name() << endl;
        }
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
        cout << "Do you want to add a Computer Scientists, Computer or "
             << "connection between Computer Scientist and a Computer?" << endl
             << "(1) Computer Scientist" << endl
             << "(2) Computer" << endl
             << "(3) Connection between Computer Scientist and a Computer" << endl;
        return;
    }
    if (c == 2)
    {
        cout << "Do you want a list of Computer Scientists, Computers or "
             << "connections between Computer Scientist and a Computer?" << endl;
        cout << "(1) Computer Scientists" << endl
             << "(2) Computers" << endl
             << "(3) Connection between Computer Scientists and Computers" << endl;
    }
    if (c == 3)
    {
        cout << "Do you want to search in the database of Computer Scientists or Computers?" << endl;
        cout << "(1) Computer Scientists" << endl
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

string presentation::verify_person_id()
{
    int input;
    while (1)
    {
        cin >> input;
        if ((input >= 1) && (input <= d->get_p_vec().size()))
        {
            break;
        }
        cout << "Invalid input, please choose again: "<< endl;

    }
    stringstream ss;
    ss << input;
    string value = ss.str();
    return value;
}

string presentation::verify_computer_id()
{
    int input;
    while (1)
    {
        cin >> input;
        if ((input >= 1) && (input <= d->get_c_vec().size()))
        {
            break;
        }
        cout << "Invalid input, please choose again: "<< endl;

    }
    stringstream ss;
    ss << input;
    string value = ss.str();
    return value;
}
