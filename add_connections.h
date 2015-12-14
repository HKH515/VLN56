#ifndef ADD_CONNECTIONS_H
#define ADD_CONNECTIONS_H

#include <QDialog>
#include <string>
#include <vector>
#include "connectionsservice.h"

using namespace std;

namespace Ui {
class add_connections;
}

class add_connections : public QDialog
{
    Q_OBJECT

public:
    explicit add_connections(QWidget *parent = 0);
    ~add_connections();

private slots:
    void on_pushbutton_add_clicked();
    void on_pushButton_cancel_clicked();

private:
    Ui::add_connections *ui;
    ConnectionsService* connections_service;
};

#endif // ADD_CONNECTIONS_H
