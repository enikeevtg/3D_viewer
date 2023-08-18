#include "affine_transformations.h"

/// @brief 
/// @param pobject 
/// @param delta 
void translationAllDirections(geometry_info* pobject, vertex_t* delta) {
  double dx = delta->x;
  double dy = delta->y;
  double dz = delta->z;
  int vertices_count = pobject->vertices_count;
  for (int i = 0; i < vertices_count; i++) {
    pobject->vertices[i].x += dx;
    pobject->vertices[i].y += dy;
    pobject->vertices[i].z += dz;
  }
}

/// @brief 
/// @param pobject 
/// @param dx delta x value
void translationXDirection(geometry_info* pobject, double dx) {
  int vertices_count = pobject->vertices_count;
  for (int i = 0; i < vertices_count; i++) {
    pobject->vertices[i].x += dx;
  }
}

void translationYDirection(geometry_info* pobject, double dy) {
  int vertices_count = pobject->vertices_count;
  for (int i = 0; i < vertices_count; i++) {
    pobject->vertices[i].y += dy;
  }
}

void translationZDirection(geometry_info* pobject, double dz) {
  int vertices_count = pobject->vertices_count;
  for (int i = 0; i < vertices_count; i++) {
    pobject->vertices[i].z += dz;
  }
}

void scaleModel(geometry_info* pobject, double scale) {
  int vertices_count = pobject->vertices_count;
  for (int i = 0; i < vertices_count; i++) {
    pobject->vertices[i].x *= scale;
    pobject->vertices[i].y *= scale;
    pobject->vertices[i].z *= scale;
  }
}
