#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widgets/openedcard.h"
#include "widgets/closedcard.h"
#include "hand.h"
#include "cardstack.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

//OpenedCard* card_;
    Ui::MainWindow *ui;
    Hand* hand_;
    CardStack* deck_;
    CardStack* cardStack_;

};
#endif // MAINWINDOW_H
