#include "connectionsservice.h"

ConnectionsService::ConnectionsService()
{
    computer_repo = new ComputerRepository("data.sqlite", "computer_connection");
    person_repo = new PersonRepository("data.sqlite", "person_computer");
}

ConnectionsService::~ConnectionsService()
{
    free_vector_memory();
    delete computer_repo;
    delete person_repo;
    delete connection_repo;
}

void ConnectionsService::free_vector_memory()
{
    for (unsigned int i = 0; i < person_vec.size(); i++)
    {
        delete person_vec[i];
    }
    for (unsigned int i = 0; i < computer_vec.size(); i++)
    {
        delete computer_vec[i];
    }
    person_vec.clear();
    computer_vec.clear();
}

void ConnectionsService::get_all_connections()
{
    cout << "Komin inn´i get_all_connections" << endl;
    free_vector_memory();
    cout << "Búin í free memory" << endl;
    parse_query_vector(connection_repo->get_conn_all_persons());
    parse_query_vector(connection_repo->get_conn_all_computers());
    cout << "Búin í get_all_connections" << endl;
}

void ConnectionsService::add_connection(int person_id, int computer_id)
{
    free_vector_memory();
    string p_id = int_to_string(person_id);
    string c_id = int_to_string(computer_id);

    connection_repo->write(p_id, c_id);
}

void ConnectionsService::remove_connection(int person_id, int computer_id)
{
    string p_id = int_to_string(person_id);
    string c_id = int_to_string(computer_id);

    connection_repo->remove_conn(p_id, c_id);
}

void ConnectionsService::get_connected(vector<string> v)
{

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
