#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    display_list();

    /* Dropdown menu for types of information */
    ui->type_dropdown->addItem(QString::fromStdString("Computer Scientists"));
    ui->type_dropdown->addItem("Computer");
    ui->type_dropdown->addItem("Connections");

    /* Dropdown for sorting column for Scientist */
    ui->sort_column_dropdown->addItem("Name");
    ui->sort_column_dropdown->addItem("Birth year");
    ui->sort_column_dropdown->addItem("Death year");
    ui->sort_column_dropdown->addItem("Sex");

    /* Dropdown for sort order */
    ui->sort_order_dropdown->addItem("Ascending");
    ui->sort_order_dropdown->addItem("Descending");

    display_list();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::display_list()
{
    vector<string> command_vec;
    command_vec.push_back("list");
    string table = ui->type_dropdown->currentText().toStdString();
    string sort_column = ui->sort_column_dropdown->currentText().toStdString();
    cout << "sort column "<< sort_column << endl;
    string sort_method = ui->sort_order_dropdown->currentText().toStdString();
    command_vec.push_back(table);
    command_vec.push_back(sort_column);
    command_vec.push_back(sort_method);
    d.handle_commands(command_vec);
    cout << d.get_p_vec().size() << endl;

    for (unsigned int i = 0; i < d.get_p_vec().size(); i++)
    {
        Person* current_person = d.get_p_vec()[i];
        ui->listWidget->addItem(QString::fromStdString(current_person->get_name()));
    }
}



void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    ui->remove_pushButton->setEnabled(true);
    ui->show_more_pushButton->setEnabled(true);
}
