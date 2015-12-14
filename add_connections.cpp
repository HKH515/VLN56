#include "add_connections.h"
#include "ui_add_connections.h"

add_connections::add_connections(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_connections)
{
    ui->setupUi(this);
    connections_service = new ConnectionsService();
}

add_connections::~add_connections()
{
    delete ui;
    delete connections_service;
}

void add_connections::on_pushbutton_add_clicked()
{
    string person_ID = ui->person_dropdown->currentText().toStdString();
    string computer_ID = ui->computer_dropdown->currentText().toStdString();
    connections_service->add_connection(person_ID, computer_ID);
}

void add_connections::on_pushButton_cancel_clicked()
{
    this->close();
}
