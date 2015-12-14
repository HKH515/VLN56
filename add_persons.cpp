#include "add_persons.h"
#include "ui_add_persons.h"

add_persons::add_persons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_persons)
{
    ui->setupUi(this);
}

add_persons::~add_persons()
{
    delete ui;
}



vector<string> add_persons::on_pushbutton_add_clicked()
{
    string name = ui->name_input->text().toStdString();
    string birth_year = ui->birth_year_input->text().toStdString();
    string death_year = ui->death_year_input->text().toStdString();
    string sex = "";
    if (ui->radiobutton_male->isChecked())
    {
        sex = "male";
    }
    else if (ui->radiobutton_female->isChecked())
    {
        sex = "female";
    }
    else
    {
        sex = "other";
    }

    string profession = ui->profession_input->text().toStdString();
    string description = ui->description_input->toPlainText().toStdString();

    vector<string> add_person_vec;
    add_person_vec.push_back(name);
    add_person_vec.push_back(profession);
    add_person_vec.push_back(description);
    add_person_vec.push_back(birth_year);
    add_person_vec.push_back(birth_year);
    add_person_vec.push_back(sex);
    return add_person_vec;

}

void add_persons::on_pushbutton_cancel_clicked()
{
    this->close();
}
