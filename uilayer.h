#ifndef UILAYER_H
#define UILAYER_H

#include <QMainWindow>

namespace Ui {
class UiLayer;
}

class UiLayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit UiLayer(QWidget *parent = 0);
    ~UiLayer();

protected:
void changeEvent(QEvent *e);

private:
    Ui::UiLayer *ui;

};

#endif // UILAYER_H
