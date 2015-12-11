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

    /* Dropdown menu for types of information */
    ui->type_dropdown->addItem(QString::fromStdString("Computer Scientists"));
    ui->type_dropdown->addItem("Computer");
    ui->type_dropdown->addItem("Connections");

    display_person_list();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::display_person_list()
{
    ui->table_view->clearContents();

    ui->table_view->setRowCount(13);
    person_service->get_all_persons();

    for (unsigned int row = 0; row < 13; row++)
    {
        Person* current_person = person_service->get_person_vec()[row];
        QString name = QString::fromStdString(current_person->get_name());
        QString birthyear = QString::number(current_person->get_birthyear());
        QString deathyear = QString::number(current_person->get_deathyear());
        QString sex = QString::fromStdString(current_person->get_sex());
        ui->table_view->setItem(row, 0, new QTableWidgetItem(name));
        ui->table_view->setItem(row, 1, new QTableWidgetItem(birthyear));
        ui->table_view->setItem(row, 2, new QTableWidgetItem(deathyear));
    }

}

void MainWindow::on_search_pushButton_clicked()
{
    ui->search_view->show();
}

void MainWindow::on_substring_input_returnPressed()
{
    ui->search_view->hide();
}

void MainWindow::on_table_view_clicked(const QModelIndex &index)
{
    ui->remove_pushButton->setEnabled(true);
    ui->show_more_pushButton->setEnabled(true);
}



void MainWindow::on_remove_pushButton_clicked()
{
    int curr_selected_elem = ui->table_view->currentIndex().row();
}
