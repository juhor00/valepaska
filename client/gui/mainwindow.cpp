#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cards->addWidget(new OpenedCard(3, 'S'));
    ui->cards->addWidget(new QLabel(tr("testi")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

