#include "domain.h"

// Parse function for queries returned from the data layer. Parses
void Domain::parse_query_vector(vector<string> v) {
    
    for (unsigned int i = 0; i < v.size(); i++) {
        string st = v[i];
        Person p = Person();
        // find the name
        unsigned long position_beg = st.find("|");
        p.set_name(st.substr(0, position_beg));
        // find the birthyear
        unsigned long position_end = st.find("|", position_beg + 1);
        p.set_birthyear(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));
        // find the deathyear
        position_beg = st.find("|", position_end + 1);
        p.set_deathyear(stoi(st.substr(position_end + 1, (position_beg - position_end - 1))));
        // find the sex
        position_end = st.find("|", position_beg + 1);
        p.set_sex(stoi(st.substr(position_beg + 1, (position_end - position_beg - 1))));
        // find the description
        position_beg = st.find("|", position_end + 1);
        p.set_description(st.substr(position_end + 1, (position_beg - position_end - 1)));
        // find the profession
        position_end = st.find("|", position_beg + 1);
        p.set_profession(st.substr(position_beg + 1, (position_end - position_beg - 1)));
        vec.push_back(p);
    }
}

/*bool Domain::greater(Person lhs, Person rhs)
{
    return lhs.get_name() > rhs.get_name();
}*/

// Sort
void Domain::sort_ascending(vector<Person> &v)
{
    stable_sort(v.begin(), v.end());
}

/*void Domain::sort_descending(vector<Person> &v)
{
    stable_sort(v.begin(), v.end(), greater);
}*/

