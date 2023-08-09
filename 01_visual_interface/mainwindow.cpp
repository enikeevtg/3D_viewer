#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->toolBar->setMovable(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_Model_triggered()
{
    QString filename = QFileDialog::getOpenFileName(nullptr, "Open", "", "*.obj");
}

