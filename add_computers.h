#ifndef ADD_COMPUTERS_H
#define ADD_COMPUTERS_H

#include <QDialog>

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

private:
    Ui::add_computers *ui;
};

#endif // ADD_COMPUTERS_H
