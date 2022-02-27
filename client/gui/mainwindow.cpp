#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    hand_(new Hand),
    deck_(new CardStack)
{
    ui->setupUi(this);

    ui->bottom->insertLayout(1, hand_);
    ui->middle->insertLayout(0, deck_);


    hand_->addWidget(new OpenedCard(3, 'S'));
    hand_->addWidget(new OpenedCard(3, 'S'));
    hand_->addWidget(new OpenedCard(3, 'S'));
    hand_->addWidget(new OpenedCard(3, 'S'));
    hand_->addWidget(new OpenedCard(3, 'S'));
    hand_->addWidget(new OpenedCard(3, 'S'));


    deck_->addWidget(new ClosedCard);
    deck_->addWidget(new ClosedCard);
    deck_->addWidget(new ClosedCard);
    deck_->addWidget(new ClosedCard);
    deck_->addWidget(new ClosedCard);
    deck_->addWidget(new ClosedCard);



}

MainWindow::~MainWindow()
{
    delete ui;
}

