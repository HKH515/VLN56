#include "personRepository.h"

PersonRepository::PersonRepository(string db_name, string conn_name)
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

    }
}

void PersonRepository::write(string line)
{
    vector<string> fields = parse_delim_string(line, '|');
    db.open();
    QSqlQuery queryObj(db);
    string queryString;
    queryString = "INSERT INTO 'persons' (name, profession, description, birthyear, deathyear, sex) values('" + fields[0] + "', '" + fields[1] + "', '" + fields[2] + "', '" + fields[3] + "', '" + fields[4] + "', '" + fields[5] + "');";
    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    db.close();
}

//Returns all entries in a specified table
vector<string> PersonRepository::read_entries()
{
    vector<string> query_vect;
    string queryString;
    if (this->db.open())
    {
        QSqlQuery queryObj(db);

        queryString = "SELECT * from persons ORDER BY name";
        QString qQueryString(queryString.c_str());
        queryObj.exec(qQueryString);
        query_vect = from_db_to_vector("persons", queryObj);
    }
    db.close();
    return query_vect;
}

//Removes a certain entry in a speficied table
void PersonRepository::remove(string column, string id)
{
    string queryString;
    db.open();
    QSqlQuery queryObj(db);
    queryString = "DELETE from persons WHERE " + column + "=" + id;
    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    db.close();

}

//Search a specified table
vector<string> PersonRepository::query_exact(string column, string data_query)
{
    vector<string> query_vect;
    vector<string> result_vect;
    db.open();
    QSqlQuery queryObj(db);
    string queryString = "SELECT * FROM persons WHERE " + column + " ='" + data_query + "'";
    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    query_vect = from_db_to_vector("persons", queryObj);
    db.close();

    return query_vect;
}

//Search a specified table with substring
vector<string> PersonRepository::query(string column, string data_query)
{
    vector<string> query_vect;
    vector<string> result_vect;
    db.open();
    QSqlQuery queryObj(db);
    string queryString = "SELECT * FROM persons WHERE " + column + " LIKE '%" + data_query + "%'";
    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    query_vect = from_db_to_vector("persons", queryObj);
    db.close();

    return query_vect;
}
