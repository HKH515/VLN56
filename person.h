#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include <ctime>
#include "computer.h"
#include <vector>

using namespace std;

class Person
{
private:
    string name;
    int birth_year;
    int death_year;
    string sex;
    string description;
    string profession; // Mathematician, Physicist, bioligist, computer scientist
    int id;
    
public:
    /* Constructor */
    Person();

    /* Set functions */
    void set_name(string n);
    void set_birthyear(int y);
    void set_deathyear(int y);
    void set_sex(string s);
    void set_description(string s);
    void set_profession(string p);
    void set_id(int i);

    /* Get functions */
    string get_name();
    int get_birthyear();
    int get_deathyear();
    string get_sex();
    string get_description();
    string get_profession();
    int get_id();

};

#endif // PERSON_H
