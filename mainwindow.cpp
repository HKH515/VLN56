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
    ui->search_view_person->hide();
    ui->search_view_computer->hide();
    ui->table_view_connections->hide();
    ui->table_view_computers->hide();
    display_person_list(1);

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
    ui->see_more_view_computer->hide();
    ui->see_more_view_person->hide();
    string current_type = ui->type_dropdown->currentText().toStdString();
    if (current_type == "Computer Scientists")
    {
        ui->search_view_person->show();
    }
    else if (current_type == "Computers")
    {
        ui->search_view_computer->show();
    }
}


void MainWindow::display_person_list(int display_type)
{
    ui->search_view_person->hide();
    ui->search_view_computer->hide();
    ui->table_view_person->show();
    ui->table_view_connections->hide();
    ui->table_view_computers->hide();
    if (display_type == 1)
    {
        person_service->get_all_persons();
    }
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
}

void MainWindow::display_computer_list(int display_type)
{
    ui->search_view_person->hide();
    ui->search_substring_computer->hide();
    ui->table_view_person->hide();
    ui->table_view_connections->hide();
    ui->table_view_computers->show();
    if (display_type == 1)
    {
        computer_service->get_all_computers();
    }
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
}

void MainWindow::display_connections_list(int display_type)
{
    ui->search_view_person->hide();
    ui->search_substring_computer->hide();
    ui->table_view_person->hide();
    ui->table_view_computers->hide();
    ui->table_view_connections->show();

    connections_service->get_all_connections();
    unsigned int vector_size = connections_service->get_person_vec().size();
    ui->table_view_connections->setRowCount(vector_size);
    for (unsigned int row = 0; row < vector_size; row++)
    {
        Person* current_person = connections_service->get_person_vec()[row];
        QString name_person = QString::fromStdString(current_person->get_name());
        Computer* current_computer = connections_service->get_computer_vec()[row];
        QString name_computer = QString::fromStdString(current_computer->get_name());

        ui->table_view_connections->setItem(row, 0, new QTableWidgetItem(name_person));
        ui->table_view_connections->setItem(row, 1, new QTableWidgetItem(name_computer));
    }

}


void MainWindow::on_type_dropdown_currentIndexChanged(const QString &arg1)
{
    ui->search_view_person->hide();
    ui->search_substring_computer->hide();
    ui->see_more_view_computer->hide();
    ui->see_more_view_person->hide();
    string current_type = ui->type_dropdown->currentText().toStdString();
    if (current_type == "Computer Scientists")
    {
        display_person_list(1);
    }
    else if (current_type == "Computers")
    {
        display_computer_list(1);
    }
    else
    {
        display_connections_list(1);
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
    ui->search_view_person->hide();
    ui->search_view_computer->hide();
    string current_type = ui->type_dropdown->currentText().toStdString();
    string currently_chosen_entry;
    if (current_type == "Computer Scientists")
    {
        ui->see_more_view_computer->hide();
        ui->description_output_person->clear();
        currently_chosen_entry = ui->table_view_person->currentItem()->text().toStdString();
        Person* current_person = find_chosen_person(currently_chosen_entry);
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
        currently_chosen_entry = ui->table_view_computers->currentItem()->text().toStdString();
        Computer* current_computer = find_chosen_computer(currently_chosen_entry);
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
    string currently_chosen_entry;
    if (current_type == "Computer Scientists")
    {
        ui->see_more_view_computer->hide();
        ui->description_output_person->clear();
        currently_chosen_entry = ui->table_view_person->currentItem()->text().toStdString();
        Person* current_person = find_chosen_person(currently_chosen_entry);
        int current_id = current_person->get_id();
        person_service->remove_person(current_id);
        display_person_list(1);
    }
    else if (current_type == "Computers")
    {
        ui->see_more_view_person->hide();
        ui->description_output_computer->clear();
        currently_chosen_entry = ui->table_view_computers->currentItem()->text().toStdString();
        Computer* current_computer = find_chosen_computer(currently_chosen_entry);
        int current_id = current_computer->get_id();
        computer_service->remove_computer(current_id);

        display_computer_list(1);
    }
    else
    {
        person_service->get_all_persons();
        computer_service->get_all_computers();
        // Get the number of the selected row
        int row = ui->table_view_connections->currentIndex().row();
        // Get the name of the person in the connection
        currently_chosen_entry = ui->table_view_connections->item(row, 0)->text().toStdString();
        // Find the corresponding person
        Person* current_person = find_chosen_person(currently_chosen_entry);
        // Get the id of this person
        int person_id = current_person->get_id();
        // Get the name of the computer in the connection
        string currently_chosen_entry_comp = ui->table_view_connections->item(row, 1)->text().toStdString();
        // Find the corresponding computer
        Computer* current_computer = find_chosen_computer(currently_chosen_entry_comp);
        // Get the id of the computer
        int computer_id = current_computer->get_id();
        connections_service->remove_connection(person_id, computer_id);
        display_connections_list(1);
    }
}

void MainWindow::on_add_pushButton_clicked()
{
    string current_type = ui->type_dropdown->currentText().toStdString();

    if (current_type == "Computer Scientists")
    {
        add_persons newadd_persons;

        int addPersonsReturnValue = newadd_persons.exec();
    }
    else if (current_type == "Computers")
    {
        add_computers newadd_computers;

        int addComputersReturnValue = newadd_computers.exec();
    }
    else if (current_type == "Connections")
    {
        add_connections newadd_connections;

        int addConnectionsReturnValue = newadd_connections.exec();
    }
}

Person* MainWindow::find_chosen_person(string chosen_name)
{
    for (unsigned int i = 0; i < person_service->get_person_vec().size(); i++)
    {
        if (person_service->get_person_vec()[i]->get_name() == chosen_name)
        {
            return person_service->get_person_vec()[i];
        }
    }
    return NULL;
}

Computer *MainWindow::find_chosen_computer(string chosen_name)
{
    for (unsigned int i = 0; i < computer_service->get_computer_vec().size(); i++)
    {
        if (computer_service->get_computer_vec()[i]->get_name() == chosen_name)
        {
            return computer_service->get_computer_vec()[i];
        }
    }
    return NULL;
}

void MainWindow::remove_chosen_connection()
{

}

void MainWindow::on_substring_input_person_returnPressed()
{
    ui->search_view_person->hide();
    string search_column = ui->search_dropdown_person->currentText().toStdString();
    string search_substring = ui->substring_input_person->text().toStdString();
    person_service->search_person(search_column, search_substring);
    display_person_list(2);
}

void MainWindow::on_substring_input_computer_returnPressed()
{
    ui->search_view_computer->hide();
    string search_column = ui->search_dropdown_computer->currentText().toStdString();
    string search_substring = ui->substring_input_computer->text().toStdString();
    computer_service->search_computer(search_column, search_substring);
    display_computer_list(2);
}
