#include "utils.h"

namespace utils
{
    string create_delim_string(vector<string> sourceVec, string delim)
    {
        string results = " ";
        for (unsigned int i = 0; i < sourceVec.size(); i++)
        {
            results = results + sourceVec[i] + delim;
        }
        return results;
    }

    vector<string> parse_delim_string(string delimString, char delim)
    {
        vector<string> results;

        for (int i = 0; i < count(delimString.begin(), delimString.end(), delim); i++)
        {
            results.push_back(delimString.substr(nth_index(delimString, delim, i)+1, nth_index(delimString, delim, i+1) - nth_index(delimString, delim, i)-1));
        }
        return results;
    }

    int nth_index(string haystack, char needle, int n)
    {
        int occurances = 0;
            for (unsigned int i = 0; i < haystack.size(); i++)
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

    vector<string> from_db_to_vector(string table, QSqlQuery queryObj)
    {
        vector<string> result;
        while(queryObj.next())
        {
            vector<string> tableData;
            string currentEntry = " ";
            if (table == "persons")
            {
                tableData.push_back("0");
                tableData.push_back(queryObj.value("name").toString().toStdString());
                tableData.push_back(queryObj.value("profession").toString().toStdString());
                tableData.push_back(queryObj.value("description").toString().toStdString());
                tableData.push_back(queryObj.value("birthyear").toString().toStdString());
                tableData.push_back(queryObj.value("deathyear").toString().toStdString());
                tableData.push_back(queryObj.value("sex").toString().toStdString());
                tableData.push_back(queryObj.value("id").toString().toStdString());

            }
            else if (table == "computers")
            {
                tableData.push_back("1");
                tableData.push_back(queryObj.value("name").toString().toStdString());
                tableData.push_back(queryObj.value("construction_year").toString().toStdString());
                tableData.push_back(queryObj.value("type").toString().toStdString());
                tableData.push_back(queryObj.value("built").toString().toStdString());
                tableData.push_back(queryObj.value("description").toString().toStdString());
                tableData.push_back(queryObj.value("id").toString().toStdString());

            }

            currentEntry = create_delim_string(tableData, "|");
            result.push_back(currentEntry);
        }
        return result;
    }

}
