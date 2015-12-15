#ifndef ADD_COMPUTERS_H
#define ADD_COMPUTERS_H

#include <QDialog>
#include <vector>
#include <string>
#include "computerservice.h"
#include "verification.h"

namespace Ui {
class add_computers;
}

class add_computers : public QDialog
{
    Q_OBJECT

public:
    explicit add_computers(QWidget *parent = 0);
    ~add_computers();

private slots:
     // Leave the window
    void on_cancel_pushbutton_clicked();
    // Add information from the user input to the database
    void on_add_pushbutton_clicked();
    // Gets the name from the user input and validates it
    void on_name_input_editingFinished();
    // Gets the construction year from the user input and validates it
    void on_construction_year_input_editingFinished();

private:
    Ui::add_computers* ui;
    ComputerService* computer_service;
    Verification* verify_input;

    // Private helper function:

    // Displays error msg if the user input is invalid
    void display_error_msg(string error_msg);
    // When all necessary information have been entered the add button is enabled
    void enable_add_button();
};

#endif // ADD_COMPUTERS_H
