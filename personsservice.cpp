#include "personService.h"

PersonsService::PersonsService()
{
    person_repo = new PersonRepository("data.sqlite", "person_repo_connection");
}

