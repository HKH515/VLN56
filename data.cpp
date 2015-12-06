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
    cout << "CONTENTS l" <<  sourceVec[0] << endl;
    if (sourceVec.size() > 1) //If the input is anything else than just the type of data (person or computer), parse, otherwise return empty vector
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
        //cleanedResults = results;
        for (int j = results.size()-1; j > 0; j--)
        {
            cout << "RESULTS: " << results[0] << endl;
            string longestComputerField;

            for (int h = results.size()-1; h > 0; h--)
            {
                cout << "j: " << j << ", h: " << h << endl;
                string resultTmpName1 = parseDelimString(results[j], '|')[1];
                string resultTmpName2 = parseDelimString(results[h], '|')[1];
                cout << "COMPARING: " << resultTmpName1 << " and " << resultTmpName2;

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
                    cout << "NAMES MATCH" << endl;
                    int lengthOfComputerField1 = parseDelimString(results[j], '|')[8].size();
                    int lengthOfComputerField2 = parseDelimString(results[h], '|')[8].size();
                    if (lengthOfComputerField1 <= lengthOfComputerField2)
                    {
                        longestComputerField = results[h];
                    }
                    else
                    {
                        longestComputerField = results[j];
                    }
                }
                cout << "EEEEEEEEEEEEEE" << endl;
             }
            cout << "AAAAAAAAAAAAA" << endl;
            cleanedResults.push_back(longestComputerField);
            cout << cleanedResults.size() << endl;
            cout << "longestComputerField for iter: " << longestComputerField;
        }


        return cleanedResults;
    }
    else
    {
        vector<string> empty;
        return empty;
    }

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
    cout << "LE TABL'E " << table << endl;
    if (table == "persons")
    {
        queryString = "SELECT * from persons ORDER BY " + column + " " + order;
    }
    else if (table == "computers")
    {
        queryString = "SELECT * from computers ORDER BY " + column + " " + order;
    }
    cout << queryString << endl;
    QString qQueryString(queryString.c_str());
    queryObj.exec(qQueryString);
    qDebug() << queryObj.lastError() << endl;
    queryVect = fromDbToVector(table, queryObj);
    for (int i = 0; i < queryVect.size(); i++)
    {
        cout << queryVect[i] << endl;
    }
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
