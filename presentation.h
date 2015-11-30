#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <string>
#include <vector>
#include <ctype.h>
#include <stdio.h>

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
    vector <string> parse_add();
    bool check_if_year(string input);
};

#endif // PRESENTATION_H
