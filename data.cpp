#include "data.h"

Data::Data(string datafile)
{
    setFile(datafile);  
}

void Data::setFile(string data)
{
    filename = data;   
}

string Data::getFile()
{
    return filename;
}

vector<string> Data::read()
{
    ifstream inputStream;
    inputStream.open(getFile())
    if (inputStream.is_open())
    {
        while (getline(inputStream, line))
        {
            push_back(line);
        }
    }
    
}

void Data::push_back(string entry)
{
    this->data.push_back(entry);
}

vector<string> Data::query(string dataQuery)
{
    vector<string> queryVect;
    for (int i = 0; i <= this->data.length(); i++)
    {
        if (regex_match(data[i], dataQuery)
        {
            queryVect.push_back(data[i]);     

        }
    }
    return queryVect;
}
