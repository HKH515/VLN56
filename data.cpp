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
    db.open();
    if( !db.open() )
    {
        cout << "failed" << endl;
    }

    cout << "db opened";
    QSqlQuery queryObj(db);
    string queryString;
    if (table == "persons")
    {
        queryString = "INSERT INTO " + table + " (name, profession, description, birthyear, deathyear, sex, id) values('"
                + fields[0] + "','" + fields[1] + "','" + "','" + fields[2] + "','" + fields[3] + "','" + fields[4] + ','
                + fields[5] + "','" + fields[6] + "');";

    }
    cout << queryString << endl;

    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    db.close();
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
    while(queryObj.next())
    {
        string currentEntry = " ";
        if (table == "persons")
        {
            currentEntry += queryObj.value("name").toString().toStdString() + "|";
            currentEntry += queryObj.value("profession").toString().toStdString() + "|";
            currentEntry += queryObj.value("description").toString().toStdString() + "|";
            currentEntry += queryObj.value("birthyear").toString().toStdString() + "|";
            currentEntry += queryObj.value("deathyear").toString().toStdString() + "|";
            currentEntry += queryObj.value("sex").toString().toStdString() + "|";
            currentEntry += queryObj.value("id").toString().toStdString() + "|";
         }
        else if (table == "computers")
        {
            currentEntry += queryObj.value("name").toString().toStdString() + "|";
            currentEntry += queryObj.value("profession").toString().toStdString() + "|";
            currentEntry += queryObj.value("description").toString().toStdString() + "|";
            currentEntry += queryObj.value("birthyear").toString().toStdString() + "|";
            currentEntry += queryObj.value("deathyear").toString().toStdString() + "|";
            currentEntry += queryObj.value("sex").toString().toStdString() + "|";
            currentEntry += queryObj.value("id").toString().toStdString() + "|";
        }
        cout << currentEntry << endl;
        result.push_back(currentEntry);
    }
    return result;
}

vector<string> Data::query(string table, string column, string dataQuery, string sortColumn, string order) {
    vector<string> queryVect;
    qDebug() << db.open();
    QSqlQuery queryObj(db);
    string queryString = "SELECT * FROM " + table + " WHERE " + column + " LIKE %" + dataQuery + "% ORDER BY " + sortColumn + ";";
    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);

    queryVect = fromDbToVector(table, queryObj);

    db.close();

    return queryVect;
}
