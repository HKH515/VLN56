#include <QCoreApplication>
#include <iostream>

#include "data.h"
#include "person.h"
#include "domain.h"

using namespace std;

string input();
void choice(string inputs);


int main(int argc, char *argv[])
{ 
    QCoreApplication a(argc, argv);

   // Person name, birth_year, death_year, sex, description, profession;

   // vector<string> people;

    cout << "Welcome to the Archive of all the great Computer science people!"<<endl;

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
        cout << "delete. Delete an entry"<< endl;
        cout << "search. search the list for info" << endl;
        cout << "sort. Sorts the list after name" << endl;
        cout << "exit. Close the program" << endl;
        cout << "--------------------" << endl;
        cin >> inputs;
    }

    return inputs;
}



void choice(string inputs)
{
    int entry;
    string querySearch;
    string name;

    do
    {
        if(inputs == "add")
        {
           cout << "Input name: " << name <<  "|" << endl;

        }
        else if(inputs == "view")
        {



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




