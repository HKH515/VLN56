#include "data.h"

Data::Data(string datafile) {

    connectionName = "VLN56_connection";

    set_file(datafile);
    init_db();
}

void Data::init_db()
{
    QString qConnectionString(connectionName.c_str());

    db = QSqlDatabase::addDatabase("QSQLITE", qConnectionString);

    db.setDatabaseName(get_file());
}

void Data::set_file(string filename)
{

    QString qName(filename.c_str());
    dbName = QString(qName);
}

QString Data::get_file()
{
    return dbName;
}

void Data::write(string table, string line)
{
    vector<string> fields = parse_delim_string(line, '|');
    db.open();
    QSqlQuery queryObj(db);
    string queryString;
    if (table == "persons")
    {
        queryString = "INSERT INTO 'persons' (name, profession, description, birthyear, deathyear, sex) values('" + fields[0] + "', '" + fields[1] + "', '" + fields[2] + "', '" + fields[3] + "', '" + fields[4] + "', '" + fields[5] + "');";

    }
    else if (table == "computers")
    {
        queryString = "INSERT INTO 'computers' (name, construction_year, type, built, description) values('" + fields[0] + "', '" + fields[1] + "', '" + fields[2] + "', '" + fields[3] + "', '" + fields[4] + "');";
    }

    else if (table == "connections")
    {
        queryString = "INSERT INTO 'connections' (ID_computers, ID_persons) values('" + fields[1] + "', '" + fields[0] + "');";
    }

    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    db.close();
}

string Data::create_delim_string(vector<string> sourceVec, string delim)
{
    string results = " ";
    for (int i = 0; i < sourceVec.size(); i++)
    {
        results = results + sourceVec[i] + delim;
    }
    return results;
}

vector<string> Data::parse_delim_string(string delimString, char delim)
{
    vector<string> results;

    for (int i = 0; i < count(delimString.begin(), delimString.end(), delim); i++)
    {

        results.push_back(delimString.substr(nth_index(delimString, delim, i)+1, nth_index(delimString, delim, i+1) - nth_index(delimString, delim, i)-1));
    }
    return results;
}

//Returns all entries in a specified table
vector<string> Data::read_entries(string table, string column, string order)
{
    vector<string> queryVect;
    vector<string> resultVect;
    string queryString;
    if (db.open())
    {
        QSqlQuery queryObj(db);

        queryString = "SELECT * from " + table + " ORDER BY " + column + " " + order;
        QString qQueryString(queryString.c_str());
        queryObj.exec(qQueryString);
        queryVect = from_db_to_vector(table, queryObj);
    }
    db.close();

    return queryVect;

}

//Removes a certain entry in a speficied table
void Data::remove(string table, string column, string id)
{
    string queryString;
    db.open();
    QSqlQuery queryObj(db);
    queryString = "DELETE from " + table + " WHERE " + column + "=" + id;
    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    db.close();

}

int Data::nth_index(string haystack, char needle, int n)
{
    int occurances = 0;
    for (unsigned int i = 0; i < haystack.size(); i++) {
        if (haystack[i] == needle) {
            occurances++;
        }
        if (occurances == n) {
            return i;
        }
    }
    return haystack.size()-1; //fallback if char is not found, return end of string
}

//Gets a QSqlQuery object and fetches all entries from it and delivers it in a pipe-seperated-string vector
vector<string> Data::from_db_to_vector(string table, QSqlQuery queryObj)
{
    vector<string> result;
    while(queryObj.next())
    {
        vector<string> tableData;
        string currentEntry = " ";
        if (table == "persons")
        {
            tableData.push_back("0");
            tableData.push_back(queryObj.value("name").toString().toStdString());
            tableData.push_back(queryObj.value("profession").toString().toStdString());
            tableData.push_back(queryObj.value("description").toString().toStdString());
            tableData.push_back(queryObj.value("birthyear").toString().toStdString());
            tableData.push_back(queryObj.value("deathyear").toString().toStdString());
            tableData.push_back(queryObj.value("sex").toString().toStdString());
            tableData.push_back(queryObj.value("id").toString().toStdString());
        }
        else if (table == "computers")
        {
            tableData.push_back("1");
            tableData.push_back(queryObj.value("name").toString().toStdString());
            tableData.push_back(queryObj.value("construction_year").toString().toStdString());
            tableData.push_back(queryObj.value("type").toString().toStdString());
            tableData.push_back(queryObj.value("built").toString().toStdString());
            tableData.push_back(queryObj.value("description").toString().toStdString());
            tableData.push_back(queryObj.value("id").toString().toStdString());
        }

        currentEntry = create_delim_string(tableData, "|");
        result.push_back(currentEntry);
    }
    return result;
}

