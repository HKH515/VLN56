#include "connectionsservice.h"

ConnectionsService::ConnectionsService()
{
    computer_repo = new ComputerRepository("data.sqlite", "computer_connection");
    person_repo = new PersonRepository("data.sqlite", "person_computer");
}

ConnectionsService::~ConnectionsService()
{
    free_vector_memory();
    delete computer_repo;
    delete person_repo;
    delete connection_repo;
}

void ConnectionsService::free_vector_memory()
{
    for (unsigned int i = 0; i < person_vec.size(); i++)
    {
        delete person_vec[i];
    }
    for (unsigned int i = 0; i < computer_vec.size(); i++)
    {
        delete computer_vec[i];
    }
}

void ConnectionsService::get_all_connections()
{
    free_vector_memory();



}

void ConnectionsService::add_connection(string person_id, string computer_id)
{
    free_vector_memory();

}

void ConnectionsService::remove_connection(string person_id, string computer_id)
{

}

void ConnectionsService::get_connected(vector<string> v)
{

}

