#ifndef ADD_CONNECTIONS_H
#define ADD_CONNECTIONS_H

#include <QDialog>

namespace Ui {
class add_connections;
}

class add_connections : public QDialog
{
    Q_OBJECT

public:
    explicit add_connections(QWidget *parent = 0);
    ~add_connections();

private:
    Ui::add_connections *ui;
};

#endif // ADD_CONNECTIONS_H
