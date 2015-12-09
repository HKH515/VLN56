#include "data.h"

Data::Data(string datafile)
{

    connection_name = "VLN56_connection";

    set_file(datafile);
    init_db();
}

void Data::init_db()
{
    QString qConnectionString(connection_name.c_str());

    db = QSqlDatabase::addDatabase("QSQLITE", qConnectionString);

    db.setDatabaseName(get_file());
}

void Data::set_file(string filename)
{

    QString qName(filename.c_str());
    db_name = QString(qName);
}

QString Data::get_file()
{
    return db_name;
}

void Data::write(string table, string line)
{
    vector<string> fields = parse_delim_string(line, '|');
    /* Open database */
    db.open();
    QSqlQuery queryObj(db);
    string query_string;

    if (table == "persons") /* Adds into the persons table */
    {
        query_string = "INSERT INTO 'persons' (name, profession, description, birthyear, deathyear, sex) values('" + fields[0] + "', '" + fields[1] + "', '" + fields[2] + "', '" + fields[3] + "', '" + fields[4] + "', '" + fields[5] + "');";

    }
    else if (table == "computers") /* Adds into the computers table */
    {
        query_string = "INSERT INTO 'computers' (name, construction_year, type, built, description) values('" + fields[0] + "', '" + fields[1] + "', '" + fields[2] + "', '" + fields[3] + "', '" + fields[4] + "');";
    }

    else if (table == "connections") /* Adds into the connections table */
    {
        query_string = "INSERT INTO 'connections' (ID_computers, ID_persons) values('" + fields[1] + "', '" + fields[0] + "');";
    }

    QString qQueryString(query_string.c_str());
    queryObj.exec(qQueryString);
    db.close();
}

/* Creates a string the domain layer can parse */
string Data::create_delim_string(vector<string> source_vec, string delim)
{
    string results = " ";
    for (unsigned long i = 0; i < source_vec.size(); i++)
    {
        results = results + source_vec[i] + delim;
    }
    return results;
}

vector<string> Data::parse_delim_string(string delim_string, char delim)
{
    vector<string> results;

    for (int i = 0; i < count(delim_string.begin(), delim_string.end(), delim); i++)
    {
        results.push_back(delim_string.substr(nth_index(delim_string, delim, i)+1, nth_index(delim_string, delim, i+1) - nth_index(delim_string, delim, i)-1));
    }
    return results;
}

//Returns all entries in a specified table
vector<string> Data::read_entries(string table, string column, string order)
{
    vector<string> query_vect;
    vector<string> result_vect;
    string query_string;
    if (db.open())
    {
        QSqlQuery queryObj(db);
        /* Get all entries from table */
        query_string = "SELECT * from " + table + " ORDER BY " + column + " " + order;
        QString qQueryString(query_string.c_str());
        queryObj.exec(qQueryString);
        query_vect = from_db_to_vector(table, queryObj);
    }
    db.close();

    return query_vect;
}

//Removes a certain entry in a speficied table
void Data::remove(string table, string column, string id)
{
    string query_string;
    db.open();
    QSqlQuery queryObj(db);
    /* Delete from database */
    query_string = "DELETE from " + table + " WHERE " + column + "=" + id;
    QString qQueryString(query_string.c_str());
    queryObj.exec(qQueryString);
    db.close();

}

/* Finds the index of the nth occurance of a specified delimiter */
int Data::nth_index(string haystack, char needle, int n)
{
    int occurances = 0;
    for (unsigned int i = 0; i < haystack.size(); i++)
    {
        if (haystack[i] == needle) {
            occurances++;
        }
        if (occurances == n) {
            return i;
        }
    }
    return haystack.size()-1; /* fallback if char is not found, return end of string */
}

/* Gets a QSqlQuery object and fetches all entries from it and delivers it in a pipe-seperated-string vector */
vector<string> Data::from_db_to_vector(string table, QSqlQuery queryObj)
{
    vector<string> result;
    while(queryObj.next())
    {
        vector<string> table_data;
        string curr_entry = " ";
        if (table == "persons")
        {
            table_data.push_back("0");
            table_data.push_back(queryObj.value("name").toString().toStdString());
            table_data.push_back(queryObj.value("profession").toString().toStdString());
            table_data.push_back(queryObj.value("description").toString().toStdString());
            table_data.push_back(queryObj.value("birthyear").toString().toStdString());
            table_data.push_back(queryObj.value("deathyear").toString().toStdString());
            table_data.push_back(queryObj.value("sex").toString().toStdString());
            table_data.push_back(queryObj.value("id").toString().toStdString());
        }
        else if (table == "computers")
        {
            table_data.push_back("1");
            table_data.push_back(queryObj.value("name").toString().toStdString());
            table_data.push_back(queryObj.value("construction_year").toString().toStdString());
            table_data.push_back(queryObj.value("type").toString().toStdString());
            table_data.push_back(queryObj.value("built").toString().toStdString());
            table_data.push_back(queryObj.value("description").toString().toStdString());
            table_data.push_back(queryObj.value("id").toString().toStdString());
        }

        curr_entry = create_delim_string(table_data, "|");
        result.push_back(curr_entry);
    }
    return result;
}

