#ifndef DATA_H
#define DATA_H

#include <QTextStream>
#include <QFile>
#include <QString>
#include <QtSql>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Data
{
    private:
        vector<string> internalData;
        QSqlDatabase db;
        QString dbName;

    public:
        Data(string datafile);
        QString getFile();
        void initDb();
        void setFile(string data);
        void push(string entry);
        int nthIndex(string haystack, char needle, int n);
        vector<string> parseDelimString(string delimString, char delim);
        vector<string> fromDbToVector(string table, QSqlQuery queryObj);
        vector<string> query(string table, string column, string dataQuery, string sortColumn, string order); //Fetches all lines matching query
        vector<string> readEntries(string table, string column, string order); //Returns a vector of all entries
        void write(string table, string line); //Creates an entry in the sqlite file
};

#endif // DATA_H
