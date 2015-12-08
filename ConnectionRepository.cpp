#include "ConnectionRepository.h"

Data::Data(string datafile) {
    set_file(datafile);
    init_db();
}

void Data::init_db()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "VLN56_connection");
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
    queryString = "INSERT INTO 'connections' (ID_computers, ID_persons) values('" + fields[1] + "', '" + fields[0] + "');";
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

vector<string> Data::create_combined_string_vector(vector<string> sourceVec, string delim)
{
    if (sourceVec.size() > 1) //If the input is anything else than just the type of data (person or computer), parse, otherwise return empty vector
    {
        vector<string> results;
        map<string, string> names;
        for (int i = 0; i < sourceVec.size(); i++)
        {
            vector<string> parsedString;
            parsedString = parse_delim_string(sourceVec[i], '|');
            string lastComputer;
            for (int o = 0; o < parsedString.size(); o++)
            {
                if (parsedString[8] != lastComputer)
                {
                    names[parsedString[1]] = names[parsedString[1]] + "," + parsedString[8];
                }
                lastComputer = parsedString[8];
                if (o == parsedString.size()-1) //If last iteration
                {
                    parsedString[8] = names[parsedString[1]];
                }


            }
            results.push_back(create_delim_string(parsedString, "|"));

        }

        vector<string> cleanedResults;
        //cleanedResults = results;
        for (int j = results.size()-1; j > 0; j--)
        {
            string longestComputerField;

            for (int h = results.size()-1; h > 0; h--)
            {
                string resultTmpName1 = parse_delim_string(results[j], '|')[1];
                string resultTmpName2 = parse_delim_string(results[h], '|')[1];

                bool alreadyExistsInClean = false;
                for (int a = 0; a < results.size(); a++)
                {
                    if (results[a] == resultTmpName1)
                    {
                        alreadyExistsInClean = true;
                    }
                }
                if (resultTmpName1 == resultTmpName2 && !alreadyExistsInClean)
                {
                    int lengthOfComputerField1 = parse_delim_string(results[j], '|')[8].size();
                    int lengthOfComputerField2 = parse_delim_string(results[h], '|')[8].size();
                    if (lengthOfComputerField1 <= lengthOfComputerField2)
                    {
                        longestComputerField = results[h];
                    }
                    else
                    {
                        longestComputerField = results[j];
                    }
                }
             }
            cleanedResults.push_back(longestComputerField);
        }
        return cleanedResults;
    }
    else
    {
        vector<string> empty;
        return empty;
    }

}

//Returns all entries in a specified table
vector<string> Data::read_entries(string table, string column, string order)
{

    vector<string> queryVect;
    vector<string> resultVect;
    string queryString;
    if (db.open())
    {

    }
    QSqlQuery queryObj(db);

    queryString = "SELECT * from " + table + " ORDER BY " + column + " " + order;
    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    queryVect = from_db_to_vector(table, queryObj);
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

//Returns all computers that have a persons associated with them, returns entries in the same order as get_conn_all_persons
vector<string> Data::get_conn_all_computers()
{
    vector<string> queryVect;
    string queryString;
    if (db.open())
    {

    }
    QSqlQuery queryObj(db);

    queryString = "SELECT computers.* FROM persons INNER JOIN connections ON ID_computers INNER JOIN computers ON computers.ID = connections.ID_computers WHERE connections.ID_persons = persons.ID ORDER BY persons.name";

    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    queryVect = from_db_to_vector("computers", queryObj);
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

    }
    QSqlQuery queryObj(db);

    queryString = "SELECT persons.* FROM persons INNER JOIN connections ON ID_computers INNER JOIN computers ON computers.ID = connections.ID_computers WHERE connections.ID_persons = persons.ID ORDER BY persons.name";

    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    queryVect = from_db_to_vector("persons", queryObj);
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

    }
    QSqlQuery queryObj(db);

    queryString = "SELECT p.* FROM persons p INNER JOIN connections con ON p.ID = con.ID_persons WHERE con.ID_computers = " + computerId + " ORDER BY p.name";

    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    queryVect = from_db_to_vector("persons", queryObj);
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
    string queryString = "SELECT * FROM " + table + " WHERE " + column + " ='" + dataQuery + "' ORDER BY " + column + " " + order;
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
    string queryString = "SELECT * FROM " + table + " WHERE " + column + " LIKE '%" + dataQuery + "%' ORDER BY " + column + " " + order;
    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    queryVect = from_db_to_vector(table, queryObj);
    db.close();

    return queryVect;
}
