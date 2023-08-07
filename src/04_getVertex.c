#include "../obj_viewer.h"

/// @brief
/// @param line
/// @param pobject
/// @return
int getVertex(char* line, geometry_info* pobject, int v_index) {
  line++;
  double x, y, z;
  if (sscanf(line, "%lf %lf %lf", &x, &y, &z) != 3) return INCORRECT_FILE;

  pobject->array_vertex_x[v_index] = x;
  pobject->array_vertex_y[v_index] = y;
  pobject->array_vertex_z[v_index] = z;

  return OK;
}
