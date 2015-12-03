#include "domain.h"

Domain::Domain() {
    data = new Data("data.dat");
}

vector<Person*> Domain::get_vec() {
    return vec;
}

Domain::~Domain() {
    delete data;
    for (unsigned int i = 0; i < vec.size(); i++) {
        delete vec[i];
    }
}

// Parse function for queries returned from the data layer.
void Domain::parse_query_vector(vector<string> v, int sort_column, string sort_method) {
    for (unsigned int i = 0; i < v.size(); i++) {
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

        vec.push_back(p);
    }
    // sort the results after prefered column and order. Entries always ordered internally by name.
    //if (sort_method == "d") {
      //  if (sort_column != 1) {
        //    sort_ascending(vec, 1);
        //}
        //sort_descending(vec, sort_column);
    //}
    //else {
        //if (sort_column != 1) {
            //sort_ascending(vec, 1);
        //}
        //sort_ascending(vec, sort_column);
    //}
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
    data->read();

    if (command == "list") /* returns all entries in specified table */
    {
        get_list(v);
    }
    else if (command == "add") /* adds new entry in specified table */
    {
        add_entry(v);
    }
    // if the user wants to search in the list
    else if (command == "search")
    {
        search(v);
    }
}

void Domain::get_list(vector<string> v)
{
    string table = get_table(v[1]);
    string sort_column = get_column(v[2], table);
    string sort_method = get_sort_method(v[3]);
    parse_query_vector(data->readEntries(table, sort_column, sort_method));
}

void Domain::add_entry(vector<string> v)
{
    string table = get_table(v[1]);
    data->write(table, parse_add_command(v));
}

void Domain::search(vector<string> v)
{
    string table = get_table(v[1]); /* database table number */
    string query_column = get_column(v[2], table); /* search column */
    string query_string = v[3]; /* search substring */
    string sort_column = get_column(v[4], get_table); /* sort by column */
    string sort_method = get_sort_method(v[5]); /* sort ascending or descending */

    parse_query_vector(data->query(query_column, query_string), sort_column, sort_method);
}

string Domain::get_table(string s)
{
    if (s == "1")
    {
        return = "persons"
    }
    else
    {
        return = "computers"
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
    if (table = "persons")
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
        else
        {
            return "description";
        }
    }
    else
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
        else
        {
            return "description"
        }
    }
}

void Domain::free_vector_memory()
{
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        delete vec[i];
    }
    vec.clear();
}

// Sort
void Domain::sort_ascending(vector<Person*> &v, int search_column)
{
    ComparePerson comp = ComparePerson(search_column,"a");
    stable_sort(v.begin(), v.end(), comp);
}

void Domain::sort_descending(vector<Person*> &v, int search_column)
{
    ComparePerson comp = ComparePerson(search_column,"d");
    stable_sort(v.begin(), v.end(), comp);
}
