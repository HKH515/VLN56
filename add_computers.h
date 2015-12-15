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
    void on_cancel_pushbutton_clicked();


    void on_add_pushbutton_clicked();

    void on_name_input_editingFinished();

    void on_construction_year_input_editingFinished();

private:
    Ui::add_computers* ui;
    ComputerService* computer_service;
    Verification* verify_input;

    void display_error_msg(string error_msg);
};

#endif // ADD_COMPUTERS_H
