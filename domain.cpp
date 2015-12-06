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
void Domain::parse_query_vector(vector<string> v)
{
    for (unsigned int i = 0; i < v.size(); i++)
    {
        string st = v[i];
        size_t position_beg = 0;
        size_t position_end = 0;
        // cut out the empty space in the beginning of the string
        st = st.substr(1, st.length());

        // find if it is a computer or a person
        position_beg = st.find("|");
        string kind = st.substr(0, position_beg);
        //cout << "kind: " << kind << endl;

        if (kind == "0")
        {
            Person* p = new Person();
            vector<Person*> vec;
            // find the name
            position_end = st.find("|", position_beg + 1);
            p->set_name(st.substr(position_beg + 1, position_end - position_beg - 1));
            //cout << "name: " << p->get_name() << endl;

            // find the profession
            position_beg = st.find("|", position_end + 1);
            p->set_profession(st.substr(position_end + 1, (position_beg - position_end - 1)));
            //cout << "profession: " << p->get_profession() << endl;

            // find the description
            position_end = st.find("|", position_beg + 1);
            p->set_description(st.substr(position_beg + 1, (position_end - position_beg - 1)));
            //cout << "description: " << p->get_description() << endl;

            // find the birthyear
            position_beg = st.find("|", position_end + 1);
            p->set_birthyear(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));
            //cout << "birthyear: " << p->get_birthyear() << endl;

            // find the deathyear
            position_end = st.find("|", position_beg + 1);
            p->set_deathyear(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));
            //cout << "deathyear: " << p->get_deathyear() << endl;

            // find the sex
            position_beg = st.find("|", position_end + 1);
            p->set_sex(st.substr(position_end + 1, (position_beg - position_end - 1)));
            // cout << "sex: " << p->get_sex() << endl;

            // find the id
            position_end = st.find("|", position_beg + 1);
            p->set_id(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));
            //cout << "id: " << p->get_id() << endl;

            //Aborting mission
            /*// Get all connected computers
            position_end = st.find(",");
            position_beg = 0;
            string first = st.substr(position_beg, (position_end - position_beg));
            cout << first << endl;
            p->push_back_vec(first);
            while (position_end != string::npos)
            {
                position_beg = position_end;
                position_end = st.find(",", position_end + 1);
                p->push_back_vec(st.substr(position_beg + 1, (position_end - position_beg - 1)));
                cout << st.substr(position_beg + 1, (position_end - position_beg - 1)) << endl;
            }
            cout << "Her" << endl;
            position_end = st.find("|", position_beg + 1);
            cout << st.substr(position_beg + 1) << endl;
            p->push_back_vec(st.substr(position_beg + 1));
            cout << p->get_vec().size() << endl;*/

            p_vec.push_back(p);
        }
        else if (kind == "1")
        {
            vector<Computer*> c_vec;
            Computer* c = new Computer();

            // find the name
            position_end = st.find("|", position_beg + 1);
            c->set_name(st.substr(position_beg + 1, position_end - position_beg));
            cout << "name: " << c->get_name() << endl;

            // find the constructio year
            position_beg = st.find("|", position_end + 1);
            c->set_construction_year(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));
            cout << "constr year: " << c->get_construction_year() << endl;

            // find the type
            position_end = st.find("|", position_beg + 1);
            c->set_type(st.substr(position_beg + 1, (position_end - position_beg - 1)));
            cout << "type: " << c->get_type() << endl;

            // find if built
            position_beg = st.find("|", position_end + 1);
            c->set_built(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));
            cout << "built: " << c->get_built() << endl;

            // find the description
            position_end = st.find("|", position_beg + 1);
            c->set_description(st.substr(position_beg + 1, (position_end - position_beg - 1)));
            cout << "description: " << c->get_description() << endl;

            // find the id
            position_beg = st.find("|", position_end + 1);
            c->set_id(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));
            cout << "id: " << c->get_id() << endl;

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
    cout << "table: " << table << endl;
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
    string table = get_table(v[1]);
    string query_column = get_column(v[2], table);
    string query_string = v[3];
    string sort_column = get_column(v[4], table);
    string sort_method = get_sort_method(v[5]);

    parse_query_vector(data->query(table, query_column, query_string, sort_column, sort_method));
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

