#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_computers.h"
#include "add_persons.h"
#include "add_connections.h"
#include <QTableView>
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
    // Hide all things that are not supposed to be on the front page
    ui->see_more_view_person->hide();
    ui->see_more_view_computer->hide();
    ui->search_view_person->hide();
    ui->search_view_computer->hide();
    ui->search_view_connections->hide();
    ui->table_view_connections->hide();
    ui->table_view_computers->hide();
    // Default display list of persons in the database, ordered after name in ascending order
    display_person_list(1);

    // When selecting something in some column, all row will get selected
    ui->table_view_person->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_view_computers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_view_connections->setSelectionBehavior(QAbstractItemView::SelectRows);

    // only allowed to read
    ui->profession_output->setReadOnly(true);
    ui->description_output_person->setReadOnly(true);
    ui->description_output_computer->setReadOnly(true);

    ui->table_view_person->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete person_service;
    delete computer_service;
    delete connections_service;
}

// When the 'big' Combobox at the top changes (Computer Scientist - Computer - Connections)
void MainWindow::on_type_dropdown_currentIndexChanged(const QString &arg1)
{
    ui->search_dropdown_connections->hide();
    ui->search_view_person->hide();
    ui->search_view_connections->hide();
    ui->search_view_computer->hide();
    ui->see_more_view_computer->hide();
    ui->see_more_view_person->hide();

    // Get the chosen value from the dropdown
    string current_type = ui->type_dropdown->currentText().toStdString();

    if (current_type == "Computer Scientists")
    {
        display_person_list(1);
    }
    else if (current_type == "Computers")
    {
        display_computer_list(1);
        //ui->search_dropdown_connections->hide();
        //ui->dropdown_list_all_ids_computer->hide();
    }
    else
    {
        display_connections_list(1);
    }

    ui->remove_pushButton->setEnabled(false);
    ui->show_more_pushButton->setEnabled(false);
}

// Remove and Show more buttons are only enabled when selecting something from the table
void MainWindow::on_table_view_person_clicked(const QModelIndex &index)
{
    ui->remove_pushButton->setEnabled(true);
    ui->show_more_pushButton->setEnabled(true);
}

// Remove and Show more buttons are only enabled when selecting something from the table
void MainWindow::on_table_view_computers_clicked(const QModelIndex &index)
{
    ui->remove_pushButton->setEnabled(true);
    ui->show_more_pushButton->setEnabled(true);
}

// Remove only enabled when something is selected from the list
void MainWindow::on_table_view_connections_clicked(const QModelIndex &index)
{
    ui->remove_pushButton->setEnabled(true);
}

void MainWindow::on_show_more_pushButton_clicked()
{
    ui->search_view_person->hide();
    ui->search_view_computer->hide();
    ui->search_view_connections->hide();
    // Get the value from the dropdown
    string current_type = ui->type_dropdown->currentText().toStdString();
    int currently_chosen_entry;
    if (current_type == "Computer Scientists")
    {
        ui->see_more_view_computer->hide();
        ui->description_output_person->clear();
        // Get the selected row number
        int row = ui->table_view_person->currentIndex().row();
        // Get the id of the person in the row
        currently_chosen_entry = ui->table_view_person->item(row, 0)->text().toInt();
        // Find the corresponding person
        Person* current_person = person_service->find_chosen_person(currently_chosen_entry);
        QString current_profession = QString::fromStdString(current_person->get_profession());
        QString current_description = QString::fromStdString(current_person->get_description());
        // Displaying the persons profession and description
        ui->profession_output->setText(current_profession);
        ui->description_output_person->append(current_description);
        ui->see_more_view_person->show();

    }
    else if (current_type == "Computers")
    {
        ui->see_more_view_person->hide();
        ui->description_output_computer->clear();
        int row = ui->table_view_computers->currentIndex().row();
        int currently_chosen_entry_comp = ui->table_view_computers->item(row, 0)->text().toInt();
        // Find the corresponding computer
        Computer* current_computer = computer_service->find_chosen_computer(currently_chosen_entry_comp);
        QString current_description = QString::fromStdString(current_computer->get_description());
        ui->description_output_computer->append(current_description);
        ui->see_more_view_computer->show();
    }
}

