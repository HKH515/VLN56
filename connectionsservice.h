#ifndef CONNECTIONSSERVICE_H
#define CONNECTIONSSERVICE_H

#include <vector>
#include <string>
#include "personsservice.h"
#include "computerservice.h"
#include "personRepository.h"
#include "connectionRepository.h"
#include "person.h"
#include "computer.h"

class ConnectionsService
{
private:
    vector<Person*> person_vec;
    vector<Computer*> computer_vec;
    ComputerRepository* computer_repo;
    PersonRepository* person_repo;
    ConnectionRepository* connection_repo;

public:
    ConnectionsService();

    /* Deletes all persons object from the vectors and clears the vectors before each command to be handled */
    void free_vector_memory();
    /* Handles the list command */
    void get_all_connections();
    /* Handles the add command */
    void add_connection(string person_id, string computer_id);
    /* Handles the remove command */
    void remove_connection(string person_id, string computer_id);
    /* Gets all computer/computer scientists connected to certain computer scientist/computer */
    void get_connected(vector<string> v);

};

#endif // CONNECTIONSSERVICE_H
