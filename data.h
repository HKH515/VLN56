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
#include <map>

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
        vector<string> createCombinedStringVector(vector<string> sourceVec, string delim); //Returns a modified pipe vector that has all appropriate computers in the last index of the vector
        vector<string> parseDelimString(string delimString, char delim);
        vector<string> fromDbToVector(string table, QSqlQuery queryObj);
        vector<string> query(string table, string column, string dataQuery, string sortColumn, string order); //Fetches all lines matching query
        vector<string> readEntries(string table, string column, string order); //Returns a vector of all entries
        void write(string table, string line); //Creates an entry in the database
        void remove(string table, string column, string id); //Deletes an entry in the database

        string createDelimString(vector<string> sourceVec, string delim);

};

#endif // DATA_H
