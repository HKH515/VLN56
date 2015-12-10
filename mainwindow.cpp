#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Dropdown menu for types of information */
    ui->type_dropdown->addItem("Computer Scientist");
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



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    ui->remove_pushButton->setEnabled(true);
    ui->show_more_pushButton->setEnabled(true);
}
