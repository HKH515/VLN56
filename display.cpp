#include "display.h"

Display::Display()
{
    prompt = "> ";
}

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
        cout << "Was the computer built? 0 for No, 1 for Yes " << endl << prompt;
    }
    else if (c == 5)
    {
        cout << "Please write some description of the computer, can be left blank if desired: " << endl << prompt;
    }

}

void Display::sort_msg(int c)
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

void Display::search_msg(int c)
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

void Display::table_msg(int c)
{
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
    if (c == 2)
    {
        cout << "Do you want a list of Computer Scientists, Computers or "
             << "connections between Computer Scientist and a Computer?" << endl;
        cout << "(1) Computer Scientists" << endl
             << "(2) Computers" << endl
             << "(3) Connection between Computer Scientists and Computers" << endl
             << prompt;
    }
    if (c == 3)
    {
        cout << "Do you want to search in the database of Computer Scientists or Computers?" << endl;
        cout << "(1) Computer Scientists" << endl
             << "(2) Computers" << endl
             << prompt;
    }
    if (c == 4)
    {
        cout << "Do you want to remove a Computer Scientist or a Computer?" << endl;
        cout << "(1) Computer Scientist" << endl
             << "(2) Computer" << endl
             << prompt;

    }
}

void Display::help_msg()
{
    cout << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "add: Add to the database" << endl;
    cout << "search: Search the list for preferred information" << endl;
    cout << "list: Display the whole list in preferred order" << endl;
    cout << "remove: Remove an entry in the database" << endl;
    cout << "exit: Close the program" << endl;
    cout << "help: Displays this screen" << endl;
    cout << "-------------------------------------------------" << endl;
}

void Display::print_results_person(Domain *d)
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

        cout << "Description: " << d->get_c_vec()[i]->get_description() << endl;
    }
}

void Display::display_valid_id(string c, Domain *d)
{
    if (c == "1")
    {
        for (unsigned int i = 0; i < d->get_p_vec().size(); i++)
        {
            cout << "Id: " << d->get_p_vec()[i]->get_id() << "\t"
                 << "Name: " << d->get_p_vec()[i]->get_name() << endl;
        }
    }
    else
    {
        for (unsigned int i = 0; i < d->get_c_vec().size(); i++)
        {
            cout << "Id: " << d->get_c_vec()[i]->get_id() << "\t"
                 << "Name: " << d->get_c_vec()[i]->get_name() << endl;
        }
    }
}
