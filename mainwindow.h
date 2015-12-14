#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include "personsservice.h"
#include "computerservice.h"
#include "connectionsservice.h"

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

    void on_search_pushButton_clicked();

    void display_person_list(int display_type);
    void display_computer_list(int display_type);
    void display_connections_list(int display_type);

    void on_type_dropdown_currentIndexChanged(const QString &arg1);
	
	 void on_add_pushButton_clicked();

    void on_table_view_person_clicked(const QModelIndex &index);

    void on_show_more_pushButton_clicked();

    void on_table_view_computers_clicked(const QModelIndex &index);

    void on_table_view_connections_clicked(const QModelIndex &index);

    void on_remove_pushButton_clicked();

    void on_substring_input_person_returnPressed();

    void on_substring_input_computer_returnPressed();

private:
    Ui::MainWindow *ui;
    PersonsService* person_service;
    ComputerService* computer_service;
    ConnectionsService* connections_service;
    vector<Person*> person_vector;
    vector<Computer*> computer_vector;
    Person* find_chosen_person(string chosen_name);
    Computer* find_chosen_computer(string chosen_name);
};

#endif // MAINWINDOW_H
