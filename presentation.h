#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <string>
#include <vector>

#include "domain.h"
#include "person.h"
#include "data.h"

class presentation
{
private:
    Domain *d;

public:
    presentation();

    string input();
    void choice(string inputs, Domain* d);
    void read();
};

#endif // PRESENTATION_H
