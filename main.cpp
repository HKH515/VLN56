#include <QCoreApplication>
#include <iostream>

#include "data.h"
#include "person.h"

using namespace std;

string input();
void choice(string inputs, vector<string> people);


int main(int argc, char *argv[])
{ 
    QCoreApplication a(argc, argv);



    vector<string> people;

    cout << "Welcome to the Archive of all the great Computer science people!"<<endl;

    string inputs = input();

    choice(inputs, people);



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
        cout << "delete. Delete an entry"<< endl;
        cout << "search. search the list for info" << endl;
        cout << "sort. Sorts the list after name" << endl;
        cout << "exit. Close the program" << endl;
        cout << "--------------------" << endl;
        cin >> inputs;
    }

    return inputs;
}



void choice(string inputs, vector<string> people)
{
    do
    {
        if(inputs == "add")
        {

        }
        else if(inputs == "view")
        {

        }
        else if(inputs == "delete")
        {

        }
        else if(inputs == "search")
        {

        }
        else if(inputs == "sort")
        {

        }
    }
    while(inputs == "exit");

}




