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

    void display_person_list();
    void display_computer_list();
    void display_connections_list();

    void on_type_dropdown_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    PersonsService* person_service;
    ComputerService* computer_service;
    ConnectionsService* connections_service;

};

#endif // MAINWINDOW_H