void MainWindow::on_remove_pushButton_clicked()
{
    // Get the type from the dropdown
    string current_type = ui->type_dropdown->currentText().toStdString();
    int selected_id, selected_id_comp, row;
    if (current_type == "Computer Scientists")
    {
        ui->see_more_view_computer->hide();
        ui->description_output_person->clear();
        // Get the selected row number
        row = ui->table_view_person->currentIndex().row();
        // Get the id of the person that is in the row selected
        selected_id = ui->table_view_person->item(row, 0)->text().toInt();
        // Remove this person
        person_service->remove_person(selected_id);
        // Displaying list again after removing
        display_person_list(1);
    }
    else if (current_type == "Computers")
    {
        ui->see_more_view_person->hide();
        ui->description_output_computer->clear();
        row = ui->table_view_computers->currentIndex().row();
        selected_id_comp = ui->table_view_computers->item(row, 0)->text().toInt();
        computer_service->remove_computer(selected_id_comp);
        display_computer_list(1);
    }
    else
    {
        person_service->get_all_persons();
        computer_service->get_all_computers();
        // Get the number of the selected row
        row = ui->table_view_connections->currentIndex().row();
        // Get the id of the person in the connection
        selected_id = ui->table_view_connections->item(row, 0)->text().toInt();
        // Get the id of the computer in the connection
        selected_id_comp = ui->table_view_connections->item(row, 2)->text().toInt();
        connections_service->remove_connection(selected_id, selected_id_comp);
        display_connections_list(1);
    }
}

void MainWindow::on_add_pushButton_clicked()
{
    // Get the type from the dropdown
    string current_type = ui->type_dropdown->currentText().toStdString();

    if (current_type == "Computer Scientists")
    {
        // Display add person window
        add_persons newadd_persons;
        int addPersonsReturnValue = newadd_persons.exec();
        display_person_list(1);
    }
    else if (current_type == "Computers")
    {
        // Display add computer window
        add_computers newadd_computers;
        int addComputersReturnValue = newadd_computers.exec();
        display_computer_list(1);
    }
    else if (current_type == "Connections")
    {
        // Display add connections window
        add_connections newadd_connections;
        int addConnectionsReturnValue = newadd_connections.exec();
        display_connections_list(1);
    }
}

void MainWindow::on_search_pushButton_clicked()
{
    // If see more view was on, hide it
    ui->see_more_view_computer->hide();
    ui->see_more_view_person->hide();

    // Get the type that was selected when pushed on search
    string current_type = ui->type_dropdown->currentText().toStdString();

    if (current_type == "Computer Scientists")
    {
        ui->search_view_person->show();
    }
    else if (current_type == "Computers")
    {
        ui->search_view_computer->show();
    }
    // Shows all computers connected to a certain scientist or all scientists connected to a certain computer
    else
    {
        ui->search_view_connections->show();
        // Default list all Computer Scientist
        ui->search_dropdown_connections->show();
        ui->dropdown_list_all_ids_computer->hide();
        ui->dropdown_list_all_ids_person->show();
        // Fill in the dropdown
        insert_all_person_ids();
        display_computer_list(3);
    }
}

void MainWindow::on_search_dropdown_connections_currentIndexChanged(const QString &arg1)
{
    if (arg1.toStdString() == "Computer Scientist")
    {
        ui->dropdown_list_all_ids_computer->hide();
        ui->dropdown_list_all_ids_person->show();
        insert_all_person_ids();
    }
    else
    {
        ui->dropdown_list_all_ids_computer->show();
        ui->dropdown_list_all_ids_person->hide();
        insert_all_computer_ids();
    }
}

void MainWindow::on_dropdown_list_all_ids_person_currentIndexChanged(const QString &arg1)
{
    connections_service->get_connected("Computer Scientist", arg1.toStdString());
    display_computer_list(3);
    ui->search_dropdown_connections->show();
}


void MainWindow::on_dropdown_list_all_ids_computer_currentIndexChanged(const QString &arg1)
{
    connections_service->get_connected("Computer", arg1.toStdString());
    display_person_list(3);
    ui->search_dropdown_connections->show();
}

// Private functions

