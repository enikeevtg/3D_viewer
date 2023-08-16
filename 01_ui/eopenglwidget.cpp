#include "eopenglwidget.h"

#ifdef Q_OS_MAC
    #include <glu.h>
#elif linux
    #include <GL/glu.h>
#endif

EOpenGLWidget::EOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

EOpenGLWidget::~EOpenGLWidget() { structClean(&object); }

void EOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void EOpenGLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  qreal aspectratio = qreal(width) / qreal(height);
  gluPerspective(90.0, aspectratio, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void EOpenGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glPointSize(5);
  glTranslatef(0, 0, -20);
  glRotatef(0, 0.f, 1.f, 0.f);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_DOUBLE, GL_TRUE, 0, object.vertices);

  if (vertices_draw_mode) {
    glDrawArrays(GL_POINTS, 0, object.vertices_count);
  }
  if (edges_draw_mode == true) {
    for (int i = 0; i < object.facets_count; i++) {
        glDrawElements(GL_LINE_LOOP, object.facets[i].facet_vertices_count, GL_UNSIGNED_INT, object.facets[i].vertex_IDs);
    }
  }
}

