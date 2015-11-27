#include <QCoreApplication>
#include <iostream>

#include "data.h"
#include "person.h"

using namespace std;

string input();
void choice(string inputs);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    string inputs = input();

    choice(inputs);



    return a.exec();
}

string input()
{
    string inputs;

    cout << endl;
    cout << "--------------------" << endl;
    cout << "add. Add names and other info" << endl;
    cout << "search. search the list for info" << endl;
    cout << "sort. Sorts the list after name" << endl;
    cout << "exit. Close the program" << endl;
    cout << "--------------------" << endl;

    cin >> inputs;

    return inputs;
}

void choice(string inputs)
{
   string name;
    do
    {
        if(inputs == "add")
        {
            cout << "add name?" <<endl;
           //data.AddName();
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

}




