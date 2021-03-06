#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDir>
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
    QFile splashFile("splash.txt");

    if (splashFile.open(QIODevice::ReadOnly ))
    {
        QTextStream splash(&splashFile);
        QTextStream out(stdout);
        QString line = splash.readLine();

        do
        {
            line = splash.readLine();

            out << line << endl;
        } while (!line.isNull());

    }
    splashFile.close();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    printSplash();
    cout << "Welcome to the Archive of all the great Computer Scientists and Computers!" << endl << "> ";

    presentation* p = new presentation();
    p->choice();

    return a.exec();
}
