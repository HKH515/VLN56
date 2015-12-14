#include "add_persons.h"
#include "ui_add_persons.h"

add_persons::add_persons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_persons)
{
    ui->setupUi(this);
    person_service = new PersonsService;
}

add_persons::~add_persons()
{
    delete ui;
    delete person_service;
}

void add_persons::on_pushbutton_add_clicked()
{
    string name = ui->name_input->text().toStdString();
    string birth_year = ui->birth_year_input->text().toStdString();
    string death_year = ui->death_year_input->text().toStdString();
    string sex = "";
    if (ui->radiobutton_male->isChecked())
    {
        sex = "m";
    }
    else if (ui->radiobutton_female->isChecked())
    {
        sex = "f";
    }
    else
    {
        sex = "o";
    }

    string profession = ui->profession_input->text().toStdString();
    string description = ui->description_input->toPlainText().toStdString();

    vector<string> add_person_vec;
    add_person_vec.push_back(name);
    add_person_vec.push_back(profession);
    add_person_vec.push_back(description);
    add_person_vec.push_back(birth_year);
    add_person_vec.push_back(death_year);
    add_person_vec.push_back(sex);
    person_service->add_person(add_person_vec);
    this->close();
}
