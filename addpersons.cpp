#include "addpersons.h"
#include "ui_add_persons.h"

add_persons::add_persons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_persons)
{
    ui->setupUi(this);
    person_service = new PersonsService;
    verify_input = new Verification;

    ui->error_label->hide();
    ui->radiobutton_other->setChecked(true);
    ui->pushbutton_add->setEnabled(false);
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

// Closes the add window
void add_persons::on_pushbutton_cancel_clicked()
{
    this->close();
}

// Gets the name from the user input and validates it, sends error msg if
// the name contains numbers or symbols
void add_persons::on_name_input_editingFinished()
{
    string name = ui->name_input->text().toStdString();
    if ((name != "") && (!verify_input->verify_name(name)))
    {
        ui->name_input->clear();
        display_error_msg("Invalid Name");
    }
    enable_add_button();
}

// Gets the birth year from the user input and validates it, sends error msg if
// the birth year is negative or contains letters or symbols
void add_persons::on_birth_year_input_editingFinished()
{
    string birth_year = ui->birth_year_input->text().toStdString();
    if ((birth_year != "") && (!verify_input->verify_year(birth_year)))
    {
        ui->birth_year_input->clear();
        display_error_msg("Invalid Birth Year");
    }
    enable_add_button();
}

// Gets the death year from the user input and validated it, sends error msg if
// the deathyear is negative or contains letters and symbols
void add_persons::on_death_year_input_editingFinished()
{
    string death_year = ui->death_year_input->text().toStdString();
    if ((death_year != "") && (!verify_input->verify_year(death_year)))
    {
        ui->death_year_input->clear();
        display_error_msg("Invalid Death Year");
    }
    enable_add_button();
}

// Gets the profession from the user input and validates it, sends error msg if the profession
// contains numbers or symbols.
void add_persons::on_profession_input_editingFinished()
{
    string profession = ui->profession_input->text().toStdString();
    if ((profession != "") && (!verify_input->verify_profession(profession)))
    {
        ui->profession_input->clear();
        display_error_msg("Invalid Profession");
    }
    enable_add_button();
}

// Displays error msg if the user input is invalid
void add_persons::display_error_msg(string error_msg)
{
    string color = "<span style='color: #ED1C58'><font size='4'>";
    string colored_error = color + error_msg;
    ui->error_label->setText(QString::fromStdString(colored_error));
    ui->error_label->show();
}

// When all necessary information have been entered the add button is enabled
void add_persons::enable_add_button()
{
    if (ui->name_input->text().isEmpty() || ui->profession_input->text().isEmpty() || ui->birth_year_input->text().isEmpty() || ui->death_year_input->text().isEmpty())
    {
        ui->pushbutton_add->setEnabled(false);
    }
    else
    {
        ui->pushbutton_add->setEnabled(true);
    }
}
