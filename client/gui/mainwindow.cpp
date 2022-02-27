#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    hand_(new Hand)
{
    ui->setupUi(this);
    ui->bottom->insertLayout(2, hand_);

    hand_->addWidget(new OpenedCard(3, 'S'));
    hand_->addWidget(new OpenedCard(3, 'S'));
    hand_->addWidget(new OpenedCard(3, 'S'));
    hand_->addWidget(new OpenedCard(3, 'S'));
    hand_->addWidget(new OpenedCard(3, 'S'));
    hand_->addWidget(new OpenedCard(3, 'S'));



}

MainWindow::~MainWindow()
{
    delete ui;
}

