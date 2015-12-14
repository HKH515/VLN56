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

}
