#include "uilayer.h"
#include "ui_uilayer.h"
#include <QApplication>
#include "qbytearray.h"
#include <QString>
#include <QTextEdit>
#include <QWidget>

UiLayer::UiLayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UiLayer)
{
    ui->setupUi(this);
}

UiLayer::~UiLayer()
{
    delete ui;
}

void UiLayer::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


