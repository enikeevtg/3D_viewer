#include "../obj_viewer.h"

/// @brief 
/// @param fp 
/// @param pobject 
/// @return 
int get_components(FILE* fp, geometry_info* pobject) {
  int error = OK;
  pobject->array_vertex_x = (double*)calloc(pobject->v_count, sizeof(double));
  pobject->array_vertex_y = (double*)calloc(pobject->v_count, sizeof(double));
  pobject->array_vertex_z = (double*)calloc(pobject->v_count, sizeof(double));

  if (pobject->array_vertex_x == NULL || pobject->array_vertex_y == NULL ||
      pobject->array_vertex_z == NULL) {
    error = RAM_ERROR;
  } else {
    char* line = NULL;
    size_t line_len = 0;
    int index = 0;
    while (getline(&line, &line_len, fp) != -1 && !error) {
      if (line[0] == 'v' && line[1] == ' ' && line[2] == ' ') {
        get_vertices(line, pobject, index);
        index++;
      }
    }
    if (line) free(line);
  }
  return error;
}
