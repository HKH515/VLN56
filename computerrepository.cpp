#include "computerrepository.h"

ComputerRepository::ComputerRepository(string db_name, string conn_name)
{
    QString q_conn_name = QString(conn_name.c_str());
    QString q_db_name = QString(db_name.c_str());
    if (QSqlDatabase::contains(q_conn_name))
    {
        db = QSqlDatabase::database(q_conn_name);
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE", q_conn_name);
        db.setDatabaseName(q_db_name);
        db.open();
    }
}

// Add an entry to the Computer table
void ComputerRepository::write(string line)
{
    vector<string> fields = parse_delim_string(line, '|');
    if (db.open())
    {
        QSqlQuery query_obj(db);
        string query_string;
        query_string = "INSERT INTO 'computers' (name, construction_year, type, built, description) values('" + fields[0] + "', '" + fields[1] + "', '" + fields[2] + "', '" + fields[3] + "', '" + fields[4] + "');";
        QString q_query_string(query_string.c_str());
        query_obj.exec(q_query_string);
    }
    db.close();
}

//Returns all entries in a specified table
vector<string> ComputerRepository::read_entries()
{
    vector<string> query_vect;
    string query_string;
    if (db.open())
    {
        QSqlQuery query_obj(db);

        query_string = "SELECT * from computers ORDER BY name";
        QString q_query_string(query_string.c_str());
        query_obj.exec(q_query_string);
        query_vect = from_db_to_vector("computers", query_obj);
    }
    db.close();

    return query_vect;
}

//Removes a certain entry in a speficied table
void ComputerRepository::remove(string column, string id)
{
    string query_string;
    if (db.open())
    {
        QSqlQuery query_obj(db);
        query_string = "DELETE from computers WHERE " + column + "=" + id;
        QString q_query_string(query_string.c_str());
        query_obj.exec(q_query_string);
        cout << "buin ad remova ur database" << endl;
    }
    db.close();

}

//Search a specified table
vector<string> ComputerRepository::query_exact(string column, string data_query)
{
    vector<string> query_vect;
    vector<string> result_vect;
    if (db.open())
    {
        QSqlQuery query_obj(db);
        string query_string = "SELECT * FROM computers WHERE " + column + " ='" + data_query + "'";;
        QString q_query_string(query_string.c_str());
        query_obj.exec(q_query_string);
        query_vect = from_db_to_vector("computers", query_obj);
    }
    db.close();

    return query_vect;
}

//Search a specified table with substring
vector<string> ComputerRepository::query(string column, string data_query)
{
    vector<string> query_vect;
    vector<string> result_vect;
    if (db.open())
    {
        QSqlQuery query_obj(db);
        string query_string = "SELECT * FROM computers WHERE " + column + " LIKE '%" + data_query + "%'";
        QString q_query_string(query_string.c_str());
        query_obj.exec(q_query_string);
        query_vect = from_db_to_vector("computers", query_obj);
    }
    db.close();

    return query_vect;
}
