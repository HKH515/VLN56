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
#include "connectionRepository.h"
#include "personRepository.h"
#include "computerRepository.h"


using namespace std;

class Data
{
    private:

        vector<string> internalData;
        QSqlDatabase db;
        QString dbName;
        ConnectionRepository* connection_repo;
        PersonRepository* person_repo;
        ComputerRepository* computer_repo;

    public:
        Data(string datafile);
        void init_db();
        vector<string> query(string table, string column, string data_query, string sort_column, string order); //Fetches all lines matching query (substring search)
        vector<string> query_exact(string table, string column, string data_query, string sort_column, string order); //Fetches all lines matching query exactly
        vector<string> get_conn_assoc_with_computer(string computer_ID);
        vector<string> get_conn_assoc_with_person(string person_ID);
        vector<string> get_conn_all_computers();
        vector<string> get_conn_all_persons();
        void remove_conn(string person_ID, string computer_ID);
        vector<string> read_entries(string table, string column, string order); //Returns a vector of all entries
        void write(string table, string line); //Creates an entry in the database
        void remove(string table, string column, string id); //Deletes an entry in the database
};

#endif // DATA_H
