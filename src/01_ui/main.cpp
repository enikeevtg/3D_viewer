#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  setlocale(LC_NUMERIC, "C");
  MainWindow _3DViewer;
  _3DViewer.show();
  return app.exec();
}
