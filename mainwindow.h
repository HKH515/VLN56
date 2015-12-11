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

    void on_substring_input_returnPressed();

    void on_table_view_clicked(const QModelIndex &index);

    void on_remove_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    PersonsService* person_service;
    ComputerService* computer_service;
    ConnectionsService* connections_service;

    void display_person_list();

    vector<Person*> curr_disp_scientists;
    vector<Computer*> curr_disp_computers;

};

#endif // MAINWINDOW_H
