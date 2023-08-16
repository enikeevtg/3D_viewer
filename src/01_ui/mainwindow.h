#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
//#include <QTextEdit>

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
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_actionOpenModel_triggered();
  void fileInfoFilling(geometry_info* pobject, QFileInfo file_info);
  int edgesCounting(geometry_info* pobject);

  void on_checkBox_vertices_stateChanged(int arg1);
  void on_checkBox__edges_stateChanged(int arg1);

  void on_actionTabInfo_triggered();
  void on_actionTabSettings_triggered();

  void on_doubleSpinBox_Tx_valueChanged(double arg1);

  void on_actionMove_Rotate_triggered();

 private:
  Ui::MainWindow* ui;
  QString file = QDir::homePath();
  geometry_info object = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  double last_tx = 0;
};
#endif  // MAINWINDOW_H
