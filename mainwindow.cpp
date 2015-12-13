#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_computers.h"
#include "add_persons.h"
#include "add_connections.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    person_service = new PersonsService();
    computer_service = new ComputerService();
    connections_service = new ConnectionsService();

    ui->setupUi(this);
    ui->see_more_view_person->hide();
    ui->see_more_view_computer->hide();
    ui->search_view->hide();
    ui->table_view_connections->hide();
    ui->table_view_computers->hide();
    display_person_list();

    ui->table_view_person->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_view_computers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_view_connections->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->profession_output->setReadOnly(true);
    ui->description_output_person->setReadOnly(true);
    ui->description_output_computer->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete person_service;
    delete computer_service;
    delete connections_service;
}

void MainWindow::on_search_pushButton_clicked()
{
    ui->search_view->show();
    ui->see_more_view_computer->hide();
    ui->see_more_view_person->hide();
}

void MainWindow::on_substring_input_returnPressed()
{
    ui->search_view->hide();
}

void MainWindow::display_person_list()
{
    ui->search_view->hide();
    ui->table_view_person->show();
    ui->table_view_connections->hide();
    ui->table_view_computers->hide();
    person_service->get_all_persons();
    unsigned int vector_size = person_service->get_person_vec().size();
    ui->table_view_person->setRowCount(vector_size);

    for (unsigned int row = 0; row < vector_size; row++)
    {
        Person* current_person = person_service->get_person_vec()[row];
        QString name = QString::fromStdString(current_person->get_name());
        QString birthyear = QString::number(current_person->get_birthyear());
        QString deathyear = QString::number(current_person->get_deathyear());
        QString sex = QString::fromStdString(current_person->get_sex());

        ui->table_view_person->setItem(row, 0, new QTableWidgetItem(name));
        ui->table_view_person->setItem(row, 1, new QTableWidgetItem(birthyear));
        ui->table_view_person->setItem(row, 2, new QTableWidgetItem(deathyear));
        ui->table_view_person->setItem(row, 3, new QTableWidgetItem(sex));
    }
    person_vector = person_service->get_person_vec();
}

void MainWindow::display_computer_list()
{
    ui->search_view->hide();
    ui->table_view_person->hide();
    ui->table_view_connections->hide();
    ui->table_view_computers->show();
    computer_service->get_all_computers();
    unsigned int vector_size = computer_service->get_computer_vec().size();
    ui->table_view_computers->setRowCount(vector_size);

    for (unsigned int row = 0; row < vector_size; row++)
    {
        Computer* current_computer = computer_service->get_computer_vec()[row];
        QString name = QString::fromStdString(current_computer->get_name());
        QString construction_year = QString::number(current_computer->get_construction_year());
        QString type = QString::fromStdString(current_computer->get_type());
        QString built = QString::number(current_computer->get_built());

        ui->table_view_computers->setItem(row, 0, new QTableWidgetItem(name));
        ui->table_view_computers->setItem(row, 1, new QTableWidgetItem(construction_year));
        ui->table_view_computers->setItem(row, 2, new QTableWidgetItem(type));
        ui->table_view_computers->setItem(row, 3, new QTableWidgetItem(built));
    }
    computer_vector = computer_service->get_computer_vec();
}

void MainWindow::display_connections_list()
{

}


void MainWindow::on_type_dropdown_currentIndexChanged(const QString &arg1)
{
    ui->search_view->hide();
    ui->see_more_view_computer->hide();
    ui->see_more_view_person->hide();
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
    ui->remove_pushButton->setEnabled(false);
    ui->show_more_pushButton->setEnabled(false);
}

void MainWindow::on_table_view_person_clicked(const QModelIndex &index)
{
    ui->remove_pushButton->setEnabled(true);
    ui->show_more_pushButton->setEnabled(true);
}

void MainWindow::on_show_more_pushButton_clicked()
{
    ui->search_view->hide();
    string current_type = ui->type_dropdown->currentText().toStdString();
    int currently_chosen_entry;
    if (current_type == "Computer Scientists")
    {
        ui->see_more_view_computer->hide();
        ui->description_output_person->clear();
        currently_chosen_entry = ui->table_view_person->currentIndex().row();
        Person* current_person = person_vector.at(currently_chosen_entry);
        QString current_profession = QString::fromStdString(current_person->get_profession());
        QString current_description = QString::fromStdString(current_person->get_description());
        ui->profession_output->setText(current_profession);
        ui->description_output_person->append(current_description);
        ui->see_more_view_person->show();

    }
    else if (current_type == "Computers")
    {
        ui->see_more_view_person->hide();
        ui->description_output_computer->clear();
        currently_chosen_entry = ui->table_view_computers->currentIndex().row();
        Computer* current_computer = computer_vector.at(currently_chosen_entry);
        QString current_description = QString::fromStdString(current_computer->get_description());
        ui->description_output_computer->append(current_description);
        ui->see_more_view_computer->show();
    }
}

void MainWindow::on_table_view_computers_clicked(const QModelIndex &index)
{
    ui->remove_pushButton->setEnabled(true);
    ui->show_more_pushButton->setEnabled(true);
}

void MainWindow::on_table_view_connections_clicked(const QModelIndex &index)
{
    ui->remove_pushButton->setEnabled(true);
    ui->show_more_pushButton->setEnabled(true);
}

void MainWindow::on_remove_pushButton_clicked()
{
    string current_type = ui->type_dropdown->currentText().toStdString();
    int currently_chosen_entry;
    if (current_type == "Computer Scientists")
    {
        ui->see_more_view_computer->hide();
        ui->description_output_person->clear();
        currently_chosen_entry = ui->table_view_person->currentIndex().row();
        QTableWidgetItem *entry_name = ui->table_view_person->item(currently_chosen_entry, 0);
        string name = entry_name->text().toStdString();
        vector<Person*> person_vec = person_service->get_person_vec();
        for (int i = 0; i < person_vec.size(); i++)
        {
            if (person_vec[i]->get_name() == name)
            {
                int id = person_vec[i]->get_id();
                stringstream ss;
                ss << id;
                string str_id = ss.str();
                person_service->remove_person(str_id);
            }
        }

        display_person_list();
    }
    else if (current_type == "Computers")
    {
        ui->see_more_view_person->hide();
        ui->description_output_computer->clear();
        currently_chosen_entry = ui->table_view_computers->currentIndex().row();
        QTableWidgetItem *entry_name = ui->table_view_computers->item(currently_chosen_entry, 0);
        string name = entry_name->text().toStdString();
        vector<Computer*> computer_vec = computer_service->get_computer_vec();
        for (int i = 0; i < computer_vec.size(); i++)
        {
            if (computer_vec[i]->get_name() == name)
            {
                int id = computer_vec[i]->get_id();
                stringstream ss;
                ss << id;
                string str_id = ss.str();
                computer_service->remove_computer(str_id);
            }
        }

        display_computer_list();
    }
}

void MainWindow::on_add_pushButton_clicked()
{
    string current_type = ui->type_dropdown->currentText().toStdString();

    if (current_type == "Computer Scientists")
    {
        add_persons newadd_persons;

        int addComputersReturnValue = newadd_persons.exec();
    }
    else if (current_type == "Computers")
    {
        add_computers newadd_computers;

        int addPersonsReturnValue = newadd_computers.exec();
    }
    else if (current_type == "Connections")
    {
        add_connections newadd_connections;

        int addConnectionsReturnValue = newadd_connections.exec();
    }
}

