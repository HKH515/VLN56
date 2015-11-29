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
    int birth_year;
    int death_year;
    bool sex;
    string description;
    string profession; // Mathematician, Physicist, bioligist, computer scientist

public:
    Person()
    {
        name = "";
        birth_year = 0;
        death_year = 0;
        sex = 1;
        description = "";
        profession = "";
    }
    Person (string n, int by, int dy, bool s, string desc, string prof)
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
    void set_birthyear(int y);
    void set_deathyear(int y);
    void set_sex(bool s);
    void set_description(string s);
    void set_profession(string p);

    // Get functions
    string get_name();
    int get_birthyear();
    int get_deathyear();
    int get_sex();
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
