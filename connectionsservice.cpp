#include "connectionsservice.h"

ConnectionsService::ConnectionsService()
{
    connection_repo = new ConnectionRepository("data.sqlite", "connection_connection");
}

ConnectionsService::~ConnectionsService()
{
    free_person_vector_memory();
    free_computer_vector_memory();
    delete connection_repo;
}

void ConnectionsService::free_person_vector_memory()
{
    for (unsigned int i = 0; i < person_vec.size(); i++)
    {
        delete person_vec[i];
    }
    person_vec.clear();
}

void ConnectionsService::free_computer_vector_memory()
{
    for (unsigned int i = 0; i < computer_vec.size(); i++)
    {
        delete computer_vec[i];
    }
    computer_vec.clear();
}

void ConnectionsService::get_all_connections()
{
    free_person_vector_memory();
    free_computer_vector_memory();
    parse_query_vector(connection_repo->get_conn_all_persons());
    parse_query_vector(connection_repo->get_conn_all_computers());
}

void ConnectionsService::add_connection(string person_id, string computer_id)
{
    connection_repo->write(person_id, computer_id);
}

void ConnectionsService::remove_connection(int person_id, int computer_id)
{
    string p_id = int_to_string(person_id);
    string c_id = int_to_string(computer_id);
    connection_repo->remove_conn(p_id, c_id);
}

void ConnectionsService::get_connected(string kind, string name)
{
    if (kind == "Computer Scientist")
    {
        free_computer_vector_memory();

        Person* current_person = find_chosen_person(name);
        string str_id = int_to_string(current_person->get_id());
        parse_query_vector(connection_repo->get_conn_assoc_with_person(str_id));
    }
    else
    {
        free_person_vector_memory();
        Computer* current_computer = find_chosen_computer(name);
        string str_id = int_to_string(current_computer->get_id());
        parse_query_vector(connection_repo->get_conn_assoc_with_computer(str_id));
        cout << person_vec.size() << endl;
    }
}

string ConnectionsService::int_to_string(int id)
{
    stringstream ss;
    ss << id;
    string str_id = ss.str();
    return str_id;
}

vector<Person *> ConnectionsService::get_person_vec()
{
    return person_vec;
}

vector<Computer *> ConnectionsService::get_computer_vec()
{
    return computer_vec;
}

void ConnectionsService::parse_query_vector(vector<string> v)
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

            person_vec.push_back(p);
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

            computer_vec.push_back(c);
        }
    }
}

Computer *ConnectionsService::find_chosen_computer(string name)
{
    cout << "c size: " << computer_vec.size() << endl;
    parse_query_vector(connection_repo->get_conn_all_computers());
    for (unsigned int i = 0; i < computer_vec.size(); i++)
    {
        cout << computer_vec[i]->get_name() << endl;
        if (computer_vec[i]->get_name() == name)
        {
            cout << "Fann tölvu!" << endl;
            return computer_vec[i];
        }
    }
    return NULL;
}

Person *ConnectionsService::find_chosen_person(string name)
{
    for (unsigned int i = 0; i < person_vec.size(); i++)
    {
        if (person_vec[i]->get_name() == name)
        {
            return person_vec[i];
        }
    }
    return NULL;
}
