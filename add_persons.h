#ifndef ADD_PERSONS_H
#define ADD_PERSONS_H

#include <QDialog>
#include <string>
#include <vector>
#include "personsservice.h"
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
    void on_pushbutton_add_clicked();

    void on_pushbutton_cancel_clicked();

    void on_name_input_editingFinished();

    void on_birth_year_input_editingFinished();

    void on_death_year_input_editingFinished();

    void on_profession_input_editingFinished();

private:
    Ui::add_persons *ui;
    PersonsService *person_service;
    Verification *verify_input;

    void display_error_msg(string error_msg);
};

#endif // ADD_PERSONS_H
