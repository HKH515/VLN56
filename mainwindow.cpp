#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    d = new Domain();
    ui->setupUi(this);
    ui->see_more_view->hide();
    ui->search_view->hide();

    /* Dropdown menu for types of information */
    ui->type_dropdown->addItem(QString::fromStdString("Computer Scientists"));
    ui->type_dropdown->addItem("Computer");
    ui->type_dropdown->addItem("Connections");

    display_list();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::display_list()
{
    ui->table_view->clearContents();

    ui->table_view->setRowCount(13);
    vector<string> command_vec;
    command_vec.push_back("list");
    string table = ui->type_dropdown->currentText().toStdString();

    command_vec.push_back(table);
    d->handle_commands(command_vec);
    cout << d->get_p_vec().size() << endl;
    cout << "size i list view: " << d->get_p_vec().size() << endl;

    for (unsigned int row = 0; row < 13; row++)
    {
        Person* current_person = d->get_p_vec()[row];
        QString name = QString::fromStdString(current_person->get_name());
        QString birthyear = QString::number(current_person->get_birthyear());
        QString deathyear = QString::number(current_person->get_deathyear());
        QString sex = QString::fromStdString(current_person->get_sex());
        ui->table_view->setItem(row, 0, new QTableWidgetItem(name));
        ui->table_view->setItem(row, 1, new QTableWidgetItem(birthyear));
        ui->table_view->setItem(row, 2, new QTableWidgetItem(deathyear));
    }

    curr_disp_scientists = d->get_p_vec();
}

void MainWindow::on_search_pushButton_clicked()
{
    ui->search_view->show();
}

void MainWindow::on_substring_input_returnPressed()
{
    ui->search_view->hide();
}

void MainWindow::on_table_view_clicked(const QModelIndex &index)
{
    ui->remove_pushButton->setEnabled(true);
    ui->show_more_pushButton->setEnabled(true);
}



void MainWindow::on_remove_pushButton_clicked()
{
    int curr_selected_elem = ui->table_view->currentIndex().row();
}
