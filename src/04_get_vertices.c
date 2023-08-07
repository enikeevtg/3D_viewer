#include "../obj_viewer.h"

/// @brief 
/// @param line 
/// @param pobject 
/// @return 
int get_vertices(char* line, geometry_info* pobject, int index) {
  int error = OK;
  line += 3;
  error = get_vertex_coordinate(&line, pobject->array_vertex_x, index);
  if (!error)
    error = get_vertex_coordinate(&line, pobject->array_vertex_y, index);
  if (!error)
    error = get_vertex_coordinate(&line, pobject->array_vertex_z, index);
  return error;
}

int get_vertex_coordinate(char** line, double* coord, int index) {
  if (sscanf(*line, "%lf", &coord[index]) != 1) return INCORRECT_FILE;

  *line = strpbrk(*line, "0123456789");
  *line += strspn(*line, "0123456789");
  if (**line == '.') {
    *line += 1;
    *line += strspn(*line, "0123456789");
  }

  if (!(**line == '\r' || **line == ' ')) return INCORRECT_FILE;

  *line += 1;

  return OK;
}

