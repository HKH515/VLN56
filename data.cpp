#include "data.h"

Data::Data(string datafile)
{
    set_file(datafile);
    init_db();
}

void Data::init_db()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "VLN56_connection");
    db.setDatabaseName(get_file());
    ConnectionRepository connection_repo(&db);
    PersonRepository person_repo(&db);
    ComputerRepository computer_repo(&db);
}
void Data::set_file(string data)
{
    QString qName(data.c_str());
    dbName = QString(qName);
}

QString Data::get_file()
{
    return dbName;
}

void Data::write(string table, string line)
{
    if (table == "persons")
    {
        person_repo.write(line);
    }
    else if (table == "computers")
    {
        computer_repo.write(line);
    }

    else if (table == "connections")
    {
        connection_repo.write(line);
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
        person_repo.remove(column, id);
    }
    else if (table == "computers")
    {
        computer_repo.remove(column, id);
    }

    else if (table == "connections")
    {
        connection_repo.remove(column, id);
    }
}

//Returns all computers that have a persons associated with them, returns entries in the same order as get_conn_all_persons
vector<string> Data::get_conn_all_computers()
{
    return connection_repo.get_conn_all_computers();
}

//Returns all persons that have a persons associated with them, returns entries in the same order as get_conn_all_computers
vector<string> Data::get_conn_all_persons()
{
    return connection_repo->get_conn_all_persons();
}

//Returns all computers that have a persons associated with them
vector<string> Data::get_conn_assoc_with_person(string personId)
{
    return connection_repo->get_conn_assoc_with_person(personId);
}

//Returns all persons that have a persons associated with them
vector<string> Data::get_conn_assoc_with_computer(string computerId)
{
    return connection_repo->get_conn_assoc_with_computer(computerId);
}

//Removes a specified entry in the connections table
void Data::remove_conn(string personId, string computerId)
{
    connection_repo->remove_conn(personId, computerId);
}

//Search a specified table
vector<string> Data::query_exact(string table, string column, string dataQuery, string sortColumn, string order)
{
    if (table == "persons")
    {
        return person_repo->query_exact(column, dataQuery, sortColumn, order);
    }
    else if (table == "computers")
    {
        return computer_repo->query_exact(column, dataQuery, sortColumn, order);
    }

    else if (table == "connections")
    {
        return connection_repo->query_exact(column, dataQuery, sortColumn, order);
    }
}

//Search a specified table with substring
vector<string> Data::query(string table, string column, string dataQuery, string sortColumn, string order)
{
    if (table == "persons")
    {
        return person_repo->query(column, dataQuery, sortColumn, order);
    }
    else if (table == "computers")
    {
        return computer_repo->query(column, dataQuery, sortColumn, order);
    }

    else if (table == "connections")
    {
        return connection_repo->query(column, dataQuery, sortColumn, order);
    }
}
