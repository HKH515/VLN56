#ifndef COMPUTER_REPO_H
#define COMPUTER_REPO_H

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

class ComputerRepository
{
    private:
        vector<string> internal_data;
        QSqlDatabase db;
        QString db_name;

    public:
        ComputerRepository(string db_name, string conn_name);
        vector<string> query(string column, string data_query); //Fetches all lines matching query (substring search)
        vector<string> query_exact(string column, string data_query); //Fetches all lines matching query exactly
        vector<string> read_entries(); //Returns a vector of all entries
        void write(string line); //Creates an entry in the database
        void remove(string column, string id); //Deletes an entry in the database
};

#endif
