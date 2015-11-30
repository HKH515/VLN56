#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <string>

#include "data.h"
#include "person.h"
#include "domain.h"
#include "presentation.h"

using namespace std;


void printSplash()
{
    ifstream splashStream("splash.txt");
    string line;

    if (splashStream.is_open())
    {
        while (getline(splashStream, line))
        {
            cout << line << endl;
        }

    } 
    splashStream.close();   
}

int main(int argc, char *argv[])
{ 
    QCoreApplication a(argc, argv);

    string inputs;

    presentation commands;

    printSplash();
    cout << "Welcome to the Archive of all the great IT people!" << endl;

    inputs = commands.input();

    Domain *d = new Domain();

    commands.choice(inputs, d);

    //choice(inputs, d);

    return a.exec();
}

