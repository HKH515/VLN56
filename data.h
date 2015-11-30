#ifndef DATA_H
#define DATA_H

#include <QTextStream>
#include <QFile>
#include <QString>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Data
{
    private:
        string internalFilename;
        vector<string> internalData;

    public:
        Data(string datafile);
        string getFile();
        void setFile(string data);
        void push(string entry);
        int nthIndex(string haystack, char needle, int n);
        vector<string> query(int column, string dataQuery); //Fetches all lines matching query
        void read(); //Reads the whole data file (internal)
        vector<string> readEntries(); //Returns a vector of all entries
        void write(string line); //Creates an entry in the data file
};

#endif // DATA_H
