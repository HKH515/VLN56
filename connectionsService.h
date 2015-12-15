#ifndef CONNECTIONSSERVICE_H
#define CONNECTIONSSERVICE_H

#include <vector>
#include <string>
#include <sstream>
#include "personsservice.h"
#include "computerservice.h"
#include "personRepository.h"
#include "connectionRepository.h"
#include "person.h"
#include "computer.h"

class ConnectionsService
{
private:
    vector<Person*> person_vec; // Stores all persons that have a connection
    vector<Computer*> computer_vec; // Stores all computers that have a connection
    ConnectionRepository* connection_repo; // Data layer

public:
    ConnectionsService();
    ~ConnectionsService();

    // Get functions
    vector<Person*> get_person_vec();
    vector<Computer*> get_computer_vec();
    // Deletes all persons object from the person_vec and clears the vector
    void free_person_vector_memory();
    // Deletes all computer objects from the computer_vec and clears the vector
    void free_computer_vector_memory();
    // List all connections
    void get_all_connections();
    // Adds a connection to the database
    void add_connection(string person_id, string computer_id);
    // Removes a connection from the database
    void remove_connection(int person_id, int computer_id);
    // Gets all computers/scientists connected to certain scientist/computer
    void get_connected(string kind, string name);
    // Parses vector from the data layer and fills into Person* and Computer* objects and pushbacks to person_vec and computer_vec
    void parse_query_vector(vector<string> v);
    // Returns the Person object for the person with name 'name'
    Person* find_chosen_person(string name);
    // Returns the Computer object for the computer with name 'name'
    Computer* find_chosen_computer(string name);
    // Changes the input integer to string
    string int_to_string(int id);

};

#endif // CONNECTIONSSERVICE_H
