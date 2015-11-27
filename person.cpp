#include "person.h"

using namespace std;

Person::Person()
{
    public:

    // set functions
    void set_name(string n) {name = n;};
    void set_birthyear(int y) {birthyear = y;};
    void set_deathyear(int y) {deathyear = y;};
    void set_profession(string p) {string profession};

    // get functions
    string get_name() {return name;};
    int get_birthyear() {return birth_year;};
    int get_deathyear() {return death_year;};
    string get_description() {return description;};
    string get_profession() {return profession};

    //function to calculate age
    int calc_age() {
        time_t t = time(NULL);
        tm* timePtr = localtime(&t);
        if (death_year = 0) {
            return timePtr->tm_year - birth_year;
        }
        // if the person has passed away the age is set to -1
        return -1;
    }
};

