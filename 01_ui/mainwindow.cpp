#include "mainwindow.h"

#include "eopenglwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->toolBar->setMovable(false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionOpen_Model_triggered() {
  file = QFileDialog::getOpenFileName(this, "Open File", file, "*.obj");
  QFileInfo file_info(file);
  if (file_info.isFile() == true) {
    structClean(&object);
    int error =
        getGeometryInfo(file_info.filePath().toLatin1().data(), &object);
    if (!error) {
      ui->file_info->setText("");
      fileInfoFilling(&object, file_info);
      ui->openGLWidget->object = object;
    }
  }
}

void MainWindow::fileInfoFilling(geometry_info* pobject, QFileInfo file_info) {
  QString filename = file_info.fileName();
  QString filepath = file_info.absolutePath();
  QString filesize = QString::number(file_info.size() / 1000.0);
  QString v_count = QString::number(pobject->vertices_count);
  QString f_count = QString::number(pobject->facets_count);
  QString e_count = QString::number(edgesCounting(pobject));

  ui->file_info->setText(
      "filename: " + filename + "\n" + "filepath: " + filepath + "/\n\n" +
      "filesize: " + filesize + " kb\n\n" + "vertices count: " + v_count +
      "\n" + "edges count: " + e_count + "\n" + "facets count: " + f_count);
}

int MainWindow::edgesCounting(geometry_info* pobject) {
  int edges_count = 0;
  for (int i = 0; i < pobject->facets_count; i++) {
    edges_count += pobject->facets->facet_vertices_count;
  }
  return edges_count;
}
