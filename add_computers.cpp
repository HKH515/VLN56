#include "add_computers.h"
#include "ui_add_computers.h"

add_computers::add_computers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_computers)
{
    ui->setupUi(this);
    computer_service = new ComputerService();
    verify_input = new Verification();

    ui->error_label->hide();
    ui->radioButton_no->setChecked(true); // Makes the computer not built by default
    ui->add_pushbutton->setEnabled(false);
}

add_computers::~add_computers()
{
    delete ui;
    delete computer_service;
    delete verify_input;
}

// to close the window
void add_computers::on_cancel_pushbutton_clicked()
{
    this->close();
}


// constructs a vector of informations from the user input and sends down to domain-layer
void add_computers::on_add_pushbutton_clicked()
{
    string name = ui->name_input->text().toStdString();
    string construction_year = ui->construction_year_input->text().toStdString();
    string built = "";
    if (ui->radioButton_yes->isChecked())
    {
        built = "1";
    }
    else if (ui->radioButton_no->isChecked())
    {
        built = "0";
    }
    string type = ui->type_dropdown->currentText().toStdString();
    string description = ui->description_input->toPlainText().toStdString();

    vector<string> add_computer_vec;
    add_computer_vec.push_back(name);
    add_computer_vec.push_back(construction_year);
    add_computer_vec.push_back(type);
    add_computer_vec.push_back(built);
    add_computer_vec.push_back(description);
    computer_service->add_computer(add_computer_vec);

    this->close();
}

// When name is entered the function validates the input and displays error msg if need be
void add_computers::on_name_input_editingFinished()
{
    string name = ui->name_input->text().toStdString();
    if ((name != "") && (!verify_input->verify_name(name)))
    {
        ui->name_input->clear();
        display_error_msg("Invalid Name");
    }
    enable_add_button();
}

// When construction year is entered the function validates the input and displays error msg if need be
void add_computers::on_construction_year_input_editingFinished()
{
    string construction_year = ui->construction_year_input->text().toStdString();
    if ((construction_year != "") && (!verify_input->verify_year(construction_year)))
    {
        ui->construction_year_input->clear();
        display_error_msg("Invalid Construction Year");
    }
    enable_add_button();
}

// displays message if input into certains field are not valid
void add_computers::display_error_msg(string error_msg)
{
    string color = "<span style='color: #ED1C58'><font size='4'>"; // the text is in large red letters
    string colored_error = color + error_msg;
    ui->error_label->setText(QString::fromStdString(colored_error));
    ui->error_label->show();
}

// The add button is only activated if both name and construction year fields are not empty
void add_computers::enable_add_button()
{
    if (ui->construction_year_input->text().isEmpty() || ui->name_input->text().isEmpty())
    {
        ui->add_pushbutton->setEnabled(false);
    }
    else
    {
        ui->add_pushbutton->setEnabled(true);
    }
}
