#include "add_computers.h"
#include "ui_add_computers.h"

add_computers::add_computers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_computers)
{
    ui->setupUi(this);
    computer_service = new ComputerService;
}

add_computers::~add_computers()
{
    delete ui;
    delete computer_service;
}

void add_computers::on_cancel_pushbutton_clicked()
{
    this->close();
}



void add_computers::on_add_pushbutton_clicked()
{
    string name = ui->name_input->text().toStdString();
    string construction_year = ui->construction_year_input->text().toStdString();
    string type = ui->type_input->text().toStdString();
    string built = "";
    if (ui->radioButton_yes->isChecked())
    {
        built = "1";
    }
    else if (ui->radioButton_no->isChecked())
    {
        built = "0";
    }
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
