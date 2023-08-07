#include "../obj_viewer.h"

/// @brief
/// @param fp
/// @param pobject
/// @return
int getComponents(FILE* fp, geometry_info* pobject) {
  pobject->array_vertex_x = (double*)calloc(pobject->v_count, sizeof(double));
  pobject->array_vertex_y = (double*)calloc(pobject->v_count, sizeof(double));
  pobject->array_vertex_z = (double*)calloc(pobject->v_count, sizeof(double));

  pobject->array_faces = (int**)calloc(pobject->f_count, sizeof(int*));

  int error = OK;
  if (pobject->array_vertex_x == NULL || pobject->array_vertex_y == NULL ||
      pobject->array_vertex_z == NULL || pobject->array_faces == NULL) {
    error = RAM_ERROR;
  } else {
    char* line = NULL;
    size_t line_len = 0;
    int v_index = 0;
    int f_index = 0;
    while (getline(&line, &line_len, fp) != -1 && !error) {
      if (line[0] == 'v' && line[1] == ' ') {
        error = getVertex(line, pobject, v_index);
        v_index++;
      } else if (line[0] == 'f' && line[1] == ' ') {
        error = getFace(line, pobject, f_index);
        f_index++;
      }
    }
    if (line) free(line);
  }
  return error;
}
