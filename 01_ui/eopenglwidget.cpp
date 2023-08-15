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
//  glEnable(GL_CULL_FACE);
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
  glTranslatef(0, 0, -5);
  glRotatef(30, 0.f, 1.f, 0.f);

  glBegin(GL_POINTS);
  for (int i = 0; i < object.vertices_count; i++) {
      vertex_t current_vertex = object.vertices[i];
      glVertex3d(current_vertex.x, current_vertex.y, current_vertex.z);
    }
  glEnd();

  for (int i = 0; i < object.facets_count; i++) {
      glBegin(GL_LINE_LOOP);
      for (int j = 0; j < object.facets[i].facet_vertices_count; j++) {
          int id = object.facets[i].vertex_IDs[j];
          vertex_t current_vertex = object.vertices[id];
          glVertex3d(current_vertex.x, current_vertex.y, current_vertex.z);
        }
      glEnd();
    }

//  glEnableVertexAttribArray(0);
//  glVertexPointer(3, GL_DOUBLE, 0, object.vertices);

//  glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, object.vertices);

//  glDrawArrays(GL_POINTS, 0, object.vertices_count);
//  glDrawElements(GL_LINES, 230, GL_UNSIGNED_INT, object.facets);

}