//Returns all computers that have a persons associated with them, returns entries in the same order as get_conn_all_persons
vector<string> Data::get_conn_all_computers()
{
    vector<string> queryVect;
    string queryString;
    if (db.open())
    {
        QSqlQuery queryObj(db);

        queryString = "SELECT computers.* FROM persons INNER JOIN connections ON ID_computers INNER JOIN computers ON computers.ID = connections.ID_computers WHERE connections.ID_persons = persons.ID ORDER BY persons.name";

        QString qQueryString(queryString.c_str());
        queryObj.exec(qQueryString);
        queryVect = from_db_to_vector("computers", queryObj);
    }
    db.close();
    return queryVect;
}

//Returns all persons that have a persons associated with them, returns entries in the same order as get_conn_all_computers
vector<string> Data::get_conn_all_persons()
{
    vector<string> queryVect;
    string queryString;
    if (db.open())
    {
        QSqlQuery queryObj(db);

        queryString = "SELECT persons.* FROM persons INNER JOIN connections ON ID_computers INNER JOIN computers ON computers.ID = connections.ID_computers WHERE connections.ID_persons = persons.ID ORDER BY persons.name";

        QString qQueryString(queryString.c_str());
        queryObj.exec(qQueryString);
        queryVect = from_db_to_vector("persons", queryObj);
    }
    db.close();
    return queryVect;
}

//Returns all computers that have a persons associated with them
vector<string> Data::get_conn_assoc_with_person(string personId)
{
    vector<string> queryVect;
    string queryString;
    if (db.open())
    {
        QSqlQuery queryObj(db);

        queryString = "SELECT c.* from computers c INNER JOIN connections con ON c.ID = con.ID_computers WHERE con.ID_persons = " + personId + " ORDER BY c.Name";

        QString qQueryString(queryString.c_str());
        queryObj.exec(qQueryString);
        queryVect = from_db_to_vector("computers", queryObj);
        db.close();
    }
    return queryVect;
}

//Returns all persons that have a persons associated with them
vector<string> Data::get_conn_assoc_with_computer(string computerId)
{
    vector<string> queryVect;
    string queryString;
    if (db.open())
    {
        QSqlQuery queryObj(db);

        queryString = "SELECT p.* FROM persons p INNER JOIN connections con ON p.ID = con.ID_persons WHERE con.ID_computers = " + computerId + " ORDER BY p.name";

        QString qQueryString(queryString.c_str());
        queryObj.exec(qQueryString);
        queryVect = from_db_to_vector("persons", queryObj);
    }
    db.close();

    return queryVect;
}

//Removes a specified entry in the connections table
void Data::remove_conn(string personId, string computerId)
{
    string queryString;
    if (db.open())
    {
        QSqlQuery queryObj(db);

        queryString = "DELETE from connections WHERE ID_computers=" + computerId + " AND ID_persons=" + personId + ";";

        QString qQueryString(queryString.c_str());
        queryObj.exec(qQueryString);
        db.close();
    }

}

//Search a specified table
vector<string> Data::query_exact(string table, string column, string dataQuery, string sortColumn, string order)
{
    vector<string> queryVect;
    vector<string> resultVect;
    db.open();
    QSqlQuery queryObj(db);
    string queryString = "SELECT * FROM " + table + " WHERE " + column + " ='" + dataQuery + "' ORDER BY " + sortColumn + " " + order;
    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    queryVect = from_db_to_vector(table, queryObj);
    db.close();

    return queryVect;
}

//Search a specified table with substring
vector<string> Data::query(string table, string column, string dataQuery, string sortColumn, string order)
{
    vector<string> queryVect;
    vector<string> resultVect;
    db.open();
    QSqlQuery queryObj(db);
    string queryString = "SELECT * FROM " + table + " WHERE " + column + " LIKE '%" + dataQuery + "%' ORDER BY " + sortColumn + " " + order;
    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    queryVect = from_db_to_vector(table, queryObj);
    db.close();

    return queryVect;
}
