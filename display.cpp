#include "display.h"

Display::Display()
{
    prompt = "> ";
}

/* Leads the user through the process of adding a Scientist to the database */
void Display::add_msg_person(int c)
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

/* Leads the user through the process of adding a computer to the database */
void Display::add_msg_computer(int c)
{
    if (c == 1)
    {
        cout << "Please enter the name of the computer: " << endl << prompt;
    }
    else if (c == 2)
    {
        cout << "Please enter the construction year of the computer: " << endl << prompt;
    }
    else if (c == 3)
    {
        cout << "Please enter the type of the computer: " << endl << prompt;
    }
    else if (c == 4)
    {
        cout << "Was the computer built?" << endl
             << "0 for No " << endl
             << "1 for Yes " << endl << prompt;
    }
    else if (c == 5)
    {
        cout << "Please write some description of the computer, can be left blank if desired: " << endl << prompt;
    }
}


void Display::sort_msg(int c)
{
    /* Sort choice menu if sorting persons */
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
    /* Sort choice menu if sorting computers */
    else if (c == 2)
    {
        cout << "What do you want to sort by? choose one of the following:" << endl
             <<"(1) Name" << endl
            << "(2) Construction Year" << endl
            << "(3) Type" << endl
            << "(4) Built" << endl
            << prompt;
    }
    /* Ask if order shoud be ascending or descending */
    else if (c == 3)
    {
        cout << "Do you want the information sorted in ascending or descending order? Choose a/d: " << endl << prompt;
    }
}

void Display::search_msg(int c)
{
    /* If searching in persons */
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
    /* If searching in computers */
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

void Display::table_msg(int c)
{
    /* Choice menu for adding to the database */
    if (c == 1)
    {
        cout << "Do you want to add a Computer Scientists, Computer or "
             << "connection between Computer Scientist and a Computer?" << endl
             << "(1) Computer Scientist" << endl
             << "(2) Computer" << endl
             << "(3) Connection between Computer Scientist and a Computer" << endl
             << prompt;
        return;
    }
    /* Choice menu for listing from the database */
    if (c == 2)
    {
        cout << "Do you want a list of Computer Scientists, Computers or "
             << "connections between Computer Scientist and a Computer?" << endl;
        cout << "(1) Computer Scientists" << endl
             << "(2) Computers" << endl
             << "(3) Connection between Computer Scientists and Computers" << endl
             << prompt;
    }
    /* Choice menu for searching in the database */
    if (c == 3)
    {
        cout << "Do you want to search in the database of Computer Scientists or Computers?" << endl;
        cout << "(1) Computer Scientists" << endl
             << "(2) Computers" << endl
             << prompt;
    }
    /* Choice menu for removing from the database */
    if (c == 4)
    {
        cout << "Do you want to remove a Computer Scientist, a Computer or "
             << "a connection between a Computer Scientist and a Computer?" << endl;
        cout << "(1) Computer Scientist" << endl
             << "(2) Computer" << endl
             << "(3) Connection between a Computer Scientist and a Computer" << endl
             << prompt;
    }
}

void Display::remove_msg(string c)
{
    /* If the user wants to remove a Computer Scientist */
    if (c == "1")
    {
        cout << "Below is a list of all Computer Scientists in the database,"
             << " please enter the Id of the Scientist you want to remove: " << endl;
    }
    /* If the user wants to remove a Computer */
    else if (c == "2")
    {
        cout << "Below is a list of all Computers in the database,"
             << " please enter the Id of the Computer you want to remove: " << endl;
    }
    /* If the user wants to remove a connection between a Scientist and a Computer */
    else if (c == "3")
    {
        cout << "Below is a list of all connections between Scientists and Computers "
             << "in the database. Please choose first the Id of the connection you want to remove: " << endl;
    }
    else if (c == "4")
    {
        cout << "Please enter the Id of the Computer Scientist you want to remove: " << endl;
    }
    else if ( c == "5")
    {
        cout << "Please enter the Id of the Computer you want to remove: " << endl;
    }
}

void Display::connection_msg(string c)
{
    /* Ask the user first if he wants to see all computers connected to a Scientist or
     * all Scientist connected to a computer */
    if (c == "0")
    {
        cout << "Do you want connections associated with a Computer Scientist or a Computer?" << endl
         << "(1) Computer Scientist" << endl
         << "(2) Computer" << endl;
    }
    /* If he chooses to see all computer connected to a certain Scientist */
    else if (c == "1")
    {
        cout << "Here below is a list of all Computer Scientists in the database, "
             << "please choose the Id of the Scientist you want to view connections: " << endl;
    }
    /* If the chooses to see all persons connected to a certain Computer */
    else if (c == "2")
    {
        cout << "Here below is a list of all Computer in the database, "
             << "please choose the Id of the Computer you want to view connections: " << endl;
    }
}

/* Help menu that displays all commands */
void Display::help_msg()
{
    cout << endl;
    cout << "-------------------------------------------------" << endl
         << "add: Add to the database" << endl
         << "search: Search the list for preferred information" << endl
         << "list: Display the whole list in preferred order" << endl
         << "remove: Remove an entry in the database" << endl
         << "connections: View specific connections" << endl
         << "exit: Close the program" << endl
         << "help: Displays this screen" << endl
         << "-------------------------------------------------" << endl;
}

/* Displays the result when using search/list and more commands for Persons*/
void Display::print_results_person(Domain *d)
{
    for (unsigned int i = 0; i < d->get_p_vec().size(); i++)
    {
        cout << "Name: " << d->get_p_vec()[i]->get_name() << endl
             << "Born: " << d->get_p_vec()[i]->get_birthyear() << endl;

        /* If the person is still alive the function displays NA */
        if (d->get_p_vec()[i]->get_deathyear() == 0)
        {
            cout << "Died: NA" << endl;
        }
        else
        {
            cout << "Died: " << d->get_p_vec()[i]->get_deathyear() << endl;
        }

        /* Displays Male, Female or Other instead of m, f or o */
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

/* Displays the result when using search/list and more commands for Computers*/
void Display::print_results_comp(Domain *d)
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
            cout << "Building Year: " << d->get_c_vec()[i]->get_construction_year() << endl;
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

        cout << "Description: " << d->get_c_vec()[i]->get_description() << endl << endl;
    }
}

void Display::print_connections_list(Domain *d)
{
    cout << "\t Persons \t\t\t\t Computers" << endl;
    for (unsigned int i = 0; i < d->get_p_vec().size(); i++)
    {
        cout << "Id: " << d->get_p_vec()[i]->get_id() << "\t"
             << "Name: " << d->get_p_vec()[i]->get_name() << "\t\t"
             << "Id: " << d->get_c_vec()[i]->get_id() << "\t"
             << "Name: " << d->get_c_vec()[i]->get_name() << endl;
    }
}

/* Display all Ids and Names of Persons and Computers in the database,
 * Used when removing, adding a connection and more */
void Display::display_valid_id(string c, Domain *d)
{
    /* Display all Ids and Names of Persons in the database */
    if (c == "1")
    {
        for (unsigned int i = 0; i < d->get_p_vec().size(); i++)
        {
            cout << "Id: " << d->get_p_vec()[i]->get_id() << "\t"
                 << "Name: " << d->get_p_vec()[i]->get_name() << endl;
        }
    }
    /* Display all Ids and Names of Computers in the database */
    else
    {
        for (unsigned int i = 0; i < d->get_c_vec().size(); i++)
        {
            cout << "Id: " << d->get_c_vec()[i]->get_id() << "\t"
                 << "Name: " << d->get_c_vec()[i]->get_name() << endl;
        }
    }
}
