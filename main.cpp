#include <QCoreApplication>
#include <iostream>

#include "data.h"
#include "person.h"
#include "domain.h"

#include <string>
#include <sstream>
#include <vector>

using namespace std;

string input();
void choice(string inputs);

vector<string> &split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);


int main(int argc, char *argv[])
{ 
    QCoreApplication a(argc, argv);

    //vector<string> choices;


    cout << "Welcome to the Archive of all the great Computer science people!"<<endl;

    string inputs = input();

    choice(inputs);



    return a.exec();
}

string input()
{
    string inputs;
    cin >> inputs;

    vector<string> &elems;


    if(inputs == "help")
    {
        cout << endl;
        cout << "--------------------" << endl;
        cout << "add. Add names and other info" << endl;
        cout << "list. View the list" << endl;
        cout << "delete. Delete an entry"<< endl;
        cout << "search. search the list for info" << endl;
        cout << "sort. Sorts the list after name" << endl;
        cout << "exit. Close the program" << endl;
        cout << "--------------------" << endl;
        cin >> inputs;
    }
    //else if()

    split(inputs, ':', elems);

    return inputs;
}

vector<string> &split(string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


/*vector<string> split(string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}*/



void choice(string inputs)
{
    int entry;
    string querySearch;
    string name;

    do
    {
        if(inputs == "add")
        {

           cout << "Input name: " << endl;
           cin >> name;

        }
        else if(inputs == "list")
        {
            string string1;
            string string2;
            string string3;
            vector<string> v;
            v.push_back(string1);
            v.push_back(string2);
            v.push_back(string3);

            for(unsigned int i = 0; i < v.size(); i++)
            {
                cout << v[i] << endl;
            }


            if(inputs == "sort")
            {
                cout << "Sorting the list after names..."<<endl;

            }
            else if(inputs == "delete")
            {
                cout << "What entry do you want to delete?"<<endl;
                cin >> entry;

            }
            else if(inputs == "search")
            {
                cout << "Input search query: "<<endl;
                cin >> querySearch;
            }
        }
        else if(inputs == "delete")
        {
            cout << "What entry do you want to delete?"<<endl;
            cin >> entry;
        }
        else if(inputs == "search")
        {
            cout << "Input search query: "<<endl;
            cin >> querySearch;
        }

    }
    while(inputs == "exit");

}

/*int main(int argc, char *argv[])
{
    string string1 = "Kalli|1982|2005|0|biology";
    string string2 = "Alli|1980|2000|0|math";
    string string3 = "Bergdis|1970|0|0|math";
    vector<string> v;
    v.push_back(string1);
    v.push_back(string2);
    v.push_back(string3);
    
    for(unsigned int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }
    
    Domain* d = new Domain();
    
    d->parse_query_vector(v);
    
    cout << endl;
    
    for(unsigned int i = 0; i < d->vec.size(); i++)
    {
        cout << d->vec[i] << endl;
    }
    d->sort_ascending(d->vec);
    
    cout << endl;
    
    for(unsigned int i = 0; i < d->vec.size(); i++)
    {
        cout << d->vec[i] << endl;
    }
    
    //d->sort_descending(d->vec);
    
    cout << endl;
    
    for(unsigned int i = 0; i < d->vec.size(); i++)
    {
        cout << d->vec[i] << endl;
    }
    
}*/