void MainWindow::display_person_list(int display_type)
{
    unsigned int vector_size;
    Person *current_person;
    //ui->search_view_person->hide();
    ui->search_view_computer->hide();
    ui->table_view_person->show();
    ui->table_view_connections->hide();
    ui->table_view_computers->hide();

    // Don't display the id column - only used to find the right person
    ui->table_view_person->setColumnHidden(0, true);

    // Adjust column widths in table
    ui->table_view_person->setColumnWidth(1, this->width()/3);
    ui->table_view_person->setColumnWidth(2, this->width()/5);
    ui->table_view_person->setColumnWidth(3, this->width()/5);
    ui->table_view_person->setColumnWidth(4, this->width()/6);

    // Dispaying all persons
    if (display_type == 1)
    {
        person_service->get_all_persons();
        vector_size = person_service->get_person_vec().size();
    }
    // Displaying search results
    else if (display_type == 2)
    {
        vector_size = person_service->get_person_vec().size();
    }
    // Displaying search for connections
    else
    {
        vector_size = connections_service->get_person_vec().size();
    }

    ui->table_view_person->setRowCount(vector_size);

    for (unsigned int row = 0; row < vector_size; row++)
    {
        if (display_type == 1 || display_type == 2)
        {
            current_person = person_service->get_person_vec()[row];
        }
        else
        {
            current_person = connections_service->get_person_vec()[row];
            cout << connections_service->get_person_vec()[row]->get_name() << endl;
        }

        // Get all information from the Person object and change to QStrings
        QString id = QString::number(current_person->get_id());
        QString name = QString::fromStdString(current_person->get_name());
        QString birthyear = QString::number(current_person->get_birthyear());
        int death_year = current_person->get_deathyear();
        QString deathyear;
        // If the person is a alive, display '-'
        if (death_year == 0)
        {
            deathyear = QString::fromStdString("-");
        }
        else
        {
            deathyear = QString::number(current_person->get_deathyear());
        }

        QString sex = QString::fromStdString(current_person->get_sex());

        // Fill information into the columns
        ui->table_view_person->setItem(row, 0, new QTableWidgetItem(id));
        ui->table_view_person->setItem(row, 1, new QTableWidgetItem(name));
        ui->table_view_person->setItem(row, 2, new QTableWidgetItem(birthyear));
        ui->table_view_person->setItem(row, 3, new QTableWidgetItem(deathyear));
        ui->table_view_person->setItem(row, 4, new QTableWidgetItem(sex));
    }

}

void MainWindow::display_computer_list(int display_type)
{
    unsigned int vector_size;
    Computer *current_computer;
    ui->search_view_person->hide();
    ui->table_view_person->hide();
    ui->table_view_connections->hide();
    ui->table_view_computers->show();

    // Hide id column - only used to find the right person, not displayed
    ui->table_view_computers->setColumnHidden(0, true);

    // Adjust column widths in table
    ui->table_view_computers->setColumnWidth(1, this->width()/3.5);
    ui->table_view_computers->setColumnWidth(2, this->width()/5);
    ui->table_view_computers->setColumnWidth(3, this->width()/4);
    ui->table_view_computers->setColumnWidth(4, this->width()/7);

    // If displaying list of all computers in the database
    if (display_type == 1)
    {
        computer_service->get_all_computers();
        vector_size = computer_service->get_computer_vec().size();
    }
    // If displaying results from search
    else if (display_type == 2)
    {
        vector_size = computer_service->get_computer_vec().size();
    }
    // If displaying results from search for connection
    else
    {
        vector_size = connections_service->get_computer_vec().size();
    }

    ui->table_view_computers->setRowCount(vector_size);

    for (unsigned int row = 0; row < vector_size; row++)
    {
        if (display_type == 1 || display_type == 2)
        {
            current_computer = computer_service->get_computer_vec()[row];
        }
        else
        {
            current_computer = connections_service->get_computer_vec()[row];
        }

        // Get information from the Computer object and change to QStrings
        QString id = QString::number(current_computer->get_id());
        QString name = QString::fromStdString(current_computer->get_name());
        QString construction_year = QString::number(current_computer->get_construction_year());
        QString type = QString::fromStdString(current_computer->get_type());
        int check_if_built = current_computer->get_built();
        QString built;
        if (check_if_built == 0)
        {
            built = QString::fromStdString("No");
        }
        else
        {
            built = QString::fromStdString("Yes");
        }

        // Insert into columns in the table
        ui->table_view_computers->setItem(row, 0, new QTableWidgetItem(id));
        ui->table_view_computers->setItem(row, 1, new QTableWidgetItem(name));
        ui->table_view_computers->setItem(row, 2, new QTableWidgetItem(construction_year));
        ui->table_view_computers->setItem(row, 3, new QTableWidgetItem(type));
        ui->table_view_computers->setItem(row, 4, new QTableWidgetItem(built));
    }
}

