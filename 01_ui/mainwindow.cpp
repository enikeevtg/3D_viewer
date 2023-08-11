#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->toolBar->setMovable(false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionOpen_Model_triggered() {
  filename = QFileDialog::getOpenFileName(this, "Open File", filename, "*.obj");
  QByteArray ba_filename = filename.toLatin1();
  structClean(&object);
  int error = getGeometryInfo(ba_filename.data(), &object);

  //  if (!error) {
  //    double x = object.vertices[0].x;
  //    double y = object.vertices[0].y;
  //    double z = object.vertices[0].z;
  //    ui->textEdit->setText("vertex #0\n\tx = " + QString::number(x) + "\n\ty
  //    = " + QString::number(y) + "\n\tz = " + QString::number(z) + "\n");
  //  }

  if (!error) {
    QString text = "";
    for (int i = 0; i < object.vertices_count; i++) {
      double x = object.vertices[i].x;
      double y = object.vertices[i].y;
      double z = object.vertices[i].z;
      text = text + "vertex #" + QString::number(i) +
             "\n\tx = " + QString::number(x) + "\n\ty = " + QString::number(y) +
             "\n\tz = " + QString::number(z) + "\n";
    }
    ui->textEdit->setText(text);
  }
}
