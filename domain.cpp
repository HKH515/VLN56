#include "domain.h"

// Parse function for queries returned from the data layer. Parses
void Domain::parse_query_vector(vector<string> v) {
    
    for (unsigned int i = 0; i < v.size(); i++) {
        string st = v[i];
        Person p = Person();
        // find the name
        unsigned long position_beg = st.find("|");
        p.set_name(st.substr(0, position_beg));
        // find the birthyear
        unsigned long position_end = st.find("|", position_beg + 1);
        p.set_birthyear(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));
        // find the deathyear
        position_beg = st.find("|", position_end + 1);
        p.set_deathyear(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));
        // find the sex
        position_end = st.find("|", position_beg + 1);
        p.set_sex(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));
        // find the description
        position_beg = st.find("|", position_end + 1);
        p.set_description(st.substr(position_end + 1, (position_beg - position_end - 1)));
        // find the profession
        position_end = st.find("|", position_beg + 1);
        p.set_profession(st.substr(position_beg + 1, (position_end - position_beg - 1)));
        vec.push_back(p);
    }
    // Default returns vector sorted by name in ascending order
    sort_ascending(vec);
}

// If the user wants to add an entry to the database, parse the incoming
// vector, put delimeter (|) between
string Domain::parse_add_command(vector<string> vec) {
    string st = " ";
    for (unsigned int i = 1; i < vec.size(); i++) {
        st += vec[i];
        st += "|";
    }
    return st;
}

/*bool Domain::greater(Person &lhs, Person &rhs) const
{
    return lhs.get_name() > rhs.get_name();
}*/

// Sort
void Domain::sort_ascending(vector<Person> &v)
{
    stable_sort(v.begin(), v.end());
}

void Domain::sort_descending(vector<Person> &v)
{
    stable_sort(v.end(), v.begin());
}

vector<Person> Domain::handle_commands(vector<string> v) {
    string command = v[0];
    data->read();
    vector<Person> pers;

    // returns all entries in database
    if (command == "list") {
        parse_query_vector(data->readEntries());
        return vec;
    }
    // if the user wants to add a new entry to the database
    else if (command == "add") {
        data->write(parse_add_command(v));
        return pers;
    }
    // if the user wants to search in the list
    else if (command == "search")
    {
        // Assume to get 2 parameters from presentation layer
        string query = v[1];
        int query_column = 0;
        if (query == "name") {
            query_column = 0;
        }
        else if (query == "description") {
            query_column = 1;
        }
        else if (query == "profession") {
            query_column = 2;
        }
        else if (query == "birthyear") {
            query_column = 3;
        }
        else if (query == "deathyear") {
            query_column = 4;
        }
        else { // sex
            query_column = 5;
        }

        string query_string = v[2];
        parse_query_vector(data->query(query_column, query_string));
        return vec;
    }

    return pers;
}
