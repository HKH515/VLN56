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
        string filename;
        vector<string> data;
    
    public:
        Data(string datafile);
        string getFile();
        void setFile(string data);
        void push_back(string entry);
        vector<string> query(); //Fetches all lines matching query
        vector<string> read(); //Reads the whole data file
};

#endif // DATA_H