/* Returns all computers that have a persons associated with them, returns entries in the same order as get_conn_all_persons */
vector<string> Data::get_conn_all_computers()
{
    vector<string> query_vect;
    string query_string;
    if (db.open())
    {
        QSqlQuery queryObj(db);

        query_string = "SELECT computers.* FROM persons INNER JOIN connections ON ID_computers INNER JOIN computers ON computers.ID = connections.ID_computers WHERE connections.ID_persons = persons.ID ORDER BY persons.name";

        QString qQueryString(query_string.c_str());
        queryObj.exec(qQueryString);
        query_vect = from_db_to_vector("computers", queryObj);
    }
    db.close();
    return query_vect;
}

//Returns all persons that have a persons associated with them, returns entries in the same order as get_conn_all_computers
vector<string> Data::get_conn_all_persons()
{
    vector<string> query_vect;
    string query_string;
    if (db.open())
    {
        QSqlQuery queryObj(db);

        query_string = "SELECT persons.* FROM persons INNER JOIN connections ON ID_computers INNER JOIN computers ON computers.ID = connections.ID_computers WHERE connections.ID_persons = persons.ID ORDER BY persons.name";

        QString qQueryString(query_string.c_str());
        queryObj.exec(qQueryString);
        query_vect = from_db_to_vector("persons", queryObj);
    }
    db.close();
    return query_vect;
}

/* Returns all computers that have a persons associated with them */
vector<string> Data::get_conn_assoc_with_person(string person_id)
{
    vector<string> query_vect;
    string query_string;
    if (db.open())
    {
        QSqlQuery queryObj(db);

        query_string = "SELECT c.* from computers c INNER JOIN connections con ON c.ID = con.ID_computers WHERE con.ID_persons = " + person_id + " ORDER BY c.Name";

        QString qQueryString(query_string.c_str());
        queryObj.exec(qQueryString);
        query_vect = from_db_to_vector("computers", queryObj);
        db.close();
    }
    return query_vect;
}

/* Returns all persons that have a persons associated with them */
vector<string> Data::get_conn_assoc_with_computer(string computer_id)
{
    vector<string> query_vect;
    string query_string;
    if (db.open())
    {
        QSqlQuery queryObj(db);

        query_string = "SELECT p.* FROM persons p INNER JOIN connections con ON p.ID = con.ID_persons WHERE con.ID_computers = " + computer_id + " ORDER BY p.name";

        QString qQueryString(query_string.c_str());
        queryObj.exec(qQueryString);
        query_vect = from_db_to_vector("persons", queryObj);
    }
    db.close();

    return query_vect;
}

/* Removes a specified entry in the connections table */
void Data::remove_conn(string person_id, string computer_id)
{
    string query_string;
    if (db.open())
    {
        QSqlQuery queryObj(db);

        query_string = "DELETE from connections WHERE ID_computers=" + computer_id + " AND ID_persons=" + person_id + ";";

        QString qQueryString(query_string.c_str());
        queryObj.exec(qQueryString);
        db.close();
    }

}

/* Search a specified table */
vector<string> Data::query_exact(string table, string column, string data_query, string sort_column, string order)
{
    vector<string> query_vect;
    vector<string> result_vect;
    db.open();
    QSqlQuery queryObj(db);
    string query_string = "SELECT * FROM " + table + " WHERE " + column + " ='" + data_query + "' ORDER BY " + sort_column + " " + order;
    QString qQueryString(query_string.c_str());
    queryObj.exec(qQueryString);
    query_vect = from_db_to_vector(table, queryObj);
    db.close();

    return query_vect;
}

/* Search a specified table with substring */
vector<string> Data::query(string table, string column, string data_query, string sort_column, string order)
{
    vector<string> query_vect;
    vector<string> result_vect;
    db.open();
    QSqlQuery queryObj(db);
    string query_string = "SELECT * FROM " + table + " WHERE " + column + " LIKE '%" + data_query + "%' ORDER BY " + sort_column + " " + order;
    QString qQueryString(query_string.c_str());
    queryObj.exec(qQueryString);
    query_vect = from_db_to_vector(table, queryObj);
    db.close();

    return query_vect;
}
