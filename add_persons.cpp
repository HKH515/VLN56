#include "add_persons.h"
#include "ui_add_persons.h"

add_persons::add_persons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_persons)
{
    ui->setupUi(this);
    person_service = new PersonsService;
    verify_input = new Verification;

    ui->error_label->hide();
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
    this->close();

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
        display_error_msg("Invalid Name");

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
        display_error_msg("Invalid Birth Year");
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
        display_error_msg("Invalid Death Year");
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
        display_error_msg("Invalid Profession");
    }
    cout << "út ur profession" << endl;
}

void add_persons::display_error_msg(string error_msg)
{
    string color = "<span style='color: #ED1C58'><font size='4'>";
    string colored_error = color + error_msg;
    ui->error_label->setText(QString::fromStdString(colored_error));
    ui->error_label->show();
}
