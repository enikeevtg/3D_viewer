#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow viewer;
  viewer.show();
  return app.exec();
}
