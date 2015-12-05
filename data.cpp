#include "data.h"

Data::Data(string datafile) {
    setFile(datafile);
    initDb();
}

void Data::initDb()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "VLN56_connection");

    db.setDatabaseName(getFile());


}

void Data::setFile(string filename) {

    QString qName(filename.c_str());
    dbName = QString(qName);
}

QString Data::getFile() {
    return dbName;
}


void Data::write(string table, string line) {
    vector<string> fields = parseDelimString(line, '|');
    cout << "field no. 0 is" << fields[0];
    for (int i = 0; i < fields.size(); i++)
    {
        cout << fields[i] << endl;
    }
    db.open();
    if( !db.open() )
    {
        cout << "failed" << endl;
    }

    cout << "db opened";
    QSqlQuery queryObj(db);
    string queryString;
    cout << "table: " << table << endl;
    cout << "line: " << line << endl;
    //if (table == "persons")
    //{
        cout << "inside wadfsadf";
        queryString = "INSERT INTO 'persons' (name, profession, description, birthyear, deathyear, sex) values('" + fields[0] + "', '" + fields[1] + "', '" + fields[2] + "', '" + fields[3] + "', '" + fields[4] + "', '" + fields[5] + "');";
                //queryString = "INSERT INTO 'persons' (name, profession, description, birthyear, deathyear, sex) values('"
                //        + fields[0] + "','" + fields[1] + "','" + "','" + fields[2] + "','" + fields[3] + "','" + fields[4] + ','
                //        + fields[5] + "');";
        cout << "YO QUERY: " << queryString << endl;

    //}
    cout << queryString << endl;

    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    qDebug() << queryObj.lastError() << endl;
    db.close();
}

string Data::createDelimString(vector<string> sourceVec, string delim)
{
    string results = " ";
    for (int i = 0; i < sourceVec.size(); i++)
    {
        results = results + sourceVec[i] + delim;
    }
    return results;
}

vector<string> Data::parseDelimString(string delimString, char delim)
{
    vector<string> results;

    for (int i = 0; i < count(delimString.begin(), delimString.end(), delim); i++)
    {

        results.push_back(delimString.substr(nthIndex(delimString, delim, i)+1, nthIndex(delimString, delim, i+1) - nthIndex(delimString, delim, i)-1));
    }
    return results;
}

vector<string> Data::readEntries(string table, string column, string order) {

    vector<string> queryVect;
    if (db.open())
    {
        cout << "WORKS" << endl;

    }
    QSqlQuery queryObj(db);
    string queryString = "SELECT * FROM '" + table + "' ORDER BY '" + column + "';";
    cout << queryString << endl;
    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    qDebug() << queryObj.lastError() << endl;
    queryVect = fromDbToVector(table, queryObj);
    cout << queryVect.size() << endl;
    db.close();
    return queryVect;

}

void Data::push(string entry) {
    internalData.push_back(entry);
}

int Data::nthIndex(string haystack, char needle, int n) {
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

vector<string> Data::fromDbToVector(string table, QSqlQuery queryObj)
{
    vector<string> result;
    result.push_back(table);
    while(queryObj.next())
    {
        vector<string> tableData;
        string currentEntry = " ";
        if (table == "persons")
        {
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
            tableData.push_back(queryObj.value("name").toString().toStdString());
            tableData.push_back(queryObj.value("construction_year").toString().toStdString());
            tableData.push_back(queryObj.value("type").toString().toStdString());
            tableData.push_back(queryObj.value("built").toString().toStdString());
            tableData.push_back(queryObj.value("description").toString().toStdString());
        }

        currentEntry = createDelimString(tableData, "|");
        result.push_back(currentEntry);
    }
    return result;
}

vector<string> Data::query(string table, string column, string dataQuery, string sortColumn, string order) {
    vector<string> queryVect;
    if (db.open())
    {
        cout << "WORKS" << endl;

    }
    QSqlQuery queryObj(db);
    string queryString = "SELECT * FROM '" + table + "' WHERE '" + sortColumn + "' LIKE '%" + dataQuery + "%' ORDER BY '" + column + "';";
    cout << queryString << endl;
    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    qDebug() << queryObj.lastError() << endl;
    queryVect = fromDbToVector(table, queryObj);
    cout << queryVect.size() << endl;
    db.close();
    return queryVect;
}
