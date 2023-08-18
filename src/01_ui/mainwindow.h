#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>

extern "C" {
#include "../02_model_loading/model_loading.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum view_settings {
  INVISIBLE = 0,
  VISIBLE,
  DASHED_EDGES,
  SOLID_EDGES,
  CIRCLE_VERTICES,
  SQUARE_VERTICES
};

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_actionOpenModel_triggered();
  void fileInfoFilling(geometry_info* pobject, QFileInfo file_info);
  int edgesCounting(geometry_info* pobject);

  void showTab();

  void visabilitySetting(int check);
  void typeSelect();
  void sizeSetting(int size);
  void getColor();

  void on_doubleSpinBox_Tx_valueChanged(double arg1);

  void on_radioButton_solid_edges_clicked();

 private:
  Ui::MainWindow* ui;
  QString file = QDir::homePath();
  geometry_info object = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  double last_tx = 0;
};
#endif  // MAINWINDOW_H
