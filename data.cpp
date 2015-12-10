#include "data.h"

Data::Data(string datafile)
{
    init_db();
}

void Data::init_db()
{

    connection_repo = new ConnectionRepository("data.sqlite", "VLN56_connection");
    person_repo = new PersonRepository("data.sqlite", "VLN56_person");
    computer_repo = new ComputerRepository("data.sqlite", "VLN56_computer");
}

void Data::write(string table, string line)
{
    if (table == "persons")
    {
        person_repo->write(line);
    }
    else if (table == "computers")
    {
        computer_repo->write(line);
    }

    else if (table == "connections")
    {
        connection_repo->write(line);
    }
}

//Returns all entries in a specified table
vector<string> Data::read_entries(string table, string column, string order)
{
    if (table == "persons")
    {
        return person_repo->read_entries(column, order);
    }
    else if (table == "computers")
    {
        return computer_repo->read_entries(column, order);
    }

    else if (table == "connections")
    {
        return connection_repo->read_entries(column, order);
    }

}

//Removes a certain entry in a speficied table
void Data::remove(string table, string column, string id)
{
    if (table == "persons")
    {
        person_repo->remove(column, id);
    }
    else if (table == "computers")
    {
        computer_repo->remove(column, id);
    }

    else if (table == "connections")
    {
        connection_repo->remove(column, id);
    }
}

//Returns all computers that have a persons associated with them, returns entries in the same order as get_conn_all_persons
vector<string> Data::get_conn_all_computers()
{
    return connection_repo->get_conn_all_computers();
}

//Returns all persons that have a persons associated with them, returns entries in the same order as get_conn_all_computers
vector<string> Data::get_conn_all_persons()
{
    return connection_repo->get_conn_all_persons();
}

//Returns all computers that have a persons associated with them
vector<string> Data::get_conn_assoc_with_person(string person_ID)
{
    return connection_repo->get_conn_assoc_with_person(person_ID);
}

//Returns all persons that have a persons associated with them
vector<string> Data::get_conn_assoc_with_computer(string computer_ID)
{
    return connection_repo->get_conn_assoc_with_computer(computer_ID);
}

//Removes a specified entry in the connections table
void Data::remove_conn(string person_ID, string computer_ID)
{
    connection_repo->remove_conn(person_ID, computer_ID);
}

//Search a specified table
vector<string> Data::query_exact(string table, string column, string data_query, string sort_column, string order)
{
    if (table == "persons")
    {
        return person_repo->query_exact(column, data_query, sort_column, order);
    }
    else if (table == "computers")
    {
        return computer_repo->query_exact(column, data_query, sort_column, order);
    }

    else if (table == "connections")
    {
        return connection_repo->query_exact(column, data_query, sort_column, order);
    }
}

//Search a specified table with substring
vector<string> Data::query(string table, string column, string data_query, string sort_column, string order)
{
    if (table == "persons")
    {
        return person_repo->query(column, data_query, sort_column, order);
    }
    else if (table == "computers")
    {
        return computer_repo->query(column, data_query, sort_column, order);
    }

    else if (table == "connections")
    {
        return connection_repo->query(column, data_query, sort_column, order);
    }
}
