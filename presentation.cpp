#include "presentation.h"

presentation::presentation()
{
    d = new Domain();
    v = new VerifyInput();
    msg = new Display();
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
    string inputs, order_of_sort, sort_by, table, kind_of_id;
    int id;
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
            msg->table_msg(1);
            table = v->verify_table();
            /* parse_add() leads the user through the add process */
            command_vec = parse_add(table);
            /* send the string to be added to the database */
            d->handle_commands(command_vec);
        }
        else if(inputs == "list")
        {
            /* The user needs to choose what he wants a list of */
            msg->table_msg(2);
            table = v->verify_table();
            command_vec.push_back(table);
            /* Table of Computer Scientists */
            if (table == "1")
            {
                /* Ask the user what he wants to sort by */
                msg->sort_msg(1);
                /* Receive input and check if the user's choice is valid */
                sort_by = v->verify_sort_column_person();
                command_vec.push_back(sort_by);
            }
            else /* Table of Computers */
            {
                msg->sort_msg(2);
                sort_by = v->verify_sort_column_comp();
                command_vec.push_back(sort_by);
            }
            
            /* Ask in what order the information should be sorted */
            msg->sort_msg(3);
            order_of_sort = v->verify_order_of_sort();
            command_vec.push_back(order_of_sort);

            d->handle_commands(command_vec);
            if (table == "1")
            {
                msg->print_results_person(d);
            }
            else if (table == "2")
            {
                msg->print_results_comp(d);
            }

        }
        else if(inputs == "search")
        {
            string search_column, search_query;
            msg->table_msg(3);
            table = v->verify_table();
            command_vec.push_back(table);
            /* Ask the user what he wants to search in */
            if (table == "1")
            {
                msg->search_msg(1);
                search_column = v->verify_search_column_person();
            }
            else
            {
                msg->search_msg(2);
                search_column = v->verify_search_column_comp();
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
                msg->sort_msg(1);
                sort_by = v->verify_sort_column_person();
                command_vec.push_back(sort_by);
            }
            else
            {
                msg->sort_msg(2);
                sort_by = v->verify_sort_column_comp();
                command_vec.push_back(sort_by);
            }
            
            // Ask in what order the information should be sorted
            msg->sort_msg(3);
            order_of_sort = v->verify_order_of_sort();
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
                    msg->print_results_person(d);
                }
            }
            else
            {
                if (d->get_c_vec().size() == 0)
                {
                    cout << "No results found." << endl;
                }
                else
                {
                    msg->print_results_comp(d);
                }
            }
        }
        else if (inputs == "remove")
        {
            command_vec = remove_entry();
            d->handle_commands(command_vec);

        }
        else if (inputs == "connections")
        {
            msg->connection_msg("0");
            kind_of_id = v->verify_connections_column();
            command_vec.push_back(kind_of_id);
            msg->connection_msg(kind_of_id);
            get_list(kind_of_id);
            cin >> id;
            string valid_id;
            valid_id = verify_id(kind_of_id, id);
            command_vec.push_back(valid_id);
            d->handle_commands(command_vec);
            if (kind_of_id == "1")
            {
                cout << "The computers connected to the person with Id = " << id << " are: " << endl;
                msg->print_results_comp(d);
            }
            else
            {
                cout << "The persons connected to the computer with Id = " << id << " are: " << endl;
                msg->print_results_person(d);
            }
        }

        else if (inputs == "help")
        {
            msg->help_msg();
        }
        else if (inputs == "exit")
        {
            exit(0);
        }
        else
        {
            cout << "You entered an invalid command, type help for a list of supported commands." << endl;
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
    add_vec.clear();
    add_vec.push_back("add");
    if (choice == "1")
    {
        add_vec.push_back("1");
        cout << "You will be asked to enter information about the person." << endl;

        msg->add_msg_person(1);
        input = v->verify_name();
        add_vec.push_back(input);

        msg->add_msg_person(2);
        input = v->verify_profession();
        add_vec.push_back(input);

        msg->add_msg_person(3);
        getline(cin, input);
        add_vec.push_back(input);

        msg->add_msg_person(4);
        input = v->verify_birthyear();
        add_vec.push_back(input);

        msg->add_msg_person(5);
        input = v->verify_deathyear(input);
        add_vec.push_back(input);

        msg->add_msg_person(6);
        input = v->verify_sex();
        add_vec.push_back(input);
    }
    else if (choice == "2")
    {
        add_vec.push_back("2");
        cout << "You will be asked to enter information about the computer." << endl;

        msg->add_msg_computer(1);
        input = v->verify_name();
        add_vec.push_back(input);

        msg->add_msg_computer(2);
        input = v->verify_birthyear();
        add_vec.push_back(input);

        msg->add_msg_computer(3);
        cin.ignore();
        getline(cin, input); /* Á eftir að búa til error check hér */
        add_vec.push_back(input);

        msg->add_msg_computer(4);
        input = v->verify_built();
        add_vec.push_back(input);

        msg->add_msg_computer(5);
        cin.ignore();
        getline(cin, input);
        add_vec.push_back(input);

    }
    else /* If the user wants to add a connection between a Scientist and a Computer */
    {
        add_vec = add_connection();
    }
    return add_vec;
}

