#include "add_connections.h"
#include "ui_add_connections.h"

add_connections::add_connections(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_connections)
{
    ui->setupUi(this);
}

add_connections::~add_connections()
{
    delete ui;
}

void add_connections::on_pushButton_cancel_clicked()
{
    this->close();
}
