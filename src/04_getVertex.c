#include "../obj_viewer.h"

/// @brief
/// @param line
/// @param pobject
/// @return
int getVertex(char* line, geometry_info* pobject, int i) {
  double x, y, z;
  if (sscanf(line, "v %lf %lf %lf", &x, &y, &z) != 3) return INCORRECT_FILE;

  pobject->vertices[i].x = x;
  pobject->vertices[i].y = y;
  pobject->vertices[i].z = z;

  return OK;
}