vector<string> presentation::add_connection()
{
    int input;
    cout << "Below is a list of all Scientist in the database, "
         << "please choose the id of the Scientist you want to connect to a computer."
         << endl << prompt;

    /* Get list of all the scientist in the database, ordered after id in ascending order */
    vector<string> list_vec;
    get_list("1");
    cin >> input;
    string p_id = verify_id("1", input); /* Verify that the input id is valid */
    cout << "Below is a list of all Computer in the database, "
         << "please choose the id of the Computer you want to connect to the previously chosen Scientist."
         << endl << prompt;
    get_list("2");
    cin >> input;
    string c_id = verify_id("2", input); /* Verify that the input id is valid */
    //list_vec.clear();
    list_vec.push_back("add");
    list_vec.push_back("3");
    list_vec.push_back(p_id);
    list_vec.push_back(c_id);
    return list_vec;
}

void presentation::get_list(string table)
{
    vector<string> comm_vec;
    /* Get list of all Computer Scientists */
    if (table == "1")
    {
        comm_vec.push_back("list");
        comm_vec.push_back(table); /* Table of persons */
        comm_vec.push_back("7"); /* Sort after id */
        comm_vec.push_back("a"); /* Ascending order */
        d->handle_commands(comm_vec);
        msg->display_valid_id("1", d); /* Display list */
    }
    /* Get list of all Computers */
    else if (table == "2")
    {
        comm_vec.push_back("list");
        comm_vec.push_back(table); /* Table of computers */
        comm_vec.push_back("6"); /* Sort after id */
        comm_vec.push_back("a"); /* Ascending order */
        d->handle_commands(comm_vec);
        msg->display_valid_id("2", d); /* Display list */
    }
}

vector<string> presentation::remove_entry()
{
    int id;
    vector<string> rem;
    msg->table_msg(4);
    string table = v->verify_table();
    msg->remove_msg(table);
    get_list(table);
    rem.push_back("remove");
    rem.push_back(table);
    rem.push_back("7");
    cin >> id;
    rem.push_back(verify_id(table, id));
    return rem;
}

vector<int> presentation::get_ids(int c)
{
    vector<int> ids;
    if (c == 1)
    {
        for (unsigned int i = 0; i < d->get_p_vec().size(); i++)
        {
            ids.push_back(d->get_p_vec()[i]->get_id());
        }
    }
    else
    {
        for (unsigned int i = 0; i < d->get_c_vec().size(); i++)
        {
            ids.push_back(d->get_c_vec()[i]->get_id());
        }
    }
    return ids;
}

string presentation::verify_id(string table, int input)
{
    bool id_not_ok = true;
    vector <int> ids;

    if (table == "1") /*Get valid persons id */
    {
        ids = get_ids(1);
    }
    else /* Get valid Computers id */
    {
        ids = get_ids(2);
    }
    while (id_not_ok)
    {
        for (int i = 0; i < ids.size(); i++)
        {
            if (input == ids[i])
            {
                id_not_ok = false;
                break;
            }
        }
        if (id_not_ok)
        {
            cout << "Invalid input, please choose again: "<< endl << prompt;
            cin >> input;
        }
    }
    return int_to_string(input);
}

string presentation::int_to_string(int number)
{
    stringstream ss;
    ss << number;
    string value = ss.str();
    return value;
}
