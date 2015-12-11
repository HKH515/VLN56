#include "computerservice.h"

ComputerService::ComputerService()
{
    computer_repo = new ComputerRepository("data.sqlite", "computer_repo_connection");
}

string ComputerService::parse_add_command(vector<string> v)
{
    string st = " "; /* add space in front of the string */
    for (unsigned int i = 2; i < v.size(); i++)
    {
        st += v[i];
        st += "|"; /* add | after each vector element */
    }
    return st;
}

void ComputerService::parse_query_vector(vector<string> v)
{
    for (unsigned int i = 0; i < v.size(); i++)
    {
        string st = v[i];
        size_t position_beg = 0;
        size_t position_end = 0;
        /* cut out the empty space in the beginning of the string */
        st = st.substr(1, st.length());
        Computer* c = new Computer();

        /* find the name */
        position_end = st.find("|");
        c->set_name(st.substr(0, position_end - 1));

        /* find the construction year */
        position_beg = st.find("|", position_end + 1);
        c->set_construction_year(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));

        /* find the type */
        position_end = st.find("|", position_beg + 1);
        c->set_type(st.substr(position_beg + 1, (position_end - position_beg - 1)));

        /* find if built */
        position_beg = st.find("|", position_end + 1);
        c->set_built(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));

        /* find the description */
        position_end = st.find("|", position_beg + 1);
        c->set_description(st.substr(position_beg + 1, (position_end - position_beg - 1)));

        /* find the id */
        position_beg = st.find("|", position_end + 1);
        c->set_id(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));

        computer_vec.push_back(c);
    }
}

void ComputerService::free_vector_memory()
{
    for (unsigned int i = 0; i < computer_vec.size(); i++)
    {
        delete computer_vec[i];
    }
    computer_vec.clear();
}

void ComputerService::get_all_computers()
{
    parse_query_vector(computer_repo->read_entries());
}

void ComputerService::add_computer(vector<string> v)
{
    computer_repo->write(parse_add_command(v));
}

void ComputerService::search_computer(string column, string substring)
{
    /*if (column == "built")  Let the user enter specific strings if searching for built
    {
        substring = check_type_query(v[3]);
    }
    else
    {
        substring = v[3];
    }
    parse_query_vector(computer_repo->query(column, substring));*/
}

void ComputerService::remove_computer(string rem_id)
{
    computer_repo->remove("id", rem_id);
}
