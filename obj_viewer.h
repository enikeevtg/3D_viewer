#ifndef OBJ_VIEWER_OBJ_VIEWER_H_
#define OBJ_VIEWER_OBJ_VIEWER_H_

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum error_codes { OK, NO_SUCH_FILE_OR_DIRECTORY, INCORRECT_FILE, RAM_ERROR };

typedef struct geometry_tag {
  int v_count;
  int f_count;
  double* array_vertex_x;
  double* array_vertex_y;
  double* array_vertex_z;
} geometry_info;

int get_object_info(FILE* fp, geometry_info* pobject);
void get_components_count(FILE* fp, geometry_info* pobject);
int get_vertices(FILE* fp, geometry_info* pobject);
int get_vertex_coordinate(char** line, double* coord, int index);
// void struct_clean(geometry_info* pobject);



#endif  // OBJ_VIEWER_OBJ_VIEWER_H_
