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

    QFile readFile(getFile().c_str());



    if (readFile.open(QIODevice::ReadOnly ))
    {
        QTextStream inputStream(&readFile);
        QTextStream out(stdout);
        QString line;
        internalData.clear();

        do
        {
            line = inputStream.readLine();
            push(line.toStdString());
        } while (!line.isNull());

    }
    readFile.close();




    /*ifstream inputStream(getFile().c_str());
    string line;
    if (inputStream.is_open())
    {
        while (getline(inputStream, line))
        {
            push(line);
        }
    }


    inputStream.close();
    */
}

void Data::write(string line)
{
    QString lineString(line.c_str());
    QString getFileString(getFile().c_str());
    QFile dataFile(getFileString);

    if (dataFile.open(QIODevice::ReadWrite | QIODevice::Append))
    {
        QTextStream out(&dataFile);
        out << lineString << endl;

    }
    dataFile.close();
}

vector<string> Data::readEntries()
{
    return internalData;
}

void Data::push(string entry)
{
    internalData.push_back(entry);
}

int Data::nthIndex(string haystack, char needle, int n)
{
    int occurances = 0;
    for (int i = 0; i < haystack.size(); i++)
    {
        if (haystack[i] == needle)   
        {
            occurances++;
        }        
        if (occurances == n)
        {
            return i;
        }
    }
    return haystack.size()-1; //fallback if char is not found, return end of string


}

vector<string> Data::query(int column, string dataQuery)
{
    vector<string> queryVect;
    string line;
    cout << internalData.size() << endl;
    int dataSize = internalData.size();
    for (unsigned int i = 0; i < dataSize; i++)
    {
        line = internalData[i];

        string column_content = line.substr(nthIndex(line, '|', column)+1, nthIndex(line, '|', column+1)-nthIndex(line, '|', column)-1);
        if (column_content.find(dataQuery) != string::npos) //if query is found in current cell
        {
            queryVect.push_back(line);
        }
    }
    return queryVect;
}
