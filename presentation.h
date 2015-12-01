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
    ~presentation();
    Domain* get_domain();

    string input();
    void choice(Domain* d);
    vector <string> parse_add();
    bool check_if_year(string input);
    void print_results(Domain *d);
};

#endif // PRESENTATION_H
