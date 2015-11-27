#include "person.h"

using namespace std;

Person::Person()
{
    // set functions
    void set_name(string n) {name = n;};
    void set_birthyear(int y) {birthyear = y;};
    void set_deathyear(int y) {dethyear = y;};

    // get functions
    string get_name() {return name;};
    int get_birthyear() {return birth_year;};
    int get_deathyear() {return death_year;};
    string get_description() {return description;};
    string get_profession() {return profession};





}

