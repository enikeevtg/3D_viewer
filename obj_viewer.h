#ifndef OBJ_VIEWER_OBJ_VIEWER_H_
#define OBJ_VIEWER_OBJ_VIEWER_H_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

enum error_codes { OK, NO_SUCH_FILE_OR_DIRECTORY };

typedef struct geometry_tag {
  int v_count;
  int f_count;
  double* vertex_x;
  double* vertex_y;
  double* vertex_z;
} geometry_info;





#endif  // OBJ_VIEWER_OBJ_VIEWER_H_
