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
        QString get_file();
        void init_db();
        void set_file(string data);
        void push(string entry);
        int nth_index(string haystack, char needle, int n);
        vector<string> create_combined_string_vector(vector<string> sourceVec, string delim); //Returns a modified pipe vector that has all appropriate computers in the last index of the vector
        vector<string> parse_delim_string(string delimString, char delim);
        vector<string> from_db_to_vector(string table, QSqlQuery queryObj);
        vector<string> query(string table, string column, string dataQuery, string sortColumn, string order); //Fetches all lines matching query (substring search)
        vector<string> query_exact(string table, string column, string dataQuery, string sortColumn, string order); //Fetches all lines matching query exactly
        vector<string> get_conn_assoc_with_computer(string computerId);
        vector<string> get_conn_assoc_with_person(string personId);
        vector<string> get_conn_all_computers();
        vector<string> get_conn_all_persons();
        vector<string> read_entries(string table, string column, string order); //Returns a vector of all entries
        void write(string table, string line); //Creates an entry in the database
        void remove(string table, string column, string id); //Deletes an entry in the database

        string create_delim_string(vector<string> sourceVec, string delim);

};

#endif // DATA_H
