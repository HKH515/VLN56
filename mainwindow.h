#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "domain.h"
#include <string>
#include <vector>

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

    void on_listWidget_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Domain d;

    void display_list();

};

#endif // MAINWINDOW_H
