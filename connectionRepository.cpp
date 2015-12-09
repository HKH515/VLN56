#include "connectionRepository.h"

ConnectionRepository::ConnectionRepository(string db_name, string conn_name)
{
    QString q_conn_name = QString(conn_name.c_str());
    QString q_db_name = QString(db_name.c_str());
    db = QSqlDatabase::addDatabase("QSQLITE", q_conn_name);
    db.setDatabaseName(q_db_name);
}

void ConnectionRepository::write(string line)
{
    vector<string> fields = parse_delim_string(line, '|');
    db.open();
    QSqlQuery query_obj(db);
    string query_string;
    query_string = "INSERT INTO 'connections' (ID_computers, ID_persons) values('" + fields[1] + "', '" + fields[0] + "');";
    QString q_query_string(query_string.c_str());
    query_obj.exec(q_query_string);
    db.close();
}

//Returns all entries in a specified table
vector<string> ConnectionRepository::read_entries(string column, string order)
{
    vector<string> queryVect;
    vector<string> resultVect;
    string query_string;
    if (db.open())
    {

    }
    QSqlQuery query_obj(db);

    query_string = "SELECT * from connection ORDER BY " + column + " " + order;
    QString q_query_string(query_string.c_str());
    query_obj.exec(q_query_string);
    queryVect = from_db_to_vector("connections", query_obj);
    db.close();

    return queryVect;

}

//Removes a certain entry in a speficied table
void ConnectionRepository::remove(string column, string id)
{
    string query_string;
    db.open();
    QSqlQuery query_obj(db);
    query_string = "DELETE from connection WHERE " + column + "=" + id;
    QString q_query_string(query_string.c_str());
    query_obj.exec(q_query_string);
    db.close();

}

//Returns all computers that have a persons associated with them, returns entries in the same order as get_conn_all_persons
vector<string> ConnectionRepository::get_conn_all_computers()
{
    vector<string> queryVect;
    string query_string;
    if (db.open())
    {
        QSqlQuery query_obj(db);

        query_string = "SELECT computers.* FROM persons INNER JOIN connections ON ID_computers INNER JOIN computers ON computers.ID = connections.ID_computers WHERE connections.ID_persons = persons.ID ORDER BY persons.name";

        QString q_query_string(query_string.c_str());
        query_obj.exec(q_query_string);
        queryVect = from_db_to_vector("computers", query_obj);
        db.close();
    }
    return queryVect;

}

//Returns all persons that have a persons associated with them, returns entries in the same order as get_conn_all_computers
vector<string> ConnectionRepository::get_conn_all_persons()
{
    vector<string> queryVect;
    string query_string;
    if (db.open())
    {

    }
    QSqlQuery query_obj(db);

    query_string = "SELECT persons.* FROM persons INNER JOIN connections ON ID_computers INNER JOIN computers ON computers.ID = connections.ID_computers WHERE connections.ID_persons = persons.ID ORDER BY persons.name";

    QString q_query_string(query_string.c_str());
    query_obj.exec(q_query_string);
    queryVect = from_db_to_vector("persons", query_obj);
    db.close();
    return queryVect;

}

//Returns all computers that have a persons associated with them
vector<string> ConnectionRepository::get_conn_assoc_with_person(string person_ID)
{
    vector<string> queryVect;
    string query_string;
    if (db.open())
    {
        QSqlQuery query_obj(db);

        query_string = "SELECT c.* from computers c INNER JOIN connections con ON c.ID = con.ID_computers WHERE con.ID_persons = " + person_ID + " ORDER BY c.Name";

        QString q_query_string(query_string.c_str());
        query_obj.exec(q_query_string);
        queryVect = from_db_to_vector("computers", query_obj);
        db.close();
    }
    return queryVect;

}

//Returns all persons that have a persons associated with them
vector<string> ConnectionRepository::get_conn_assoc_with_computer(string computer_ID)
{
    vector<string> queryVect;
    string query_string;
    if (db.open())
    {

    }
    QSqlQuery query_obj(db);

    query_string = "SELECT p.* FROM persons p INNER JOIN connections con ON p.ID = con.ID_persons WHERE con.ID_computers = " + computer_ID + " ORDER BY p.name";

    QString q_query_string(query_string.c_str());
    query_obj.exec(q_query_string);
    queryVect = from_db_to_vector("connections", query_obj);
    db.close();

    return queryVect;

}

//Removes a specified entry in the connections table
void ConnectionRepository::remove_conn(string person_ID, string computer_ID)
{
    string query_string;
    if (db.open())
    {
        QSqlQuery query_obj(db);

        query_string = "DELETE from connections WHERE ID_computers=" + computer_ID + " AND ID_persons=" + person_ID + ";";

        QString q_query_string(query_string.c_str());
        query_obj.exec(q_query_string);
        db.close();
    }

}

//Search a specified table
vector<string> ConnectionRepository::query_exact(string column, string data_query, string sort_column, string order)
{
    vector<string> queryVect;
    vector<string> resultVect;
    db.open();
    QSqlQuery query_obj(db);
    string query_string = "SELECT * FROM connections WHERE " + column + " ='" + data_query + "' ORDER BY " + sort_column + " " + order;
    QString q_query_string(query_string.c_str());
    query_obj.exec(q_query_string);
    queryVect = from_db_to_vector("connections", query_obj);
    db.close();

    return queryVect;
}

//Search a specified table with substring
vector<string> ConnectionRepository::query(string column, string data_query, string sort_column, string order)
{
    vector<string> queryVect;
    vector<string> resultVect;
    db.open();
    QSqlQuery query_obj(db);
    string query_string = "SELECT * FROM connections WHERE " + column + " LIKE '%" + data_query + "%' ORDER BY " + sort_column + " " + order;
    QString q_query_string(query_string.c_str());
    query_obj.exec(q_query_string);
    queryVect = from_db_to_vector("connections", query_obj);
    db.close();

    return queryVect;
}
