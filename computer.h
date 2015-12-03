#ifndef COMPUTER_H
#define COMPUTER_H


class Computer
{
private:
    string name;
    int construction_year;
    string type;
    bool built;
    string description;

public:
    Computer();

    string get_name();
    int get_contruction_year();
    string get_type();
    bool get_built();

    void set_name(string s);
    void set_construction_year(int y);
    void set_type(string s);
    void set_built(bool b);
};

#endif // COMPUTER_H
