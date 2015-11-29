//#include <QCoreApplication>
#include <iostream>

#include "data.h"
#include "person.h"
#include "Domain.h"

using namespace std;

string input();
void choice(string inputs);
void read();

/*int main(int argc, char *argv[])
{ 
    QCoreApplication a(argc, argv);

    //vector names[];

    cout << "Welcome to the Archive of all the great IT people!"<<endl;

    string inputs = input();

    choice(inputs);



    return a.exec();
}

string input()
{
    string inputs;
    cin >> inputs;

    if(inputs == "help")
    {
        cout << endl;
        cout << "--------------------" << endl;
        cout << "add. Add names and other info" << endl;
        cout << "view. View the list" << endl;
        cout << "search. search the list for info" << endl;
        cout << "sort. Sorts the list after name" << endl;
        cout << "exit. Close the program" << endl;
        cout << "--------------------" << endl;
        cin >> inputs;
    }

    return inputs;
}

void read()
{

}

void choice(string inputs)
{
    do
    {
        if(inputs == "add")
        {
            cout << "add name?" <<endl;
           //data.AddName();
        }
        else if(inputs == "view")
        {
            cout << "view the list?" <<endl;
            //data.view();
        }
        else if(inputs == "search")
        {
            cout << "search the list?" <<endl;
            //data.search();
        }
        else if(inputs == "sort")
        {
            cout << "sort the list?" <<endl;
            //data.search();
        }
    }
    while(inputs == "exit");

}*/

int main(int argc, char *argv[])
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
    
}



