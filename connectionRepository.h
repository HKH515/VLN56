#ifndef CONN_REPO_H
#define CONN_REPO_H

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
#include "utils.h"

using namespace std;
using namespace utils;

class ConnectionRepository
{
    private:
        vector<string> internal_data;
        QSqlDatabase db;
        QString db_name;

    public:
        ConnectionRepository(string db_name, string conn_name);
        vector<string> query(string column, string data_query, string sort_column, string order); //Fetches all lines matching query (substring search)
        vector<string> query_exact(string column, string data_query, string sort_column, string order); //Fetches all lines matching query exactly
        vector<string> get_conn_assoc_with_computer(string computer_ID);
        vector<string> get_conn_assoc_with_person(string person_ID);
        vector<string> get_conn_all_computers();
        vector<string> get_conn_all_persons();
        void remove_conn(string person_ID, string computer_ID);
        vector<string> read_entries(string column, string order); //Returns a vector of all entries
        void write(string line); //Creates an entry in the database
        void remove(string column, string id); //Deletes an entry in the database
};

#endif
