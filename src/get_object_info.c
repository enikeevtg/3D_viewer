#include "../obj_viewer.h"

int get_object_info(FILE* fp, geometry_info* pobject) {
  int error = OK;

  char* line = NULL;
  size_t line_len = 0;
  while (getline(&line, &line_len, fp) != -1) {
    if (line[0] == 'v' && line[1] == ' ') pobject->v_count++;
    if (line[0] == 'f' && line[1] == ' ') pobject->f_count++;
  }

  printf("vertices number is %d\n", pobject->v_count);
  printf("faces number is %d\n", pobject->f_count);

  if (pobject->v_count < 3 || pobject->f_count < 1) return INCORRECT_FILE;

  pobject->array_vertex_x = (double*)calloc(pobject->v_count, sizeof(double));
  pobject->array_vertex_y = (double*)calloc(pobject->v_count, sizeof(double));
  pobject->array_vertex_z = (double*)calloc(pobject->v_count, sizeof(double));

  if (pobject->array_vertex_x == NULL || pobject->array_vertex_y == NULL ||
      pobject->array_vertex_z == NULL)
    return RAM_ERROR;

  fseek(fp, 0, SEEK_SET);
  int index = 0;
  while (getline(&line, &line_len, fp) != -1 && !error) {
    if (line[0] == 'v' && line[1] == ' ') {
      line += 2;
      error = get_vertex_coordinate(&line, pobject->array_vertex_x, index);
      if (!error)
        error = get_vertex_coordinate(&line, pobject->array_vertex_y, index);
      if (!error)
        error = get_vertex_coordinate(&line, pobject->array_vertex_z, index);
      index++;
    }
  }
  free(line);

  return error;
}

int get_vertex_coordinate(char** line, double* coord, int index) {
  if (sscanf(*line, "%lf", coord[index]) != 1) return INCORRECT_FILE;

  *line += strspn(*line, "0123456789");
  if (**line == '.') {
    *line += 1;
    *line += strspn(*line, "0123456789");
  }

  if (**line != ' ') return INCORRECT_FILE;

  *line += 1;

  return OK;
}
