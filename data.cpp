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


    QSqlQuery queryObj(db);
    string queryString;
    cout << "table: " << table << endl;
    cout << "line: " << line << endl;
    if (table == "persons")
    {
        cout << "inside wadfsadf";
        queryString = "INSERT INTO 'persons' (name, profession, description, birthyear, deathyear, sex) values('" + fields[0] + "', '" + fields[1] + "', '" + fields[2] + "', '" + fields[3] + "', '" + fields[4] + "', '" + fields[5] + "');";


    }
    else if (table == "computers")
    {
        queryString = "INSERT INTO 'computers' (name, construction_year, type, built, description) values('" + fields[0] + "', '" + fields[1] + "', '" + fields[2] + "', '" + fields[3] + "', '" + fields[4] + "');";
    }

    else if (table == "connections")
    {
        queryString = "INSERT INTO 'connections' (ID_computers, ID_persons) values('" + fields[0] + "', '" + fields[1] + "');";
    }
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

vector<string> Data::createCombinedStringVector(vector<string> sourceVec, string delim)
{
    vector<string> results;
    map<string, string> names;
    for (int i = 0; i < sourceVec.size(); i++)
    {
        vector<string> parsedString;
        parsedString = parseDelimString(sourceVec[i], '|');
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
        results.push_back(createDelimString(parsedString, "|"));

    }

    vector<string> cleanedResults;

    string prevName;
    for (int j = results.size()-1; j >=0; j--)
    {
        /*cout << results[j] << endl;
        string resultTmpName = parseDelimString(results[j], '|')[1];
        cout << "COMPARING: " << resultTmpName << " and " << prevName;
        if (resultTmpName != prevName)
        {
            cleanedResults.push_back(results[j]);
        }
        prevName = resultTmpName;*/
    }

    return results;

}

vector<string> Data::readEntries(string table, string column, string order) {

    vector<string> queryVect;
    vector<string> resultVect;
    string queryString;
    if (db.open())
    {
        cout << "WORKS" << endl;

    }
    QSqlQuery queryObj(db);
    if (table == "persons")
    {
        queryString = "SELECT persons.name, persons.profession, persons.description, persons.birthyear, persons.deathyear, persons.sex, persons.ID, computers.name as computer_name FROM persons INNER JOIN connections ON ID_computers INNER JOIN computers ON computers.ID = connections.ID_computers WHERE persons.ID = connections.ID_persons";
    }
    cout << queryString << endl;
    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    qDebug() << queryObj.lastError() << endl;
    queryVect = fromDbToVector(table, queryObj);
    resultVect = createCombinedStringVector(queryVect, "|");
    cout << queryVect.size() << endl;
    for (int i = 0; i < resultVect.size(); i++)
    {
        cout << resultVect[i] << endl;
    }
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
            tableData.push_back("0");
            tableData.push_back(queryObj.value("name").toString().toStdString());
            tableData.push_back(queryObj.value("profession").toString().toStdString());
            tableData.push_back(queryObj.value("description").toString().toStdString());
            tableData.push_back(queryObj.value("birthyear").toString().toStdString());
            tableData.push_back(queryObj.value("deathyear").toString().toStdString());
            tableData.push_back(queryObj.value("sex").toString().toStdString());
            tableData.push_back(queryObj.value("id").toString().toStdString());
            tableData.push_back(queryObj.value("computer_name").toString().toStdString());

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
    vector<string> resultVect;
    db.open();
    QSqlQuery queryObj(db);
    string queryString = "SELECT * FROM '" + table + "' WHERE '" + sortColumn + "' LIKE '%" + dataQuery + "%' ORDER BY '" + column + "';";
    cout << queryString << endl;
    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    qDebug() << queryObj.lastError() << endl;
    queryVect = fromDbToVector(table, queryObj);
    resultVect = createCombinedStringVector(queryVect, "|");
    cout << queryVect.size() << endl;
    db.close();

    return resultVect;
}
