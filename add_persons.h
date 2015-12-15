#ifndef ADD_PERSONS_H
#define ADD_PERSONS_H

#include <QDialog>
#include <string>
#include <vector>
#include "personsService.h"
#include "verification.h"
#include <QMessageBox>

using namespace std;

namespace Ui {
class add_persons;
}

class add_persons : public QDialog
{
    Q_OBJECT

public:
    explicit add_persons(QWidget *parent = 0);
    ~add_persons();

private slots:
    // Constructs a vector of strings that contains all informations about the Scientist
    // entered by the user. Sends the vector to the domain-layer
    void on_pushbutton_add_clicked();
    // Closes the add window
    void on_pushbutton_cancel_clicked();
    // Gets and validates the name entered
    void on_name_input_editingFinished();
    // Gets and validates the birth year entered
    void on_birth_year_input_editingFinished();
    // Gets and validates the death year entered
    void on_death_year_input_editingFinished();
    // Gets and validates the profession entered
    void on_profession_input_editingFinished();

private:
    Ui::add_persons *ui;
    PersonsService *person_service;
    Verification *verify_input;

    // Private helper functions:

    // Displays error msg if the user input is invalid
    void display_error_msg(string error_msg);
    // enables add button when all necessary info has been entered
    void enable_add_button();
};

#endif // ADD_PERSONS_H
