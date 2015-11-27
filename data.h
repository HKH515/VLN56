#ifndef DATA_H
#define DATA_H

#include <fstream>
#include <string>
#include <vector>
#include <regex>

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
        vector<string> query(int column, string dataQuery); //Fetches all lines matching query
        void read(); //Reads the whole data file
};

#endif // DATA_H
