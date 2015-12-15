#include "connectionsService.h"

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

vector<Person *> ConnectionsService::get_person_vec()
{
    return person_vec;
}

vector<Computer *> ConnectionsService::get_computer_vec()
{
    return computer_vec;
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
    // Pushbacks all the persons that have a connection into the person_vec, if one person has more than
    // one connection she will appear more than once in the vector
    parse_query_vector(connection_repo->get_conn_all_persons());
    // Pushbacks all the computers that have a connection into the computer_vec, same goes as above.
    parse_query_vector(connection_repo->get_conn_all_computers());
}

void ConnectionsService::add_connection(string person_id, string computer_id)
{
    // Sends an add command to the data layer with the Ids to connect
    connection_repo->write(person_id, computer_id);
}

void ConnectionsService::remove_connection(int person_id, int computer_id)
{
    // Change the Ids from int to string
    string p_id = int_to_string(person_id);
    string c_id = int_to_string(computer_id);
    // Sends remove command to the data layer
    connection_repo->remove_conn(p_id, c_id);
}

void ConnectionsService::get_connected(string kind, string name)
{
    // Get all computers connected to this scientist
    if (kind == "Computer Scientist")
    {
        // Clear the computer vector
        free_computer_vector_memory();
        // Find the right person
        Person* current_person = find_chosen_person(name);
        // Change the Id from int to string
        string str_id = int_to_string(current_person->get_id());
        // Send command to data layer
        parse_query_vector(connection_repo->get_conn_assoc_with_person(str_id));
    }
    // Get all persons connected to this computer
    else
    {
        free_person_vector_memory();
        Computer* current_computer = find_chosen_computer(name);
        string str_id = int_to_string(current_computer->get_id());
        parse_query_vector(connection_repo->get_conn_assoc_with_computer(str_id));
    }
}

void ConnectionsService::parse_query_vector(vector<string> v)
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

        if (kind == "0")
        {
            Person* p = new Person();

            // find the name
            position_end = st.find("|", position_beg + 1);
            p->set_name(st.substr(position_beg + 1, position_end - position_beg - 1));

            // find the profession
            position_beg = st.find("|", position_end + 1);
            p->set_profession(st.substr(position_end + 1, (position_beg - position_end - 1)));

            // find the description
            position_end = st.find("|", position_beg + 1);
            p->set_description(st.substr(position_beg + 1, (position_end - position_beg - 1)));

            // find the birthyear
            position_beg = st.find("|", position_end + 1);
            p->set_birthyear(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));

            // find the deathyear
            position_end = st.find("|", position_beg + 1);
            p->set_deathyear(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));

            // find the sex
            position_beg = st.find("|", position_end + 1);
            p->set_sex(st.substr(position_end + 1, (position_beg - position_end - 1)));

            // find the id
            position_end = st.find("|", position_beg + 1);
            p->set_id(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));

            person_vec.push_back(p);
        }
        else if (kind == "1")
        {
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
}

Computer *ConnectionsService::find_chosen_computer(string name)
{
    // Make sure the vector is empty
    free_computer_vector_memory();
    // Set all computers that have a connection into the computer_vec
    parse_query_vector(connection_repo->get_conn_all_computers());

    for (unsigned int i = 0; i < computer_vec.size(); i++)
    {
        if (computer_vec[i]->get_name() == name)
        {
            return computer_vec[i];
        }
    }
    return NULL;
}

Person *ConnectionsService::find_chosen_person(string name)
{
    // Make sure the vector is empty
    free_person_vector_memory();
    // Set all persons that have a connection into the person_vec
    parse_query_vector(connection_repo->get_conn_all_persons());

    for (unsigned int i = 0; i < person_vec.size(); i++)
    {
        if (person_vec[i]->get_name() == name)
        {
            return person_vec[i];
        }
    }
    return NULL;
}

// Changes the input id from int to string using stringstream
string ConnectionsService::int_to_string(int id)
{
    stringstream ss;
    ss << id;
    string str_id = ss.str();
    return str_id;
}
