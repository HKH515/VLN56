#include "domain.h"

Domain::Domain()
{
    data = new Data("data.sqlite");
}

vector<Person*> Domain::get_p_vec()
{
    return p_vec;
}

vector<Computer*> Domain::get_c_vec()
{
    return c_vec;
}

Domain::~Domain() {
    delete data;
    for (unsigned int i = 0; i < p_vec.size(); i++)
    {
        delete p_vec[i];
    }
    for (unsigned int i = 0; i < c_vec.size(); i++)
    {
        delete c_vec[i];
    }
}

// Parse function for queries returned from the data layer.
void Domain::parse_query_vector(vector<string> v, string table)
{
    if (table == "persons")
    {
        for (unsigned int i = 0; i < v.size(); i++)
        {
            string st = v[i];
            Person* p = new Person();
            // cut out the empty space in the beginning of the string
            st = st.substr(1, st.length());

            // find the name
            size_t position_beg = st.find("|");
            p->set_name(st.substr(0, position_beg));

            // find the profession
            size_t position_end = st.find("|", position_beg + 1);
            p->set_profession(st.substr(position_beg + 1, (position_end - position_beg - 1)));

            // find the description
            position_beg = st.find("|", position_end + 1);
            p->set_description(st.substr(position_end + 1, (position_beg - position_end - 1)));

            // find the birthyear
            position_end = st.find("|", position_beg + 1);
            string by = st.substr(position_beg + 1, (position_end - position_beg - 1));
            p->set_birthyear(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));

            // find the deathyear
            position_beg = st.find("|", position_end + 1);
            p->set_deathyear(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));

            // find the sex
            position_end = st.find("|", position_beg + 1);
            p->set_sex(st.substr(position_beg + 1, (position_end - position_beg - 1)));

            position_beg = st.find("|", position_end + 1);
            p->set_id(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));

            p_vec.push_back(p);
        }
    }
    else
    {
        for (unsigned int i = 0; i < v.size(); i++)
        {
            string st = v[i];
            Computer* c = new Computer();
            // cut out the empty space in the beginning of the string
            st = st.substr(1, st.length());

            // find the name
            size_t position_beg = st.find("|");
            c->set_name(st.substr(0, position_beg));

            // find the construction year
            size_t position_end = st.find("|", position_beg + 1);
            c->set_construction_year(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));

            // find the type
            position_beg = st.find("|", position_end + 1);
            c->set_type(st.substr(position_end + 1, (position_beg - position_end - 1)));

            // find if built
            position_end = st.find("|", position_beg + 1);
            string by = st.substr(position_beg + 1, (position_end - position_beg - 1));
            c->set_built(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));

            // find the description
            position_beg = st.find("|", position_end + 1);
            c->set_description(st.substr(position_end + 1, (position_beg - position_end - 1)));

            // find the id
            position_end = st.find("|", position_beg + 1);
            c->set_id(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));

            c_vec.push_back(c);
        }
    }
}

string Domain::parse_add_command(vector<string> v) {
    string st = " ";
    for (unsigned int i = 2; i < v.size(); i++) {
        st += v[i];
        st += "|";
    }
    return st;
}

void Domain::handle_commands(vector<string> v) {
    free_vector_memory(); /* Clear vector for new query */
    string command = v[0];

    if (command == "list") /* returns all entries in specified table */
    {
        get_list(v);
    }
    else if (command == "add") /* adds new entry in specified table */
    {
        add_entry(v);
    }
    else if (command == "search") /* search in the list */
    {
        search(v);
    }
}

void Domain::get_list(vector<string> v)
{
    string table = get_table(v[1]);
    string sort_column = get_column(v[2], table);
    string sort_method = get_sort_method(v[3]);
    parse_query_vector(data->readEntries(table, sort_column, sort_method), table);
}

void Domain::add_entry(vector<string> v)
{
    string table = get_table(v[1]);
    data->write(table, parse_add_command(v));
}

void Domain::search(vector<string> v)
{
    string table = get_table(v[1]);
    string query_column = get_column(v[2], table);
    string query_string = v[3];
    string sort_column = get_column(v[4], table);
    string sort_method = get_sort_method(v[5]);

    parse_query_vector(data->query(table, query_column, query_string, sort_column, sort_method), table);
}

string Domain::get_table(string s)
{
    if (s == "1")
    {
        return "persons";
    }
    else if (s == "2")
    {
        return "computers";
    }
    else
    {
        return "connections";
    }

}

string Domain::get_sort_method(string s)
{
    if (s == "a")
    {
        return "ASC";
    }
    else
    {
        return "DESC";
    }
}

string Domain::get_column(string s, string table)
{
    if (table == "persons")
    {
        if (s == "1")
        {
            return "name";
        }
        else if (s == "2")
        {
            return "birthyear";
        }
        else if (s == "3")
        {
            return "deathyear";
        }
        else if (s == "4")
        {
            return "sex";
        }
        else if (s == "5")
        {
            return "profession";
        }
        else if (s == "6")
        {
            return "description";
        }
        else
        {
            return "id";
        }
    }
    else if (table == "computers")
    {
        if (s == "1")
        {
            return "name";
        }
        else if (s == "2")
        {
            return "construction_year";
        }
        else if (s == "3")
        {
            return "type";
        }
        else if (s == "4")
        {
            return "built";
        }
        else if (s == "5")
        {
            return "description";
        }
        else
        {
            return "id";
        }
    }
}

void Domain::free_vector_memory()
{
    for (unsigned int i = 0; i < p_vec.size(); i++)
    {
        delete p_vec[i];
    }
    p_vec.clear();

    for (unsigned int i = 0; i < c_vec.size(); i++)
    {
        delete c_vec[i];
    }
    c_vec.clear();
}

