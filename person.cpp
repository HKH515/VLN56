#include "person.h"

using namespace std;

  // set functions
void Person::set_name(string n) {name = n;};
void Person::set_birthyear(int y) {birth_year = y;};
void Person::set_deathyear(int y) {death_year = y;};

// get functions
string Person::get_name() {return name;};
int Person::get_birthyear() {return birth_year;};
int Person::get_deathyear() {return death_year;};
string Person::get_description() {return description;};
string Person::get_profession() {return profession;};

int Person::calc_age() {
        time_t t = time(NULL);
        tm* timePtr = localtime(&t);
        if (death_year = 0) {
            return timePtr->tm_year - birth_year;
        }
        // if the person has passed away the age is set to -1
        return -1;
    }
