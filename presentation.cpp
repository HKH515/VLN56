#include "presentation.h"

presentation::presentation()
{
    d = new Domain();
    v = new VerifyInput();
    msg = new Display();
    prompt = "> ";
}

/* Free allocated memory */
presentation::~presentation()
{
    delete d;
    delete v;
    delete msg;
}

Domain* presentation::get_domain()
{
    return d;
}

void presentation::choice()
{
    string inputs, order_of_sort, sort_by, table, kind_of_id, right_id;
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

        /* Handles Add command */
        if(inputs == "add")
        {
            msg->table_msg(1); /* Display choice menu of tables to user */
            table = v->verify_table(); /* Receive input and verify it */
            /* parse_add() leads the user through the add process */
            command_vec = parse_add(table);
            /* send the string to be added to the database */
            d->handle_commands(command_vec);
        }
        /* Handles List command */
        else if(inputs == "list")
        {
            /* The user needs to choose what he wants a list of, Scientists, Computers or Connections */
            msg->table_msg(2);
            table = v->verify_table();
            command_vec.push_back(table);
            if (table == "1") /* Computer Scientists */
            {
                /* Ask the user what he wants to sort by */
                msg->sort_msg(1);
                /* Receive input and check if the user's choice is valid */
                sort_by = v->verify_sort_column_person();
                command_vec.push_back(sort_by);
            }
            else if (table == "2") /* Computers */
            {
                msg->sort_msg(2);
                sort_by = v->verify_sort_column_comp();
                command_vec.push_back(sort_by);
            }
           /* The user can choose ascending/descending when listing Persons or Computer
            * Not when listing connections, then they will always appear in ascending order after Name */
            if (table != "3")
            {
                msg->sort_msg(3);
                order_of_sort = v->verify_order_of_sort();
                command_vec.push_back(order_of_sort);
            }

            /* Send the command to the domain layer */
            d->handle_commands(command_vec);

            /* Printing results from the domain layer */
            if (table == "1")
            {
                msg->print_results_person(d, 1); /* List of Scientists*/
            }
            else if (table == "2")
            {
                msg->print_results_comp(d, 1); /* List of Computers */
            }
            else
            {
                msg->print_connections_list(d); /* List of Connections */
            }

        }
        /*Handles Search command */
        else if(inputs == "search")
        {
            string search_column, search_query;
            msg->table_msg(3); /* Display a choice menu for the user */
            table = v->verify_table(); /* Receive table choice and verify it */
            command_vec.push_back(table);
            /* Ask the user what he wants to search in */
            if (table == "1") /* Computer Scientists */
            {
                msg->search_msg(1); /* List columns that are available to search in*/
                search_column = v->verify_search_column_person();
            }
            else /* Computers */
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
            
            /* Ask the user what he wants to sort the results from search by */
            if (table == "1") /* Computer Scientists */
            {
                msg->sort_msg(1);
                sort_by = v->verify_sort_column_person();
                command_vec.push_back(sort_by);
            }
            else /* Computers */
            {
                msg->sort_msg(2);
                sort_by = v->verify_sort_column_comp();
                command_vec.push_back(sort_by);
            }
            
            /* Ask in what order the information should be sorted (a/d) */
            msg->sort_msg(3);
            order_of_sort = v->verify_order_of_sort();
            command_vec.push_back(order_of_sort);
            
            /* Send vector of command to the domain layer to be handled */
            d->handle_commands(command_vec);
            
            /* Display results */
            if (table == "1")
            {
                msg->print_results_person(d, 2);
            }
            else
            {
                msg->print_results_comp(d, 2);
            }
        }
        /* Handle remove command */
        else if (inputs == "remove")
        {
            command_vec = remove_entry();
            d->handle_commands(command_vec);

        }
        /* Handle connections command */
        else if (inputs == "connections")
        {
            /* Ask the user if he wants to view a Person and all its connected Computers or a Computer and all
             * its connected Persons */
            msg->connection_msg("0");
            kind_of_id = v->verify_connections_column(); /* Receive input and verify that it is valid */
            command_vec.push_back(kind_of_id);
            msg->connection_msg(kind_of_id);
            get_list(kind_of_id); /* Display list of all valid Id's from the database */
            right_id = valid_id(kind_of_id); /* Receive and verify users inputed Id */
            command_vec.push_back(right_id);
            d->handle_commands(command_vec); /* Send the command to the domain layer */

            /* Print results */
            if (kind_of_id == "1")
            {
                cout << "The computers connected to the person with Id = " << right_id << " are: " << endl;
                msg->print_results_comp(d, 3);
            }
            else
            {
                cout << "The persons connected to the computer with Id = " << right_id << " are: " << endl;
                msg->print_results_person(d, 3);
            }
        }
        /* Handle help command */
        else if (inputs == "help")
        {
            msg->help_msg();
        }
        /* Handle exit command */
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
    /* Adding að Computer Scientist */
    if (choice == "1")
    {
        add_vec.push_back("1");
        cout << "You will be asked to enter information about the person." << endl;

        /* Receiving and verifying name of Scientist from user */
        msg->add_msg_person(1);
        input = v->verify_name();
        add_vec.push_back(input);

        /* Receiving and verifying profession of Scientist from user */
        msg->add_msg_person(2);
        input = v->verify_profession();
        add_vec.push_back(input);

        /* Receiving description of Scientist */
        msg->add_msg_person(3);
        getline(cin, input);
        add_vec.push_back(input);

        /* Receiving and verifying birthyear of Scientist */
        msg->add_msg_person(4);
        input = v->verify_birthyear();
        add_vec.push_back(input);

        /* Receiving and verifying deathyear of Scientist */
        msg->add_msg_person(5);
        input = v->verify_deathyear(input);
        add_vec.push_back(input);

        /* Receiving and verifying sex of Scientist */
        msg->add_msg_person(6);
        input = v->verify_sex();
        add_vec.push_back(input);
        msg->add_msg_person(7);
    }
    /* Adding a Computer */
    else if (choice == "2")
    {
        add_vec.push_back("2");
        cout << "You will be asked to enter information about the computer." << endl;

        /* Receiving and verifying name of Computer */
        msg->add_msg_computer(1);
        input = v->verify_name();
        add_vec.push_back(input);

        /* Receiving and verifying construction year of Computer */
        msg->add_msg_computer(2);
        input = v->verify_birthyear();
        add_vec.push_back(input);

        /* Receiving and verifying type of computer */
        msg->add_msg_computer(3);
        input = v->verify_name();
        add_vec.push_back(input);

        /* Receiving and verifying if the Computer was built */
        msg->add_msg_computer(4);
        input = v->verify_built();
        add_vec.push_back(input);

        /* Receiving description of the Computer */
        msg->add_msg_computer(5);
        cin.ignore();
        getline(cin, input);
        add_vec.push_back(input);
        msg->add_msg_computer(6);
    }
    /* Adding a Connection */
    else /* If the user wants to add a connection between a Scientist and a Computer */
    {
        add_vec = add_connection();
        msg->add_msg_connection(3);
    }
    return add_vec;
}

