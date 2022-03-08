#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    hand_(new Hand(this))
{
    ui->setupUi(this);

    ui->bottom->addWidget(hand_);


    hand_->add(new OpenedCard(3, 'S', hand_));
    hand_->add(new OpenedCard(3, 'S', hand_));
    hand_->add(new OpenedCard(3, 'S', hand_));
    hand_->add(new OpenedCard(3, 'S', hand_));
    hand_->add(new OpenedCard(3, 'S', hand_));
    hand_->add(new OpenedCard(3, 'S', hand_));

    hand_->show();



}

MainWindow::~MainWindow()
{
    delete ui;
}

