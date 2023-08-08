#include "../obj_viewer.h"

/// @brief
/// @param line
/// @param pobject
/// @return
int getVertex(char* line, geometry_info* pobject, int v_index) {
  double x, y, z;
  if (sscanf(line, "v %lf %lf %lf", &x, &y, &z) != 3) return INCORRECT_FILE;

  pobject->vertices[v_index].x = x;
  pobject->vertices[v_index].y = y;
  pobject->vertices[v_index].z = z;

  return OK;
}