vector<string> presentation::add_connection()
{
    vector<string> list_vec;
    msg->add_msg_connection(1);
    /* Get list of all the scientist in the database, ordered after id in ascending order */
    get_list("1");
    string p_id = valid_id("1"); /* Verify that the input id is valid */
    /* Get list of all computers in the database, ordered after id in ascending order */
    msg->add_msg_connection(2);
    get_list("2");
    string c_id = valid_id("2"); /* Verify that the input id is valid */
    list_vec.push_back("add");
    list_vec.push_back("3"); /* Table of connections */
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
        cout << prompt;
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
        cout << prompt;
    }
    /* Get list of all connections */
    else
    {
        comm_vec.push_back("list");
        comm_vec.push_back("3");
        d->handle_commands(comm_vec);
        msg->print_connections_list(d);
    }
}

vector<string> presentation::remove_entry()
{
    vector<string> rem;
    msg->table_msg(4); /* Display a choice menu for the user to choose what to remove */
    string table = v->verify_table();
    msg->remove_msg(table);
    get_list(table);
    rem.push_back("remove");
    rem.push_back(table);
    /* If he wants to remove either a Scientist or a Computer */
    if (table != "3")
    {
        rem.push_back("7");
        rem.push_back(valid_id(table));
    }
    /* If he wants to remove a Connection */
    else
    {
        msg->remove_msg("4");
        rem.push_back(valid_id("1"));
        msg->remove_msg("5");
        rem.push_back(valid_id("2"));
    }
    return rem;
}

vector<string> presentation::get_ids(int c)
{
    vector<string> ids;
    /* Push all Ids of Computer Scientist in the database into a vector */
    if (c == 1)
    {
        for (unsigned int i = 0; i < d->get_p_vec().size(); i++)
        {
            ids.push_back(int_to_string(d->get_p_vec()[i]->get_id()));
        }
    }
    /* Push all Ids of Computers in the database into a vector */
    else
    {
        for (unsigned int i = 0; i < d->get_c_vec().size(); i++)
        {
            ids.push_back(int_to_string(d->get_c_vec()[i]->get_id()));
        }
    }
    return ids;
}

string presentation::valid_id(string table)
{
    bool id_not_ok = true;
    vector <string> ids;
    string input;

    if (table == "1") /* Get all Persons id in the database*/
    {
        ids = get_ids(1);
    }
    else /* Get all Computers id in the database */
    {
        ids = get_ids(2);
    }
    cin >> input;
    while (id_not_ok)
    {
        for (unsigned int i = 0; i < ids.size(); i++)
        {
            /* If chosen Id matches an id in the vector, return*/
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
    return input;
}

/* Returns the integer variable number as a string using stringstream*/
string presentation::int_to_string(int number)
{
    stringstream ss;
    ss << number;
    string value = ss.str();
    return value;
}
