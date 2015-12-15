#include "add_persons.h"
#include "ui_add_persons.h"

add_persons::add_persons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_persons)
{
    ui->setupUi(this);
    person_service = new PersonsService;
    verify_input = new Verification;
}

add_persons::~add_persons()
{
    delete ui;
    delete person_service;
    delete verify_input;
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

}

void add_persons::on_pushbutton_cancel_clicked()
{
    this->close();
}


void add_persons::on_name_input_editingFinished()
{
    cout << "name " << endl;
    string name = ui->name_input->text().toStdString();
    if (!verify_input->verify_name(name))
    {
        ui->name_input->clear();
        ui->name_input->setText(QString::fromStdString("Invalid name"));
    }
    cout << "út ur name" << endl;
}

void add_persons::on_birth_year_input_editingFinished()
{
    cout << "birthyear " << endl;
    string birth_year = ui->birth_year_input->text().toStdString();
    if (!verify_input->verify_year(birth_year))
    {
        ui->birth_year_input->clear();
        ui->birth_year_input->setText(QString::fromStdString("Invalid birthyear"));
    }
    cout << "út ur birthyear" << endl;
}

void add_persons::on_death_year_input_editingFinished()
{
    cout << "deathyear " << endl;
    string birth_year = ui->birth_year_input->text().toStdString();
    string death_year = ui->death_year_input->text().toStdString();
    while (!verify_input->verify_deathyear(birth_year, death_year))
    {
        ui->death_year_input->clear();
        ui->death_year_input->setText(QString::fromStdString("Invalid deathyear"));
    }
    cout << "út ur deathyear" << endl;
}

void add_persons::on_profession_input_editingFinished()
{
    cout << "profession " << endl;
    string profession = ui->profession_input->text().toStdString();
    while (!verify_input->verify_profession(profession))
    {
        ui->profession_input->clear();
        ui->profession_input->setText(QString::fromStdString("Invalid profession"));
    }
    cout << "út ur profession" << endl;
}
