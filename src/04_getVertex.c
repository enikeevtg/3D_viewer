#include "../obj_viewer.h"

int getVertexCoordinate(char** line, double* coord, int v_index);

/// @brief
/// @param line
/// @param pobject
/// @return
int getVertex(char* line, geometry_info* pobject, int v_index) {
  int error = OK;
  line++;
  line += strspn(line, " ");
  error = getVertexCoordinate(&line, pobject->array_vertex_x, v_index);
  if (!error)
    error = getVertexCoordinate(&line, pobject->array_vertex_y, v_index);
  if (!error)
    error = getVertexCoordinate(&line, pobject->array_vertex_z, v_index);
  return error;
}

int getVertexCoordinate(char** line, double* coord, int v_index) {
  // strtod()?
  if (sscanf(*line, "%lf", &coord[v_index]) != 1) return INCORRECT_FILE;

  *line = strpbrk(*line, ".0123456789");
  *line += strspn(*line, "0123456789");
  if (**line == '.') {
    *line += 1;
    *line += strspn(*line, "0123456789");
  }

  if (!(**line == '\r' || **line == ' ')) return INCORRECT_FILE;

  *line += strspn(*line, " ");

  return OK;
}
