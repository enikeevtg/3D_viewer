#ifndef EOPENGLWIDGET_H
#define EOPENGLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "mainwindow.h"

class EOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions {
  Q_OBJECT

 public:
  EOpenGLWidget(QWidget* parent = nullptr);
  ~EOpenGLWidget();
  geometry_info object;

  bool vertices_draw_mode;
  int edges_draw_mode;

 private:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
};

#endif  // EOPENGLWIDGET_H
