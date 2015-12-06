#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <vector>

class Person;

using namespace std;

class Computer
{
private:
    string name;
    int construction_year;
    string type;
    int built;
    string description;
    int id;
    vector<string> per_associated;

public:
    Computer();
    string get_name();
    int get_construction_year();
    string get_type();
    int get_built();
    int get_id();
    string get_description();

    vector<string> get_vec();

    void set_name(string s);
    void set_construction_year(int y);
    void set_type(string s);
    void set_built(int b);
    void set_description(string s);
    void set_id(int i);
};

#endif // COMPUTER_H
