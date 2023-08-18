#include "eopenglwidget.h"

#ifdef Q_OS_MAC
#include <glu.h>
#elif linux
#include <GL/glu.h>
#endif

EOpenGLWidget::EOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {
  object = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  aspect_ratio = 1;

  projection_type = PARALLEL_PROJECTION;

  vertices_visibility = VISIBLE;
  vertices_type = CIRCLE_VERTICES;
  vertices_size = 1;
  vertices_color = Qt::white;

  edges_visibility = VISIBLE;
  edges_type = SOLID_EDGES;
  edges_thickness = 1;
  edges_color = Qt::white;

  background_color = Qt::black;
}

EOpenGLWidget::~EOpenGLWidget() { structClean(&object); }

void EOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void EOpenGLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
  w_width = width;
  w_height = height;
  aspect_ratio = qreal(width) / qreal(height);
}

void EOpenGLWidget::paintGL() {
  setDisplay();

  if (vertices_visibility == VISIBLE) {
    setVerticesDisplay();
    glDrawArrays(GL_POINTS, 0, object.vertices_count);
  }

  if (edges_visibility == VISIBLE) {
    setEdgesDisplay();
    for (int i = 0; i < object.facets_count; i++) {
      glDrawElements(GL_LINE_LOOP, object.facets[i].facet_vertices_count,
                     GL_UNSIGNED_INT, object.facets[i].vertex_IDs);
    }
  }
}

void EOpenGLWidget::setDisplay() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (projection_type == PARALLEL_PROJECTION) {
    glOrtho(-aspect_ratio, aspect_ratio, -1, 1, 1, -1);
  } else if (projection_type == CENTRAL_PROJECTION) {
//      gluPerspective(90.0, aspect_ratio, 1, -1);
    glFrustum(-aspect_ratio, aspect_ratio, -1, 1, 1, -1);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(background_color.redF(), background_color.greenF(),
               background_color.blueF(), background_color.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_DOUBLE, GL_TRUE, 0, object.vertices);
}

void EOpenGLWidget::setVerticesDisplay() {
  if (vertices_type == SQUARE_VERTICES) {
    glDisable(GL_POINT_SMOOTH);
  } else if (vertices_type == CIRCLE_VERTICES) {
    glEnable(GL_POINT_SMOOTH);
  }

  glPointSize(vertices_size);

  glColor4d(vertices_color.redF(), vertices_color.greenF(),
            vertices_color.blueF(), vertices_color.alphaF());
}

void EOpenGLWidget::setEdgesDisplay() {
  glEnable(GL_LINE_STIPPLE);
  if (edges_type == DASHED_EDGES) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(5, 0x00FF);
  } else if (edges_type == SOLID_EDGES) {
    glDisable(GL_LINE_STIPPLE);
  }

  glLineWidth(edges_thickness);

  glColor4d(edges_color.redF(), edges_color.greenF(), edges_color.blueF(),
            edges_color.alphaF());
}
