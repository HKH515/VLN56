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
    if (sort_method == "d") {
        if (sort_column != 1) {
            sort_descending(vec, 1);
        }
        sort_descending(vec, sort_column);
    }
    else {
        if (sort_column != 1) {
            sort_descending(vec, 1);
        }
        sort_ascending(vec, sort_column);
    }
}

string Domain::parse_add_command(vector<string> v) {
    string st = " ";
    for (unsigned int i = 1; i < v.size(); i++) {
        st += v[i];
        st += "|";
    }
    return st;
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
        // Assume to get 2 parameters from presentation layer. Get the column to search in
        string query = v[1];
        int query_column = stoi(query) - 1;
        // get which substring to look for
        string query_string = v[2];
        // what column to sort by
        int sort_column = stoi(v[3]);
        // sort in ascending or descending order
        string sort_method = v[4];
        parse_query_vector(data->query(query_column, query_string), sort_column, sort_method);
    }
}
