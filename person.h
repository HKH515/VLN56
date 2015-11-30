#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include <ctime>

using namespace std;

class Person
{
private:
    string name;
    string birth_year;
    string death_year;
    string sex;
    string description;
    string profession; // Mathematician, Physicist, bioligist, computer scientist

public:
    Person()
    {
        name = "";
        birth_year = "";
        death_year = "";
        sex = "f";
        description = "";
        profession = "";
    }
    Person (string n, string by, string dy, string s, string desc, string prof)
    {
        name = n;
        birth_year = by;
        death_year = dy;
        sex = s;
        description = desc;
        profession = prof;
    }
    // Set functions
    void set_name(string n);
    void set_birthyear(string y);
    void set_deathyear(string y);
    void set_sex(string s);
    void set_description(string s);
    void set_profession(string p);

    // Get functions
    string get_name();
    string get_birthyear();
    string get_deathyear();
    string get_sex();
    string get_description();
    string get_profession();

    friend bool operator < (const Person &lhs, const Person &rhs);
    friend bool operator > (const Person &lhs, const Person &rhs);
    friend ostream& operator <<(ostream& outs, const Person &p);
    void operator = (const Person& rhs);
    // copy constructor
    Person(const Person& copyme);

    int calc_age();
};

#endif // PERSON_H
