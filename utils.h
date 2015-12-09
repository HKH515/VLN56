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
#include <algorithm>

using namespace std;

namespace utils
{
    string create_delim_string(vector<string> source_vec, string delim);
    vector<string> parse_delim_string(string delim_string, char delim);
    int nth_index(string haystack, char needle, int n);
    vector<string> from_db_to_vector(string table, QSqlQuery query_obj);
}
