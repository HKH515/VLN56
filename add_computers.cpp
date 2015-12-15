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
    ui->radioButton_no->setChecked(true);
}

add_computers::~add_computers()
{
    delete ui;
    delete computer_service;
    delete verify_input;
}

void add_computers::on_cancel_pushbutton_clicked()
{
    this->close();
}



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

void add_computers::on_name_input_editingFinished()
{
    string name = ui->name_input->text().toStdString();
    if ((name != "") && (!verify_input->verify_name(name)))
    {
        ui->name_input->clear();
        display_error_msg("Invalid Name");
    }
}

void add_computers::on_construction_year_input_editingFinished()
{
    string construction_year = ui->construction_year_input->text().toStdString();
    if ((construction_year != "") && (!verify_input->verify_year(construction_year)))
    {
        ui->construction_year_input->clear();
        display_error_msg("Invalid Construction Year");
    }
}

void add_computers::display_error_msg(string error_msg)
{
    string color = "<span style='color: #ED1C58'><font size='4'>";
    string colored_error = color + error_msg;
    ui->error_label->setText(QString::fromStdString(colored_error));
    ui->error_label->show();
}
