#ifndef EOPENGLWIDGET_H
#define EOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "mainwindow.h"

class EOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions {
  Q_OBJECT

  public:
  EOpenGLWidget(QWidget* parent = nullptr);
  ~EOpenGLWidget();
  geometry_info object = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  bool vertices_draw_mode = 1;
  bool edges_draw_mode = 1;

  private:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
};

#endif  // EOPENGLWIDGET_H
