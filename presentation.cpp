#include "presentation.h"

presentation::presentation()
{

}

string presentation::input()
{
    string inputs;
    cin >> inputs;

    if(inputs == "help")
    {
        cout << endl;
        cout << "--------------------" << endl;
        cout << "add. Add names and other info" << endl;
        cout << "view. View the list" << endl;
        cout << "search. search the list for info" << endl;
        cout << "sort. Sorts the list after name" << endl;
        cout << "exit. Close the program" << endl;
        cout << "--------------------" << endl;
        cin >> inputs;
    }

    return inputs;
}

void presentation::read()
{

}

void presentation::choice(string inputs, Domain* d)
{
    do
    {
        if(inputs == "add")
        {
            cout << "add name?" <<endl;
            //d->handle_commands();
        }
        else if(inputs == "view")
        {
            cout << "view the list?" <<endl;
            //data.view();
        }
        else if(inputs == "search")
        {
            cout << "search the list?" <<endl;
            //data.search();
        }
        else if(inputs == "sort")
        {
            cout << "sort the list?" <<endl;
            //data.search();
        }
    }
    while(inputs == "exit");

}

vector <string> presentation::parse_add()
{
    string input;
    vector<string> add_vec;
    cout << "You will be asked to enter information about the person, if you want to leave out information enter "-" when asked."<< endl;
    cout << "Please write the name of the person" << endl;
    cin >> input;
    add_vec.push_back(input);
    cout << "Please write some description" << endl;
    cin >> input;
    add_vec.push_back(input);


}