void MainWindow::display_connections_list(int display_type)
{
    ui->search_view_person->hide();
    ui->table_view_person->hide();
    ui->table_view_computers->hide();
    ui->table_view_connections->show();

    // Do not display the ids of the scientists/computers - only used to find the right one
    ui->table_view_connections->setColumnHidden(0, true);
    ui->table_view_connections->setColumnHidden(2, true);

    // Adjust column sizes
    ui->table_view_connections->setColumnWidth(1, this->width()/2);
    ui->table_view_connections->setColumnWidth(3, this->width()/2);

    connections_service->get_all_connections();
    unsigned int vector_size = connections_service->get_person_vec().size();
    ui->table_view_connections->setRowCount(vector_size);

    for (unsigned int row = 0; row < vector_size; row++)
    {
        // Get names and ids of scientists/computers in the table
        Person* current_person = connections_service->get_person_vec()[row];
        QString person_id = QString::number(current_person->get_id());
        QString name_person = QString::fromStdString(current_person->get_name());
        Computer* current_computer = connections_service->get_computer_vec()[row];
        QString computer_id = QString::number(current_computer->get_id());
        QString name_computer = QString::fromStdString(current_computer->get_name());

        // Insert into the columns
        ui->table_view_connections->setItem(row, 0, new QTableWidgetItem(person_id));
        ui->table_view_connections->setItem(row, 1, new QTableWidgetItem(name_person));
        ui->table_view_connections->setItem(row, 2, new QTableWidgetItem(computer_id));
        ui->table_view_connections->setItem(row, 3, new QTableWidgetItem(name_computer));
    }
}

void MainWindow::insert_all_person_ids()
{
    // Clear the dropdown so each person only appears once
    //ui->dropdown_list_all_ids_person->clear();
    person_service->free_vector_memory();
    person_service->get_all_persons();
    vector<Person*> person_vec = person_service->get_person_vec();

    for (unsigned int i = 0; i < person_vec.size(); i++)
    {
        ui->dropdown_list_all_ids_person->addItem(QString::fromStdString(person_vec[i]->get_name()));
    }
}

void MainWindow::insert_all_computer_ids()
{
    // Clear the dropdown so each computer only appears once
    //ui->dropdown_list_all_ids_computer->clear();
    computer_service->free_vector_memory();
    computer_service->get_all_computers();
    vector<Computer*> computer_vec = computer_service->get_computer_vec();

    for (unsigned int i = 0; i < computer_vec.size(); i++)
    {
        ui->dropdown_list_all_ids_computer->addItem(QString::fromStdString(computer_vec[i]->get_name()));
    }
}

void MainWindow::display_connections_search_list(int kind, string name)
{
    if (kind == 1)
    {
        connections_service->get_connected("Computer Scientist", name);
        unsigned int vector_size = connections_service->get_computer_vec().size();

        for (int row = 0; row < vector_size; row++)
        {
            Computer* current_computer;
            QString id = QString::number(current_computer->get_id());
            QString name = QString::fromStdString(current_computer->get_name());
            QString construction_year = QString::number(current_computer->get_construction_year());
            QString type = QString::fromStdString(current_computer->get_type());
            int check_if_built = current_computer->get_built();
            QString built;
            if (check_if_built == 0)
            {
                built = QString::fromStdString("No");
            }
            else
            {
                built = QString::fromStdString("Yes");
            }
            ui->table_view_computers->setItem(row, 0, new QTableWidgetItem(id));
            ui->table_view_computers->setItem(row, 1, new QTableWidgetItem(name));
            ui->table_view_computers->setItem(row, 2, new QTableWidgetItem(construction_year));
            ui->table_view_computers->setItem(row, 3, new QTableWidgetItem(type));
            ui->table_view_computers->setItem(row, 4, new QTableWidgetItem(built));
        }

    }
}


void MainWindow::on_substring_input_person_textEdited(const QString &arg1)
{
    string search_column = ui->search_dropdown_person->currentText().toStdString();
    string search_substring = ui->substring_input_person->text().toStdString();
    cout << "return pressed, buin að na i colum: " << search_column << " substring " << search_substring << endl;
    person_service->search_person(search_column, search_substring);
    cout << "sendi search nidur i domain layer" << endl;
    display_person_list(2);
    cout << "gat ekkert displayað" << endl;
    if (ui->substring_input_person->text().isEmpty())
    {
        ui->search_view_person->hide();
    }

}

void MainWindow::on_substring_input_computer_textEdited(const QString &arg1)
{
    string search_column = ui->search_dropdown_computer->currentText().toStdString();
    string search_substring = ui->substring_input_computer->text().toStdString();
    computer_service->search_computer(search_column, search_substring);
    display_computer_list(2);
    if (ui->substring_input_computer->text().isEmpty())
    {
        ui->search_view_computer->hide();
    }

}
