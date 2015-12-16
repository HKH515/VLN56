#include "addconnections.h"
#include "ui_addconnections.h"

add_connections::add_connections(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_connections)
{
    ui->setupUi(this);
    connections_service = new ConnectionsService();
    person_service = new PersonsService();
    computer_service = new ComputerService();

    // Gets all Scientist and Computers in database in certain order
    get_all_persons_ids();
    get_all_computer_ids();
}

add_connections::~add_connections()
{
    delete ui;
    delete connections_service;
    delete person_service;
    delete computer_service;
}

void add_connections::on_pushbutton_add_clicked()
{
    string name_person = ui->person_dropdown->currentText().toStdString();
    // get all information about the person with name_person
    Person *current_person = person_service->find_chosen_person_by_name(name_person);
    string person_id = connections_service->int_to_string(current_person->get_id());
    string name_computer = ui->computer_dropdown->currentText().toStdString();
    // get all information about the computer with name_computer
    Computer *current_computer = computer_service->find_chosen_computer_by_name(name_computer);
    string computer_id = connections_service->int_to_string(current_computer->get_id());
    connections_service->add_connection(person_id, computer_id); // add connection do database
    this->close();
}

// Close the window
void add_connections::on_pushButton_cancel_clicked()
{
    this->close();
}

// Add all Scientist to the dropdown
void add_connections::get_all_persons_ids()
{
    person_service->get_all_persons();
    vector<Person*> person_vec = person_service->get_person_vec();
    for (unsigned int i = 0; i < person_vec.size(); i++)
    {
        ui->person_dropdown->addItem(QString::fromStdString(person_vec[i]->get_name()));
    }
}

// Add all Computers to the dropdown
void add_connections::get_all_computer_ids()
{
    computer_service->get_all_computers();
    vector<Computer*> computer_vec = computer_service->get_computer_vec();
    for (unsigned int i = 0; i < computer_vec.size(); i++)
    {
        ui->computer_dropdown->addItem(QString::fromStdString(computer_vec[i]->get_name()));
    }
}

