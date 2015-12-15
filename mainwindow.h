#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include "personsService.h"
#include "computerservice.h"
#include "connectionsService.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // Changing the 'big' dropdown at the top of the screen (Computer Scientist - Computer - Connection)
    void on_type_dropdown_currentIndexChanged(const QString &arg1);
    // Selecting a row from table of persons
    void on_table_view_person_clicked(const QModelIndex &index);
    // Selecting a row from table of computers
    void on_table_view_computers_clicked(const QModelIndex &index);
    // Selecting a row from table of connections
    void on_table_view_connections_clicked(const QModelIndex &index);
    // Pushing show more button
    void on_show_more_pushButton_clicked();
    // Pushing remove button
    void on_remove_pushButton_clicked();
    // Pushing add button
    void on_add_pushButton_clicked();
    // Pushing search button
    void on_search_pushButton_clicked();
    // Changing if looking at scientist/computers in search menu for connections
    void on_search_dropdown_connections_currentIndexChanged(const QString &arg1);
    void on_dropdown_list_all_ids_person_currentIndexChanged(const QString &arg1);
    void on_dropdown_list_all_ids_computer_currentIndexChanged(const QString &arg1);

    void on_substring_input_person_textEdited(const QString &arg1);

    void on_substring_input_computer_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
    PersonsService* person_service;
    ComputerService* computer_service;
    ConnectionsService* connections_service;

    // Displays list of scientists
    void display_person_list(int display_type);
    // Displays list of computers
    void display_computer_list(int display_type);
    // Displays list of connections
    void display_connections_list(int display_type);
    // Inserts name of all persons in database to a dropdown
    void insert_all_person_ids();
    // Inserts name of all computers in database to a dropdown
    void insert_all_computer_ids();

    void display_connections_search_list(int kind, string name);
};

#endif // MAINWINDOW_H
