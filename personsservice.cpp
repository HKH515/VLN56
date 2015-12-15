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

vector<Person*> PersonsService::get_person_vec()
{
    return person_vec;
}

void PersonsService::free_vector_memory()
{
    for (unsigned int i = 0; i < person_vec.size(); i++)
    {
        delete person_vec[i];
    }
    person_vec.clear();
}

string PersonsService::check_search_substring(string column, string substring)
{
    if (column == "Sex")
    {
        if (substring == "Male" || substring == "male" || substring == "M" || substring == "m")
        {
            return "m";
        }
        else if (substring == "Female" || substring == "female" || substring == "F" || substring == "f")
        {
            return "f";
        }
        else
        {
            return "o";
        }
    }
    if (column == "deathyear")
    {
        if (substring == "-")
        {
            return "0";
        }
    }
    return substring;

}

string PersonsService::parse_add_command(vector<string> vec)
{
    string st = " "; // add space in front of the string
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        st += vec[i];
        st += "|"; // add | after each vector element
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
        // cut out the empty space in the beginning of the string
        st = st.substr(1, st.length());
        position_beg = st.find("|");

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
        string sex = st.substr(position_end + 1, (position_beg - position_end - 1));
        if (sex == "m")
        {
            p->set_sex("Male");
        }
        else if (sex == "f")
        {
            p->set_sex("Female");
        }
        else
        {
            p->set_sex("Other");
        }

        // find the id
        position_end = st.find("|", position_beg + 1);
        p->set_id(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));

        person_vec.push_back(p);
    }

}

void PersonsService::get_all_persons()
{
    // Pushbacks all persons in the database into the person_vec
    parse_query_vector(person_repo->read_entries());
}

void PersonsService::add_person(vector<string> v)
{
    // Sends add command to the database
    person_repo->write(parse_add_command(v));
}

void PersonsService::search_person(string column, string substring)
{
    // The columns in the database are named birthyear and deathyear
    if (column == "Birth Year")
    {
        column = "birthyear";
    }
    else if (column == "Death Year")
    {
        column = "deathyear";
        parse_query_vector(person_repo->query_exact(column, check_search_substring(column, substring)));
        return;
    }

    // Sends search command to data layer
    substring = check_search_substring(column, substring);
    parse_query_vector(person_repo->query(column, substring));
}


void PersonsService::remove_person(int id)
{
    // Change the id to string
    stringstream ss;
    ss << id;
    string str_id = ss.str();
    // Send remove command to data layer
    person_repo->remove("id", str_id);
}

Person* PersonsService::find_chosen_person(int chosen_id)
{
    for (unsigned int i = 0; i < person_vec.size(); i++)
    {
        if (person_vec[i]->get_id() == chosen_id)
        {
            return person_vec[i];
        }
    }
    return NULL;
}

Person *PersonsService::find_chosen_person_by_name(string chosen_name)
{
    for (unsigned int i = 0; i < person_vec.size(); i++)
    {
        if (person_vec[i]->get_name() == chosen_name)
        {
            return person_vec[i];
        }
    }
    return NULL;

}

