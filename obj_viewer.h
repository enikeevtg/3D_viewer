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
  int** array_faces;
} geometry_info;

int getObjectInfo(FILE* fp, geometry_info* pobject);
void getComponentsCount(FILE* fp, geometry_info* pobject);
int getComponents(FILE* fp, geometry_info* pobject);
int getVertex(char* line, geometry_info* pobject, int v_index);
int getFace(char* line, geometry_info* pobject, int f_index);

void structClean(geometry_info* pobject);



#endif  // OBJ_VIEWER_OBJ_VIEWER_H_
