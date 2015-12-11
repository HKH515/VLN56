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
