#ifndef CONNECTIONS_H
#define CONNECTIONS_H


class Connections
{
private:
    int person_id;
    int computer_id;

public:
    Connections();
    int get_person_id();
    int get_computer_id();
    void set_person_id(int p);
    void set_computer_id(int c);
};

#endif // CONNECTIONS_H
