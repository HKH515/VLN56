#include "domain.h"

Domain::Domain() {
    data = new Data("data.dat");
}

vector<Person> Domain::get_vec() {
    return vec;
}

// Parse function for queries returned from the data layer.
void Domain::parse_query_vector(vector<string> v, int search_column, string sort_method) {
    for (unsigned int i = 0; i < v.size(); i++) {
        string st = v[i];
        //cout << i << endl;
        Person p = Person();
        //cout << v[i] << endl;
        st = st.substr(1, st.length());
        // find the name
        size_t position_beg = st.find("|");
        p.set_name(st.substr(0, position_beg));

        // find the profession
        size_t position_end = st.find("|", position_beg + 1);
        p.set_profession(st.substr(position_beg + 1, (position_end - position_beg - 1)));

        // find the description
        position_beg = st.find("|", position_end + 1);
        p.set_description(st.substr(position_end + 1, (position_beg - position_end - 1)));

        // find the birthyear
        position_end = st.find("|", position_beg + 1);
        string by = st.substr(position_beg + 1, (position_end - position_beg - 1));
        p.set_birthyear(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));

        // find the deathyear
        position_beg = st.find("|", position_end + 1);
        p.set_deathyear(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));

        // find the sex
        position_end = st.find("|", position_beg + 1);
        p.set_sex(st.substr(position_beg + 1, (position_end - position_beg - 1)));
        vec.push_back(p);
    }
    if (sort_method == "d") {
        sort_descending(vec, search_column);
    }
    else {
        sort_ascending(vec, search_column);
    }
}

// If the user wants to add an entry to the database, parse the incoming
// vector, put delimeter (|) between
string Domain::parse_add_command(vector<string> v) {
    string st = " ";
    for (unsigned int i = 1; i < v.size(); i++) {
        st += v[i];
        st += "|";
    }
    return st;
}

// Sort
void Domain::sort_ascending(vector<Person> &v, int search_column)
{
    ComparePerson comp = ComparePerson(search_column,"a");
    stable_sort(v.begin(), v.end(), comp);
}

void Domain::sort_descending(vector<Person> &v, int search_column)
{
    ComparePerson comp = ComparePerson(search_column,"d");
    stable_sort(v.begin(), v.end(), comp);
    reverse(v.begin(), v.end());
}

void Domain::handle_commands(vector<string> v) {
    vec.clear();
    string command = v[0];
    data->read();

    // returns all entries in database
    if (command == "list") {
        cout << "handle commands: list" << endl;
        int sort_column = stoi(v[1]);
        string sort_method = v[2];
        parse_query_vector(data->readEntries(), sort_column, sort_method);
        cout << "Buin med list" << endl;
    }
    // if the user wants to add a new entry to the database
    else if (command == "add") {
        cout << "komin inn í command = add" << endl;
        cout << parse_add_command(v) << endl;
        data->write(parse_add_command(v));
        vec.clear();
    }
    // if the user wants to search in the list
    else if (command == "search")
    {
        // Assume to get 2 parameters from presentation layer
        string query = v[1];
        int query_column = 0;
        if (query == "1") {
            query_column = 0;
        }
        else if (query == "2") {
            query_column = 1;
        }
        else if (query == "3") {
            query_column = 2;
        }
        else if (query == "4") {
            query_column = 3;
        }
        else if (query == "5") {
            query_column = 4;
        }
        else if (query == "6") {
            query_column = 5;
        }
        string query_string = v[2];
        int sort_column = stoi(v[3]);
        string sort_method = v[4];
        parse_query_vector(data->query(query_column, query_string), sort_column, sort_method);
    }
}
