#include "data.h"

Data::Data(string datafile)
{
    setFile(datafile);
}

void Data::setFile(string filename)
{
    internalFilename = filename;
}

string Data::getFile()
{
    return internalFilename;
}


void Data::read()
{
    ifstream inputStream;
    inputStream.open(getFile());
    string line;
    if (inputStream.is_open())
    {
        while (getline(inputStream, line))
        {
            push(line);
        }
    }

}

void Data::push(string entry)
{
    internalData.push_back(entry);
}

vector<string> Data::query(int column, string dataQuery)
{
    regex queryString(dataQuery);
    vector<string> queryVect;
    string line;
    for (unsigned int i = 0; i < internalData.size(); i++)
    {
        line = internalData[i];
        string column_content = line.substr(column, line.find("|"));
        if (regex_match(column_content.begin(), column_content.end(), queryString))
        {
            push(line);
        
        }
    }
    return queryVect;
}
