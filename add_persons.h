#ifndef ADD_PERSONS_H
#define ADD_PERSONS_H

#include <QDialog>
#include <string>
#include <vector>

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

    vector<string> on_pushbutton_add_clicked();

private:
    Ui::add_persons *ui;
};

#endif // ADD_PERSONS_H
