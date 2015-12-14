#include "personsservice.h"

PersonsService::PersonsService()
{
    person_repo = new PersonRepository("data.sqlite", "person_repo_connection");
}

PersonsService::~PersonsService()
{
    free_vector_memory();
    delete person_repo;
}

string PersonsService::parse_add_command(vector<string> vec)
{
    string st = " "; /* add space in front of the string */
    for (unsigned int i = 2; i < vec.size(); i++)
    {
        st += vec[i];
        st += "|"; /* add | after each vector element */
    }
    return st;
}

void PersonsService::parse_query_vector(vector<string> v)
{
    free_vector_memory();
    for (unsigned int i = 0; i < v.size(); i++)
    {
        string st = v[i];
        size_t position_beg = 0;
        size_t position_end = 0;
        /* cut out the empty space in the beginning of the string */
        st = st.substr(1, st.length());
        Person* p = new Person();

        /* find the name */
        position_end = st.find("|");
        p->set_name(st.substr(0, position_end));

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
}

void PersonsService::free_vector_memory()
{
    for (unsigned int i = 0; i < person_vec.size(); i++)
    {
        delete person_vec[i];
    }
    person_vec.clear();
}

void PersonsService::get_all_persons()
{
    cout << "Inni í get all persons" << endl;
    parse_query_vector(person_repo->read_entries());
}

void PersonsService::add_person(vector<string> v)
{
    person_repo->write(parse_add_command(v));
}

void PersonsService::search_person(string column, string substr)
{
    if (column == "Birth Year")
    {
        column = "birthyear";
    }
    else if (column == "Death Year")
    {
        column = "deathyear";
    }
    cout << column << ": " << substr << endl;
    parse_query_vector(person_repo->query(column, substr));
}

vector<Person*> PersonsService::get_person_vec()
{
    return person_vec;
}

void PersonsService::remove_person(int id)
{
    stringstream ss;
    ss << id;
    string str_id = ss.str();
    person_repo->remove("id", str_id);
}



