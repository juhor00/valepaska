#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->handLayout->addWidget(new OpenedCard(3, 'S'));
    ui->handLayout->addWidget(new QLabel(tr("testi")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

