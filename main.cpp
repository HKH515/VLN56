#include <QCoreApplication>
#include <iostream>

#include "data.h"
#include "person.h"
#include "domain.h"

using namespace std;



int main(int argc, char *argv[])
{ 
    QCoreApplication a(argc, argv);

    //vector names[];

    cout << "Welcome to the Archive of all the great IT people!"<<endl;


    Domain *d = new Domain();
    //choice(inputs, d);

    return a.exec();
}

