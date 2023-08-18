#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>

extern "C" {
#include "../02_model_loading/model_loading.h"
#include "../03_affine_transformations/affine_transformations.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum view_settings {
  PARALLEL_PROJECTION,
  CENTRAL_PROJECTION,
  VISIBLE,
  DASHED_EDGES,
  SOLID_EDGES,
  CIRCLE_VERTICES,
  SQUARE_VERTICES,

};

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_actionOpenModel_triggered();
  void fileInfoFilling(QFileInfo file_info);
  int edgesCounting();
  void objectNormalization();

  void showTab();

  void visabilitySetting(int check);
  void typeSelect();
  void componentsSizesSettings(int size);
  void getColor();

  void on_doubleSpinBox_Tx_valueChanged(double arg1);

  void on_doubleSpinBox_scale_valueChanged(double scale);

private:
  Ui::MainWindow* ui;
  QString file = QDir::homePath();
  geometry_info object = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  double last_tx = 0;
};
#endif  // MAINWINDOW_H
