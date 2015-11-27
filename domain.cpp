#include "domain.h"

//void Domain::sort_ascending(vector<Person> v);


void Domain::parse_query_vector(vector<string> v) {

    for (unsigned int i = 0; i < v.size(); i++) {
        string st = v[i];
        Person* p = new Person();
        int position_beg = st.find("|");
        p->set_name(st.substr(0,position));
        int position_end = st.find("|", position_beg);
        p->set_birthyear(st.substr(position_beg + 1, position_end));
    }
}

