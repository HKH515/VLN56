#include "computerservice.h"

ComputerService::ComputerService()
{
    computer_repo = new ComputerRepository("data.sqlite", "computer_repo_connection");
}

ComputerService::~ComputerService()
{
    free_vector_memory();
    delete computer_repo;
}

string ComputerService::parse_add_command(vector<string> v)
{
    string st = " "; /* add space in front of the string */
    for (unsigned int i = 0; i < v.size(); i++)
    {
        st += v[i];
        st += "|"; /* add | after each vector element */
    }
    return st;
}

void ComputerService::parse_query_vector(vector<string> v)
{
    free_vector_memory();
    for (unsigned int i = 0; i < v.size(); i++)
    {
        string st = v[i];
        size_t position_beg = 0;
        size_t position_end = 0;
        /* cut out the empty space in the beginning of the string */
        st = st.substr(1, st.length());

        position_beg = st.find("|");
        string kind = st.substr(0, position_beg);
        Computer* c = new Computer();

        // find the name
        position_end = st.find("|", position_beg + 1);
        c->set_name(st.substr(position_beg + 1, position_end - position_beg - 1));

        // find the construction year
        position_beg = st.find("|", position_end + 1);
        c->set_construction_year(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));

        // find the type
        position_end = st.find("|", position_beg + 1);
        c->set_type(st.substr(position_beg + 1, (position_end - position_beg - 1)));

        // find if built
        position_beg = st.find("|", position_end + 1);
        c->set_built(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));

        // find the description
        position_end = st.find("|", position_beg + 1);
        c->set_description(st.substr(position_beg + 1, (position_end - position_beg - 1)));

        // find the id
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
    if (column == "Construction Year")
    {
        column = "construction_year";
    }

    if (column == "Built")
    {
        substring = check_search_substring(substring);
    }
    parse_query_vector(computer_repo->query(column, substring));
}

void ComputerService::remove_computer(int id)
{
    stringstream ss;
    ss << id;
    string str_id = ss.str();
    computer_repo->remove("id", str_id);
}

vector<Computer *> ComputerService::get_computer_vec()
{
    return computer_vec;
}

Computer* ComputerService::find_chosen_computer(string chosen_name)
{
    for (unsigned int i = 0; i < computer_vec.size(); i++)
    {
        if (computer_vec[i]->get_name() == chosen_name)
        {
            return computer_vec[i];
        }
    }
    return NULL;
}


string ComputerService::check_search_substring(string subst)
{
    if (subst == "No" || subst == "no" || subst == "n" || subst == "N")
    {
        return "0";
    }
    else if (subst == "Yes" || subst == "yes" || subst == "y" || subst == "Y")
    {
        return "1";
    }
    else
    {
        return subst;
    }
}
