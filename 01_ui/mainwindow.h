#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QTextEdit>

extern "C" {
#include "../02_model_loading/model_loading.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_actionOpen_Model_triggered();

 private:
  Ui::MainWindow *ui;
  QString filename = QDir::homePath();
  geometry_info object = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  void fileAttributesFilling(QString file, QTextEdit *output);
};
#endif  // MAINWINDOW_H
