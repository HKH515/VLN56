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

/* Parse function for queries returned from the data layer. */
void Domain::parse_query_vector(vector<string> v)
{
    for (unsigned int i = 0; i < v.size(); i++)
    {
        string st = v[i];
        size_t position_beg = 0;
        size_t position_end = 0;
        /* cut out the empty space in the beginning of the string */
        st = st.substr(1, st.length());

        /* find if it is a computer or a person */
        position_beg = st.find("|");
        string kind = st.substr(0, position_beg);

        if (kind == "0")
        {
            Person* p = new Person();

            /* find the name */
            position_end = st.find("|", position_beg + 1);
            p->set_name(st.substr(position_beg + 1, position_end - position_beg - 1));

            /* find the profession */
            position_beg = st.find("|", position_end + 1);
            p->set_profession(st.substr(position_end + 1, (position_beg - position_end - 1)));

            /* find the description */
            position_end = st.find("|", position_beg + 1);
            p->set_description(st.substr(position_beg + 1, (position_end - position_beg - 1)));

            /* find the birthyear */
            position_beg = st.find("|", position_end + 1);
            p->set_birthyear(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));

            /* find the deathyear */
            position_end = st.find("|", position_beg + 1);
            p->set_deathyear(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));

            /* find the sex */
            position_beg = st.find("|", position_end + 1);
            p->set_sex(st.substr(position_end + 1, (position_beg - position_end - 1)));

            /* find the id */
            position_end = st.find("|", position_beg + 1);
            p->set_id(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));

            p_vec.push_back(p);
        }
        else if (kind == "1")
        {
            Computer* c = new Computer();

            /* find the name */
            position_end = st.find("|", position_beg + 1);
            c->set_name(st.substr(position_beg + 1, position_end - position_beg - 1));

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

            c_vec.push_back(c);
        }
    }
}

string Domain::parse_add_command(vector<string> v) {
    string st = " "; /* add space in front of the string */
    for (unsigned int i = 2; i < v.size(); i++) { /* add | after each vector element */
        st += v[i];
        st += "|";
    }
    return st;
}

void Domain::handle_commands(vector<string> v) {
    free_vector_memory(); /* Clear vector for new query */
    string command = v[0];

    if (command == "list") /* Returns all entries in specified table */
    {
        get_list(v);
    }
    else if (command == "add") /* Adds new entry in specified table */
    {
        add_entry(v);
    }
    else if (command == "search") /* Search in the list */
    {
        search(v);
    }
    else if (command == "remove") /* Remove entry from database */
    {
        remove_entry(v);
    }
    else if (command == "connections") /* Get all Scientists/computers associated with certain Computer/scientist */
    {
        get_connected(v);
    }
}

void Domain::get_connected(vector<string> v)
{
    string table = get_table(v[1]);
    if (table == "persons")
    {
        string id = v[2];
        parse_query_vector(data->get_conn_assoc_with_person(id)); /* Gets all computers associated with the scientist */
    }
    else
    {
        string id = v[2];
        parse_query_vector(data->get_conn_assoc_with_computer(id)); /* Get all scientists associated with the computer */
    }
}

void Domain::get_list(vector<string> v)
{
    string table = get_table(v[1]);
    if (table == "connections")
    {
        parse_query_vector(data->get_conn_all_computers()); /* Get all computers ordered by connections*/
        parse_query_vector(data->get_conn_all_persons()); /* Get all scientist ordered by connections */
    }
    else /* If list of scientists/computers then get all and sort by requerments */
    {
        string sort_column = get_column(v[2], table);
        string sort_method = get_sort_method(v[3]);
        parse_query_vector(data->read_entries(table, sort_column, sort_method));
    }
}

void Domain::add_entry(vector<string> v)
{
    string table = get_table(v[1]);
    data->write(table, parse_add_command(v)); /* Add to the database */
}

void Domain::search(vector<string> v)
{
    string table = get_table(v[1]);
    string query_column = get_column(v[2], table);
    string query_string;
    if (query_column == "built") /* Let the user enter specific strings if searching for built */
    {
        query_string = check_type_query(v[3]);
    }
    else if (query_column == "sex") /* Let the user enter specific strings if searching for sex */
    {
        query_string = check_sex_query(v[3]);
    }
    else
    {
        query_string = v[3];
    }
    string sort_column = get_column(v[4], table);
    string sort_method = get_sort_method(v[5]);
    parse_query_vector(data->query(table, query_column, query_string, sort_column, sort_method));
}

void Domain::remove_entry(vector<string> v)
{
    string table = get_table(v[1]);
    if (table == "connections")
    {
        string pers_id = v[2];
        string comp_id = v[3];
        data->remove_conn(pers_id, comp_id);
    }
    else
    {
        string query_column = get_column(v[2], table);
        string rem_id = v[3];
        data->remove(table, query_column, rem_id);
    }
}

/* Returns the name of right table in database to work with */
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

/* Returns the required sort method */
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

/* Returns the name of the requried column to sort by or search in */
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

/* This function lets the user enter specific key words and returns correct results */
string Domain::check_type_query(string v)
{
    if (v == "1" || v == "built" || v == "yes")
    {
        return "1";
    }
    else if (v == "0" || v == "not built" || v == "no")
    {
        return "0";
    }
    else
    {
        return v;
    }
}

/* This function lets the user enter specific key words and returns correct results */
string Domain::check_sex_query(string v)
{
    if (v == "m" || v == "male")
    {
        return "m";
    }
    else if (v == "f" || v == "femal")
    {
        return "f";
    }
    else if (v == "o" || v == "other")
    {
        return "o";
    }
    else
    {
        return v;
    }

}

/* Deallocate memory for person and computer objects */
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

