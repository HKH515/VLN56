#ifndef VERIFICATION_H
#define VERIFICATION_H
#include <string>
#include <iostream>

using namespace std;

class Verification
{
public:
    Verification();

    bool verify_name(string name_input);
    bool verify_profession(string profession_input);
    bool verify_year(string year_input);
    bool verify_deathyear(string birthyear_input, string deathyear_input);

private:
    bool check_if_word(string input);
    bool check_if_year(string input);
};

#endif // VERIFICATION_H
