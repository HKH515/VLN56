#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    person_service = new PersonsService();
    computer_service = new ComputerService();
    connections_service = new ConnectionsService();

    ui->setupUi(this);
    ui->see_more_view->hide();
    ui->search_view->hide();
    display_person_list();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_search_pushButton_clicked()
{
    ui->search_view->show();
}

void MainWindow::on_substring_input_returnPressed()
{
    ui->search_view->hide();
}

void MainWindow::display_person_list()
{
    person_service->get_all_persons();
    unsigned int vector_size = person_service->get_person_vec().size();
    ui->table_view->setRowCount(vector_size);

    for (unsigned int row = 0; row < vector_size; row++)
    {
        Person* current_person = person_service->get_person_vec()[row];
        QString name = QString::fromStdString(current_person->get_name());
        QString birthyear = QString::number(current_person->get_birthyear());
        QString deathyear = QString::number(current_person->get_deathyear());
        QString sex = QString::fromStdString(current_person->get_sex());

        ui->table_view->setItem(row, 0, new QTableWidgetItem(name));
        ui->table_view->setItem(row, 1, new QTableWidgetItem(birthyear));
        ui->table_view->setItem(row, 2, new QTableWidgetItem(deathyear));
        ui->table_view->setItem(row, 3, new QTableWidgetItem(sex));
    }
}

void MainWindow::display_computer_list()
{
    computer_service->get_all_computers();
    unsigned int vector_size = computer_service->get_computer_vec().size();
    ui->table_view->setRowCount(vector_size);

    for (unsigned int row = 0; row < vector_size; row++)
    {
        Computer* current_computer = computer_service->get_computer_vec()[row];
        QString name = QString::fromStdString(current_computer->get_name());
        QString construction_year = QString::number(current_computer->get_construction_year());
        QString type = QString::fromStdString(current_computer->get_type());

        ui->table_view->setItem(row, 0, new QTableWidgetItem(name));
        ui->table_view->setItem(row, 1, new QTableWidgetItem(construction_year));
        ui->table_view->setItem(row, 2, new QTableWidgetItem(type));
    }
}

void MainWindow::display_connections_list()
{

}


void MainWindow::on_type_dropdown_currentIndexChanged(const QString &arg1)
{
    string current_type = ui->type_dropdown->currentText().toStdString();
    if (current_type == "Computer Scientists")
    {
        display_person_list();
    }
    else if (current_type == "Computers")
    {
        display_computer_list();
    }
    else
    {
        display_connections_list();
    }
}
