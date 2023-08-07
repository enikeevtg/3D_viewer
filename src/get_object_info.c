#include "../obj_viewer.h"

int get_object_info(FILE* fp, geometry_info* pobject) {
  int error = OK;
  get_components_count(fp, pobject);

  // printf("vertices number is %d\n", pobject->v_count);
  // printf("faces number is %d\n", pobject->f_count);
  // char str[11] = {0};
  // printf("first line is: \"%s\"", fgets(str, 10, fp));

  if (pobject->v_count < 3 || pobject->f_count < 1) return INCORRECT_FILE;

  get_vertices(fp, pobject);

  for (int i = 0; i < 11; i++) {
    printf("#%d:\n x = %lf\n y = %lf\n z = %lf\n", i, pobject->array_vertex_x[i], pobject->array_vertex_y[i], pobject->array_vertex_z[i]);
  }
  return error;
}

void get_components_count(FILE* fp, geometry_info* pobject) {
  char* line = NULL;
  size_t line_len = 0;

  while (getline(&line, &line_len, fp) != -1) {
    if (line[0] == 'v' && line[1] == ' ') pobject->v_count++;
    if (line[0] == 'f' && line[1] == ' ') pobject->f_count++;
  }
  if (line) free(line);

  fseek(fp, 0, SEEK_SET);
}

int get_vertices(FILE* fp, geometry_info* pobject) {
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
      if (line[0] == 'v' && line[1] == ' ') {
        char* ptr = line + 3;
        error = get_vertex_coordinate(&ptr, pobject->array_vertex_x, index);
        if (!error)
          error = get_vertex_coordinate(&ptr, pobject->array_vertex_y, index);
        if (!error)
          error = get_vertex_coordinate(&ptr, pobject->array_vertex_z, index);
        index++;
      }
    }
    if (line) free(line);
  }
  return error;
}

int get_vertex_coordinate(char** line, double* coord, int index) {
  if (sscanf(*line, "%lf", &coord[index]) != 1) return INCORRECT_FILE;

  *line += strspn(*line, "-");
  *line += strspn(*line, "0123456789");
  if (**line == '.') {
    *line += 1;
    *line += strspn(*line, "0123456789");
  }

  if (!(**line == '\r' || **line == ' ')) return INCORRECT_FILE;

  *line += 1;

  return OK;
}
