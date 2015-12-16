#include "utils.h"

namespace utils
{
    //This function takes in a vector of strings, and returns a string of each index seperated by a specified delimeter
    string create_delim_string(vector<string> source_vec, string delim)
    {
        string results = " ";
        for (unsigned int i = 0; i < source_vec.size(); i++)
        {
            results = results + source_vec[i] + delim;
        }
        return results;
    }
    //This function does the exact opposite of create_delim_string, i.e. takes in a delimeter seperated string with data, and returns vector of the data.
    vector<string> parse_delim_string(string delim_string, char delim)
    {
        vector<string> results;

        for (int i = 0; i < count(delim_string.begin(), delim_string.end(), delim); i++)
        {
            results.push_back(delim_string.substr(nth_index(delim_string, delim, i)+1, nth_index(delim_string, delim, i+1) - nth_index(delim_string, delim, i)-1));
        }
        return results;
    }

    //This function returns the position in the string where the n'th occurance of the needle is found in the haystack string
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

    //This function returns a vector of entries from the database, each entry is a string where each field in the table is seperated by a '|' character
    vector<string> from_db_to_vector(string table, QSqlQuery query_obj)
    {
        vector<string> result;
        while(query_obj.next())
        {
            vector<string> table_data;
            string current_entry = " ";
            if (table == "persons")
            {
                table_data.push_back("0");
                table_data.push_back(query_obj.value("name").toString().toStdString());
                table_data.push_back(query_obj.value("profession").toString().toStdString());
                table_data.push_back(query_obj.value("description").toString().toStdString());
                table_data.push_back(query_obj.value("birthyear").toString().toStdString());
                table_data.push_back(query_obj.value("deathyear").toString().toStdString());
                table_data.push_back(query_obj.value("sex").toString().toStdString());
                table_data.push_back(query_obj.value("id").toString().toStdString());

            }
            else if (table == "computers")
            {
                table_data.push_back("1");
                table_data.push_back(query_obj.value("name").toString().toStdString());
                table_data.push_back(query_obj.value("construction_year").toString().toStdString());
                table_data.push_back(query_obj.value("type").toString().toStdString());
                table_data.push_back(query_obj.value("built").toString().toStdString());
                table_data.push_back(query_obj.value("description").toString().toStdString());
                table_data.push_back(query_obj.value("id").toString().toStdString());

            }

            current_entry = create_delim_string(table_data, "|");
            result.push_back(current_entry);
        }
        return result;
    }

}
