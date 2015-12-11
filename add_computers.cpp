#include "add_computers.h"
#include "ui_add_computers.h"

add_computers::add_computers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_computers)
{
    ui->setupUi(this);
}

add_computers::~add_computers()
{
    delete ui;
}
